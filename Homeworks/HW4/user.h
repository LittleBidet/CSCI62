#ifndef USER_H
#define USER_H

#include <string>
#include <set>

class User {
        private:
                int id_;
                std::string name_;
                int year_;
                int zip_;
                std::set<int> friends_;

        public:
                //Constructors
                //Pre: None
                //Post: Initializes a default user
                User();
                //Pre: Takes in ID, Name, Birthyear, Zip, and a set of friends.
                //Post: Initializes a user with these specific values. 
                User(int id, std::string name, int year, int zip, std::set<int> friends);

                //getters: returns corresponding information

                //Pre: None
                //Post: Returns the ID of the User
                int getId() const;

                //Pre: None
                //Post: Returns the name of the User.
                std::string getName() const;

                //Pre: None
                //Post: Returns the birthyear of the User.
                int getYear() const;

                //Pre: None
                //Post: Returns the zip code of the User.
                int getZip() const;

                //Pre: None
                //Post: Returns the User's set of friends.
                std::set<int>& getFriends();

                //modifier functions
                //Pre: The ID of the friend.
                //Post: Adds the ID of the friend to the User's friend set.
                void addFriend(int id);

                //Pre: The ID of the friend.
                //Post: Deletes the ID of the friend from the User's friend set.
                void deleteFriend(int id);
};

#endif