// CHANGES MADE SINCE HW1: none
#ifndef USER_H
#define USER_H

#include <vector>
#include <cassert>
#include <string>
#include <iostream>

#include "post.h"

class User {
public:
    // CONSTRUCTORS
    // pre: none
    // post: creates a new User
    User();

    // pre: none
    // post: creates a new user with the parameters specified
    User(std::size_t id, std::string name, std::size_t year, std::size_t zip, std::vector<std::size_t> friends);

    // pre: none
    // post: clears the memory off the heap
    ~User();

    // ACCESSORS
    // pre: none
    // post: return the user's ID
    std::size_t getId();

    // pre: none
    // post: returns the user's name
    std::string getName();

    // pre: none
    // post: returns the user's birth year
    std::size_t getYear();

    // pre: none
    // post: returns the user's zip code
    std::size_t getZip();

    // pre: none
    // post: returns the user's friends
    std::vector<std::size_t> getFriends();

    // pre: none
    // post: returns the vector of Posts
    std::vector<Post*> getMessages();

    // pre: the friend is not already a friend
    // post: the friend is a part of the user's friend list
    void addFriend(std::size_t id);

    // pre: the friend's ID is in the list of friends
    // post: delete the friend's ID from the user's friend list
    void deleteFriend(std::size_t id);

    // pre: none
    // post: adds a post to the vector of posts
    void addPost(Post* p);

    // pre: the messages_ vector starts from the most recent
    // post: returns a string shows the most recent howmany posts
    std::string displayPosts(std::size_t howmany, bool showOnlyPublic);
private:
    std::size_t id_;
    std::string name_;
    std::size_t year_;
    std::size_t zip_;
    std::vector<std::size_t> friends_;
    std::vector<Post*> messages_;
};

#endif
