#include "network.h"

Network::Network(): users_() {};
User* Network::getUser(int id){
        if(id >= 0 && id < users_.size()){
                return users_[id];
        }
        return nullptr;
}

void Network::addUser(User* user){
        users_.push_back(user);
        posts_.push_back(std::vector<Post*>());
}
int Network::addConnection(std::string s1, std::string s2){
        int firstId = getId(s1);
        int secondId = getId(s2);
        //Checks if both user exists
        if(firstId  == -1 || secondId == -1){
                return -1;
        }
        User* firstUser = getUser(firstId);
        User* secondUser = getUser(secondId);
        firstUser->addFriend(secondId);
        secondUser->addFriend(firstId);
        return 0;
}
int Network::deleteConnection(std::string s1, std::string s2){
        int firstId = getId(s1);
        int secondId = getId(s2);
        //Checks if both user exists
        if(firstId  == -1 || secondId == -1){
                return -1;
        }
        User* firstUser = getUser(firstId);
        User* secondUser = getUser(secondId);
        firstUser->deleteFriend(secondId);
        secondUser->deleteFriend(firstId);

        return 0;
}

int Network::getId(std::string name){
        //Iterates through the list of users and checks the name of each user.
        for(User* cur : users_){
                if(cur->getName() == name){
                        return cur->getId();
                }
        }
        return -1;
}
int Network::numUsers(){
        return users_.size();
}

