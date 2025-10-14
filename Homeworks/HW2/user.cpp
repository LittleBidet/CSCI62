#include "user.h"

User::User(): id_(1), name_("James James"), year_(2000), zip_(11111){};
User::User(int id, std::string name, int year, int zip, std::set<int> friends)
        : id_(id), name_(name), year_(year), zip_(zip) , friends_(friends){};

int User::getId() const{
        return id_;
}
std::string User::getName() const{
        return name_;
}
int User::getYear() const{
        return year_;
}
int User::getZip() const{
        return zip_;
}
std::set<int>& User::getFriends(){
        return friends_;
}
void User::addFriend(int id){
        friends_.insert(id);
}
void User::deleteFriend(int id){
        friends_.erase(id);
}