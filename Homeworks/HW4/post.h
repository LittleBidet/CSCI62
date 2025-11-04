#ifndef POST_H
#define POST_H

#include <string>

class Post{
        public:
                //Pre: n/a
                //Post: initializes an empty post object
                Post();
                //Pre: profile id, author id, message, likes
                //Post: A post object with the corresponding stats
                Post(int profileId, int authorId, std::string message, int likes);
                //Pre: n/a
                //Post: returns the message id
                int getMessageId();
                //Pre: id of a message
                //Post: sets the message id
                void setMessageId(int id);
                //Pre: n/a
                //Post: returns the post's profile id;
                int getProfileId();
                //Pre: n/a
                //Post: returns the post's author id
                int getAuthorId();
                //Pre: n/a
                //Post: returns the post's message
                std::string getMessage();
                //Pre: n/a
                //Post: returns the post's like count
                int getLikes();
                //Pre: n/a
                //Post: Virtual function, returns an empty string
                std::string virtual getURL();
                //Pre: n/a
                //Post: Virtual function, prints the message content and likes of a post
                std::string virtual toString();
        private:
               int messageId_;
               int profileId_;
               int authorId_;
               std::string message_;
               int likes_;
};
class LinkPost : public Post{
        public:
                //Pre: n/a
                //Post: initializes an empty LinkPost object
                LinkPost();
                //Pre: profile id, author id, message, likes, and url
                //Post: A LinkPost object with the corresponding stats
                LinkPost(int profileId, int authorId, std::string message, int likes, std::string url);
                //Pre: n/a
                //Post: returns the LinkPost's message
                std::string getURL();
                //Pre: n/a
                //Post: prints the  message content, url, and likes of a LinkPost
                std::string toString();
        private:
                std::string url_;
};

#endif