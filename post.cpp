#include "post.h"

// POST class definitions

// pre: none
// post: creates a new Post with the parameters specified
std::string Post::displayPost() {
    std::string out = getMessage() + "\n" + std::to_string(getLikes().size()) + " likes\n" + std::to_string(getLaughs().size()) + " laughs\n" + std::to_string(getLoves().size()) + " loves\n" + std::to_string(getLives().size()) + " lives\n";
    return out;
}

// pre: none
// post: adds a reaction
void Post::addReaction(std::string type, std::string name) {
    if (type == "like") {
        likes_.push_back(name);
    }
    else if (type == "love") {
        loves_.push_back(name);
    }
    else if (type == "laugh") {
        laughs_.push_back(name);
    }
    else if (type == "live") {
        lives_.push_back(name);
    }
    else {
        std::cout << "Invalid reaction" << std::endl;
    }
}

// pre: none
// post: return the ID of the post
std::size_t Post::getID() {
    return id_;
}

// pre: none
// post: return the message of the post
std::string Post::getMessage() {
    return message_;
}

// pre: none
// post: return the users who liked the post
std::vector<std::string> Post::getLikes() {
    return likes_;
}

// pre: none
// post: return the users who liked the post
std::vector<std::string> Post::getLaughs() {
    return laughs_;
}

// pre: none
// post: return the users who liked the post
std::vector<std::string> Post::getLoves() {
    return loves_;
}

// pre: none
// post: return the users who liked the post
std::vector<std::string> Post::getLives() {
    return lives_;
}

// INCOMINGPOST class definitions

// pre: none
// post: returns a string of text with the message, the number of likes, and the author of the post
std::string IncomingPost::displayPost() {
    std::string out;
    if (isPublic_) {
        out = out + "\nPublic: \n";
    }
    else {
        out = out + "\nPrivate: \n";
    }

    // call the Post's displayPost()
    out = out + Post::displayPost();
    return out;
}

// pre: none
// post: return the value of isPublic_
bool IncomingPost::getIsPublic() {
    return isPublic_;
}
