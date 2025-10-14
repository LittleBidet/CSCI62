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