#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
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
        private:
                std::vector<User*> users_;

};

#endif