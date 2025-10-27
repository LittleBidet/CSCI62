#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include "post.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class Network{
        public:
                //Pre: None.
                //Post: Initializes an enpty network.
                Network();
                //Pre: ID of user we want to find. 
                //Post: returns a pointer to the corresponding user. Returns nullptr if none found.
                User* getUser(int id);

                //Pre: Pointer to a user we want to add.
                //Post: Adds user to the vector of users in the network.
                void addUser(User*);

                //Pre: Two sets of first and last names.
                //Post: Adds a friend connection between the two users. Returns 0 if successful and -1 if not.
                int addConnection(std::string s1, std::string s2);


                //Pre: Two sets of first and last names.
                //Post: Deletes a friend connection between the two users. Returns 0 if successful and -1 if not.
                int deleteConnection(std::string s1, std::string s2);

                //Pre: Name of the user we want the ID for.
                //Post: Returns the ID corresponding to the name if found o returns -1 if not found.
                int getId(std::string name);

                //Pre: None.
                //Post: Returns the number of users in the network.
                int numUsers();

                //Pre: Filename we want to read from.
                //Post: Adds the users and their corresponding connections from the file to the network.
                void readUsers(const char* fname);

                //Pre: Filename we want to read to.
                //Post: Writes the users and their corresponding connections from the network to the file.
                void writeUsers(const char* fname);

                //Pre: Takes in two users as IDs.
                //Post: Returns a vector containing the shortest path between the two users.
                std::vector<int> shortestPath(int from, int to);

                //Pre: Takes in a User ID, a reference to an integer, and the relational distance we want.
                //Post: Finds a user whose relational distance from the User matches the distance given, 
                //sets the integer reference to the integer reference, and returns the vectors of User IDs of the shortest path.
                std::vector<int> distanceUser(int from, int& to, int distance);

                //Pre: Takes in a User and an integer reference to keep track of the highest score.
                //Post: Sets the integer reference to the highest score and returns a lst of Users who have that score.
                std::vector<int> suggestFriends(int who, int& score);

                //Pre: None.
                //Post: Computes the connected components of the network and returns the list of all the corresponding IDs.
                std::vector<std::vector<int> > groups();

                //Pre: From User ID, reference to a list of visited Users
                //Post: Returns a list of all the IDs of Users that are connected to the from User.
                std::vector<int> groupHelper(int from, std::vector<bool>& visited);

                //Pre: A post pointer.
                //Post: Assigns an ID to the post and adds it to the specific user's vector of posts.
                void addPost(Post* post);
                
                //Pre: A User id
                //Post: Returns a vector containing all the Posts corresponding to the provided User.
                std::vector<Post*> getPosts(int id);

                //Pre: A Post pointer.
                //Post: Returns a string showing who the author is and the message of the post.
                std::string postDisplayString(Post* post);

                //Pre: A User id and an interger of how many posts to return.
                //Post: Returns the most recent posts from the specified user.
                std::string getPostsString(int profileId, int howMany);

                //Pre: File name to read from.
                //Post: Reads in Posts from a file into the network.
                int readPosts(char* fname);

                //Pre: File name to write to.
                //Post: Writes in Posts from the network to the file.
                int writePosts(char* fname);


        private:
                std::vector<User*> users_;
                std::vector<std::vector<Post*>> posts_;
                

};

#endif