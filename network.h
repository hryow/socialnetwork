// CHANGES MADE SINCE HW1: none
#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <algorithm>

#include "user.h"

class Network {
public:
    // pre: none
    // post: creates a new Network
    Network();

    // pre: none
    // post: frees memory use on the heap
    ~Network();

    // pre: none
    // post: add a User to the Network
    void addUser(User* u);

    // pre: none
    // post: add a connection between two users
    int addConnection(std::string s1, std::string s2);

    // pre: there is a connection between the two users
    // post: the connection is removed
    int removeConnection(std::string s1, std::string s2);

    // pre: none
    // post: return the id of a particular user
    std::size_t getId(std::string name);

    // pre: none
    // post: read the file's information and add them to the Network
    int readUsers(char* fname);

    // pre: none
    // post: write all Network information to a specified file name
    int writeUsers(char* fname);

    // pre: none
    // post: return the number of users in the Network
    std::size_t numUsers();

    // pre: the User is in the Network
    // post: returns a pointer to the corresponding User
    User* getUser(std::size_t id);

    // pre: the users are present within the Network
    // post: returns the shortest path between two users within the Network
    std::vector<std::size_t> shortestPath(std::size_t from, std::size_t to);

    // pre: there is a connection between the users
    // post: returns a vector of the path between 2 users within a certain distance
    std::vector<std::size_t> distanceUser(std::size_t from, std::size_t& to, std::size_t distance);

    // pre: none
    // post: return a list of the ids of users who have the score
    std::vector<std::size_t> suggestFriends(std::size_t who, std::size_t& score);

    // pre: none
    // post: outputs a vector with all of the groups within the Network
    std::vector<std::vector<std::size_t>> groups();

    // pre: the specified user has posts
    // post: return a string containing the most recent posts of a particular user
    std::string displayPosts(std::string name, std::size_t howMany, bool showOnlyPublic);

    // pre: none
    // post: adds the post to the user's messages_ list
    void addPost(std::size_t ownerId, std::string message, std::vector<std::string> likes, std::vector<std::string> laughs, std::vector<std::string> loves, std::vector<std::string> deads, bool incoming, std::size_t author, bool IsPublic);

    // pre: none
    // post: reads in the posts from a file
    // int readPosts(char* filename);
private:
    std::vector<User*> users_;
};

#endif
