// CHANGES MADE SINCE HW 1: none
#include "user.h"

// pre: none
// post: creates a new User
User::User() {
    id_ = 0;
    name_ = "";
    year_ = 0000;
    zip_ = 00000;
    std::vector<std::size_t> v;
    friends_ = v;
}

// pre: none
// post: creates a new user with the parameters specified
User::User(std::size_t id, std::string name, std::size_t year, std::size_t zip, std::vector<std::size_t> friends) {
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    friends_ = friends;
}

User::~User() {
    friends_.clear();
    messages_.clear();
}

// pre: none
// post: returns the user's ID
std::size_t User::getId() {
    return id_;
}

// pre: none
// post: returns the user's name
std::string User::getName() {
    return name_;
}

// pre: none
// post: returns the user's birth year
std::size_t User::getYear() {
    return year_;
}

// pre: none
// post: returns the user's zip code
std::size_t User::getZip() {
    return zip_;
}

// pre: none
// post: returns the user's friends
std::vector<std::size_t> User::getFriends() {
    return friends_;
}

// pre: none
// post: returns the vector of Posts
std::vector<Post*> User::getMessages() {
    return messages_;
}

// pre: the friend is not already a friend
// post: the friend is a part of the user's friend list
void User::addFriend(std::size_t id) {
    // check if the friend is in the user's friend list
    for (int i = 0; i < friends_.size(); i++) {
        if (friends_[i] == id) {
            return;
        }
    }

    // add the friend's id to the user's vector of friend IDs
    friends_.push_back(id);
}

// pre: the friend's ID is in the list of friends
// post: delete the friend's ID from the user's friend list
void User::deleteFriend(std::size_t id) {
    // check if the friend is in the user's friend's list
    std::size_t pos;
    bool notfound = true;
    for(int i = 0; i < friends_.size(); i++) {
        // stop if the ID is found
        if (friends_[i] == id) {
            pos = i;
            notfound = false;
            break;
        }
    }
    // if the friend's ID isn't found then do nothing
    if (notfound) {
        std::cout << "Friend ID not found." << std::endl;
        return;
    }

    // delete the friend from the list
    friends_.erase(friends_.begin() + pos);
}

// pre: none
// post: adds a post to the vector of posts
void User::addPost(Post* p) {
    messages_.push_back(p);
}

// pre: the messages_ vector starts from the most recent
// post: returns a string shows the most recent howmany posts
std::string User::displayPosts(std::size_t howmany, bool showOnlyPublic) {
    std::string out;
    if (howmany > getMessages().size()) {
        out = out + "Desired number of posts exceeds the number of posts that this user has. Showing all of the user's messages.";
        howmany = getMessages().size();
    }
    std::size_t messagecount = 0;
    for (int i = 0; i < messages_.size(); i++) {
        std::string message = messages_[i]->displayPost();
        // if the post is private (i.e. if the second character of the message is r)
        if (showOnlyPublic && message.length() >= 2 && message[1] == 'r') {
            continue;
        }
        else {
            out = out + (messages_[i]->displayPost()) + "\n\n";
            messagecount++;
        }
        if (messagecount == howmany) {
            break;
        }
    }
    return out;
}