void Network::readUsers(const char* fname){
        std::ifstream myfile(fname);
        if(!myfile.is_open()) return;
        std::string myline;
        getline(myfile, myline);
        int num_users = stoi(myline);
        for(int i = 0; i < num_users; i++){
                int id, year, zip;
                std::string username; 

                getline(myfile, myline);
                id = stoi(myline);

                getline(myfile, myline);
                //Skips the leading tab
                username = myline.substr(1);

                //Uses stoi() to convert strong into int
                getline(myfile, myline);
                year = stoi(myline);
                getline(myfile, myline);
                zip = stoi(myline);

                User* newUser = new User(id, username, year, zip, {});
                getline(myfile, myline);
                std::stringstream ss(myline);
                int friendIds;
                while(ss >> friendIds){
                        newUser->addFriend(friendIds);
                }
                addUser(newUser);
        }
}
void Network::writeUsers(const char* fname){
        std::ofstream myfile(fname);
        if(!myfile.is_open()) return;
        std::string myline;
        int num_users = users_.size();
        myfile << users_.size() << '\n';
        for(int i = 0; i < num_users; i++){
                myfile << users_[i]->getId() << '\n';
                myfile << '\t' << users_[i]->getName() << '\n';
                myfile << '\t' << users_[i]->getYear() << '\n';
                myfile << '\t' << users_[i]->getZip() << '\n';
                myfile << '\t';
                for(int ids : users_[i]->getFriends()){
                        myfile << ids << ' ';

                }
                myfile << '\n';
        }
}
std::vector<int> Network::shortestPath(int from, int to){
        std::queue<int> q;
        std::vector<int> previous(numUsers(), -1);
        std::vector<bool> visited(numUsers(), 0);
        visited[from] = true;
        q.push(from);
        while(q.size() > 0){
                int cur = q.front();
                q.pop();
                for(int neighborID : getUser(cur)->getFriends()){
                        if(!visited[neighborID]){
                                previous[neighborID] = cur;
                                visited[neighborID] = true;
                                q.push(neighborID);
                        }
                }
        }
        if(visited[to] == 0){
                return {};
        }
        std::vector<int> output;
        int currentUser = to;
        while(currentUser != -1){
                output.push_back(currentUser);
                currentUser = previous[currentUser];
        }
        std::reverse(output.begin(), output.end());
        return output;
}
std::vector<int> Network::distanceUser(int from, int& to, int distance){
        std::queue<int> q;
        std::vector<int> dist(numUsers(), -1);
        std::vector<bool> visited(numUsers(), 0);
        visited[from] = true;
        dist[from] = 0;
        q.push(from);
        while(q.size() > 0){
                int cur = q.front();
                q.pop();
                for(int neighborID : getUser(cur)->getFriends()){
                        if(!visited[neighborID]){
                                dist[neighborID] = dist[cur] + 1;
                                visited[neighborID] = true;
                                if(dist[neighborID] == distance){
                                        to = neighborID;
                                        return shortestPath(from, to);
                                }
                                q.push(neighborID);
                        }
                }
        }
        to = -1;
        return {};
}
std::vector<int> Network::suggestFriends(int who, int& score){
        std::queue<int> q;
        std::vector<int> scoreList(numUsers(), -1);
        std::vector<bool> visited(numUsers(), 0);
        visited[who] = true;
        q.push(who);
        while(q.size() > 0){
                int cur = q.front();
                q.pop();
                std::set<int> whosFriends = getUser(who)->getFriends();
                for(int neighborID : getUser(cur)->getFriends()){
                        if(!visited[neighborID]){
                                std::set<int> friendsFriend = getUser(neighborID)->getFriends();
                                int similarity = 0;
                                for(auto i : whosFriends){
                                        if(friendsFriend.find(i) != friendsFriend.end()){
                                                similarity++;
                                        }
                                }
                                scoreList[neighborID] = similarity;
                                visited[neighborID] = true;
                                q.push(neighborID);
                        }
                }
        }
        //finds the highest score
        score = 0;
        for(int i = 0; i < scoreList.size(); i++){
               if(scoreList[i] > score){
                        score = scoreList[i];
               } 
        }
        //gets all Users with the highest similarity score
        std::vector<int> output;
        for(int i = 0; i < scoreList.size(); i++){
               if(scoreList[i] == score && getUser(i)->getFriends().count(who) == 0){
                        output.push_back(i);
               }
        }
        return output;
}
std::vector<std::vector<int>> Network::groups(){
        std::vector<std::vector<int>> output;
        std::vector<bool> visited(numUsers(), 0);
        
        //iterates through the users in the network, adding the group to the output if its not already in the list
        for(int i = 0; i<numUsers(); i++){
                if(!visited[i]){
                        output.push_back(groupHelper(i, visited));
                }
        }
        return output;

}
std::vector<int> Network::groupHelper(int from, std::vector<bool>& visited){
        std::stack<int> q;
        std::vector<int> output;
        visited[from] = true;
        q.push(from);
        output.push_back(from);
        while(q.size() > 0){
                int cur = q.top();
                q.pop();
                for(int neighborID : getUser(cur)->getFriends()){
                        if(!visited[neighborID]){
                                visited[neighborID] = true;
                                q.push(neighborID);
                                output.push_back(neighborID);
                        }
                }
        }
        return output;
}
void Network::addPost(Post* post){
        int user = post->getProfileId();
        if(user < users_.size() && user >= 0){
                int newId = 0;
                for(auto userPosts : posts_) {
                    newId += userPosts.size();
                }
                post->setMessageId(newId);
                posts_[user].push_back(post);
        }
}
std::vector<Post*> Network::getPosts(int id){
        if(id < posts_.size() && id >= 0){
                return posts_[id];
        }
        return {};
}
std::string Network::postDisplayString(Post* post){
        int id = post->getAuthorId();
        std::string name = getUser(id)->getName();
        return  name + " wrote: " + post->toString();
}
std::string Network::getPostsString(int profileId, int howMany){
        std::vector<Post*> postList = getPosts(profileId);
        std::string output;
        int count = 0;
        for(int i = postList.size()-1; i >= 0 && count < howMany; i--) {
                output += (postDisplayString(postList[i]) + "\n\n");
                count++;
        }
        return output;
}
int Network::readPosts(char* fname){
        std::ifstream myfile(fname);
        if(!myfile.is_open()) return -1;
        std::string myline;
        getline(myfile, myline);
        int numPosts = stoi(myline);
        for(int i = 0; i < numPosts; i++){
                int profile, author, mesID, likes;
                std::string message, url;

                
                getline(myfile, myline);
                mesID = stoi(myline);

                getline(myfile, myline);
                message = myline;

                //Uses stoi() to convert strong into int
                getline(myfile, myline);
                profile = stoi(myline.substr(1));

                getline(myfile, myline);
                author = stoi(myline.substr(1));

                getline(myfile, myline);
                likes = stoi(myline.substr(1));

                getline(myfile, myline);
                url = myline;

                if(url == ""){
                        Post* newPost = new Post(profile, author, message, likes);
                        addPost(newPost);
                }
                else{
                        Post* newPost = new LinkPost(profile, author, message, likes, url.substr(1));
                        addPost(newPost);
                }
        }
        return numPosts;
}
bool comparison(Post* a, Post* b){
        return a->getMessageId() < b->getMessageId();
}
int Network::writePosts(char* fname){
        std::ofstream myfile(fname);
        if(!myfile.is_open()) return -1;
        std::string myline;

        std::vector<Post*> allPosts;
        for(int i = 0; i < posts_.size(); i++){
                for(auto j : posts_[i]){
                        allPosts.push_back(j);
                }
        }
        std::sort(allPosts.begin(), allPosts.end(), comparison);
        int numPosts = allPosts.size();

        myfile << numPosts << '\n';
        for(int i = 0; i < numPosts; i++){
                myfile << allPosts[i]->getMessageId() << '\n';
                myfile << '\t' << allPosts[i]->getMessage() << '\n';
                myfile << '\t' << allPosts[i]->getProfileId() << '\n';
                myfile << '\t' << allPosts[i]->getAuthorId() << '\n';
                myfile << '\t' << allPosts[i]->getLikes() << '\n';
                myfile << '\t' << allPosts[i]->getURL() << '\n';
        }
        return numPosts;
}