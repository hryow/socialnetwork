#ifndef POST_H
#define POST_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

class Post {
public:
    // CONSTRUCTORS
    // pre: none
    // post: creates a new Post
    Post() : id_(0), message_(""), likes_(0) {}

    // pre: none
    // post: creates a new Post with the parameters specified
    Post(std::size_t i, std::string m, std::vector<std::string> l, std::vector<std::string> laugh,std::vector<std::string> love, std::vector<std::string> live) : id_(i), message_(m), likes_(l), laughs_(laugh), loves_(love), lives_(live) {}

    Post(std::size_t i, std::string m, std::size_t num_likes) :id_(i), message_(m), likesCount_(num_likes) {}

    // pre: none
    // post: returns a string of text with the message and then number of likes
    virtual std::string displayPost();

    // pre: none
    // post: adds a reaction
    void addReaction(std::string type, std::string name);

    // ACCESSOR FUNCTIONS
    // pre: none
    // post: return the ID of the post
    std::size_t getID();

    // pre: none
    // post: return the message of the post
    std::string getMessage();

    // pre: none
    // post: return the users who liked the post
    std::vector<std::string> getLikes();

    // pre: none
    // post: return the users who liked the post
    std::vector<std::string> getLaughs();

    // pre: none
    // post: return the users who liked the post
    std::vector<std::string> getLoves();

    // pre: none
    // post: return the users who liked the post
    std::vector<std::string> getLives();
private:
    std::size_t id_;
    std::string message_;
    std::vector<std::string> likes_;
    std::vector<std::string> laughs_;
    std::vector<std::string> loves_;
    std::vector<std::string> lives_;
    std::size_t likesCount_;
};

class IncomingPost : public Post {
public:
    // CONSTRUCTORS
    // pre: none
    // post: creates a new IncomingPost
    IncomingPost() {
        isPublic_ = false;
    }

    // pre: none
    // post: creates a new IncomingPost with the parameters specified
    IncomingPost(std::size_t i, std::string m, std::vector<std::string> l, std::vector<std::string> laugh, std::vector<std::string> loves, std::vector<std::string> lives, bool p, std::string n) : Post(i, (m + "\nFrom: " + n), l, laugh, loves, lives) {
        isPublic_ = p;
    }

    IncomingPost(std::size_t i, std::string m, std::size_t num_likes, bool p, std::string n) : Post(i, (m + "\nFrom: " + n), num_likes) {
        isPublic_ = p;
    }

    // pre: none
    // post: returns a string of text with the message, the number of likes, and the author of the post
    std::string displayPost();

    // ACCESSORS
    // pre: none
    // post: return the value of isPublic_
    bool getIsPublic();
private:
    bool isPublic_;
};

#endif
