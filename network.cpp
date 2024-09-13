// CHANGES MADE SINCE HW1: defined the writeUsers function
#include "network.h"

// pre: none
// post: creates a new Network
Network::Network() {
    std::vector<User*> u;
    users_ = u;
}

// pre: none
// post: frees memory use on the heap
Network::~Network() {
    users_.clear();
}

// pre: none
// post: add a User to the Network
void Network::addUser(User* u) {
    // check if the user already exists
    for (int i = 0; i < users_.size(); i++) {
        if (users_[i] == u) {
            return;
        }
    }

    // add the user if the user doesn't exist yet
    users_.push_back(u);
}

// pre: none
// post: add a connection between two users
int Network::addConnection(std::string s1, std::string s2) {

    // get the user's IDs
    std::size_t User1Id = getId(s1);
    std::size_t User2Id = getId(s2);

    // make pointers to the users
    User* User1ptr = getUser(User1Id);
    User* User2ptr = getUser(User2Id);

    // check if the users are already friends
    bool flag = false;
    for (int i = 0; i < User1ptr->getFriends().size(); i++) {
        if (User1ptr->getFriends()[i] == User2Id) {
            flag = true;
        }
    }

    // if the users are friends, then return -1
    if (flag) {
        return -1;
    }

    User1ptr->addFriend(User2Id);
    User2ptr->addFriend(User1Id);
    return 0;
}

// pre: there is a connection between the two users
// post: the connection is removed
int Network::removeConnection(std::string s1, std::string s2) {
    // get the user's IDs
    std::size_t User1Id = getId(s1);
    std::size_t User2Id = getId(s2);

    // make pointers to the users
    User* User1ptr = getUser(User1Id);
    User* User2ptr = getUser(User2Id);

    // check if the users are already friends
    bool flag = true;
    for (int i = 0; i < User1ptr->getFriends().size(); i++) {
        if (User1ptr->getFriends()[i] == User2Id) {
            flag = false;
        }
    }

    // if the users aren't friends
    if (flag) {
        return -1;
    }

    User1ptr->deleteFriend(User2Id);
    User2ptr->deleteFriend(User1Id);
    return 0;
}

// pre: none
// post: return the id of a particular user
std::size_t Network::getId(std::string name) {
    // find the user
    for (int i = 0; i < users_.size(); i++) {
        if (users_[i]->getName() == name) {
            return users_[i]->getId();
        }
    }

    // if the user isn't found
    std::cout << "Unable to find the user." << std::endl;
    return -1;
}

// pre: none
// post: read the file's information and add them to the Network
int Network::readUsers(char* fname) {
    std::ifstream file;
    file.open(fname);
    if (!file.is_open()) {
        return -1; // file not open or not found
    }

    int n;
    file >> n;
    std::cout << n << std::endl;

    for (int i = 0; i < n; i++) {
        std::size_t id;
        std::string first_name, last_name, name;
        int year;
        int zip;
        std::vector<std::size_t> friends;
        friends.clear();

        file >> id;
        file >> first_name >> last_name;
        file >> year;
        file >> zip;
        name = first_name + " " + last_name;

        std::string line;
        std::getline(file, line);
        std::getline(file, line);

        std::stringstream ss(line);

        std::size_t id2;
        while (ss >> id2) {
            friends.push_back(id2);
        }

        User* u = new User(id, name, year, zip, friends);
        addUser(u);
    }
    return 0;
}

// pre: none
// post: write all Network information to a specified file name
int Network::writeUsers(char* fname) {
    std::ofstream file(fname);
    if (!file) {
        std::cout << "File not created." << std::endl;
        return -1;
    }
    else {
        std::cout << "File created successfully." << std::endl;
        User* ptr;
        for (int i = 0; i < users_.size(); i++) {
            ptr = users_[i];
            file << std::to_string(ptr->getId()) << std::endl;
            file << "\t" << ptr->getName() << std::endl;
            file << "\t" << std::to_string(ptr->getYear()) << std::endl;
            file << "\t" << std::to_string(ptr->getZip()) << std::endl;
            file << "\t";
            std::vector<size_t> usersfriendslist = ptr->getFriends();
            for (int j = 0; j < usersfriendslist.size(); j++) {
                std::cout << usersfriendslist[i] << std::endl;
                file << usersfriendslist[i] << " ";
            }
            file << std::endl;
        }
        file.close();
    }
    return 0;
}

// pre: none
// post: return the number of users in the Network
std::size_t Network::numUsers() {
    return users_.size();
}

// pre: the User is in the Network
// post: returns a pointer to the corresponding User
User* Network::getUser(std::size_t id) {
    User* ptr;
    for (int i = 0; i < users_.size(); i++) {
        if (users_[i]->getId() == id) {
            ptr = users_[i];
        }
    }
    return ptr;
}

// pre: there are users within the Network
// post: returns the shortest path between two users within the Network
std::vector<std::size_t> Network::shortestPath(std::size_t from, std::size_t to) {
    std::queue<std::size_t> q;
    std::vector<bool> visited(users_.size(), 0); // vector tracking of which users have already been visited
    std::vector<std::size_t> previous(users_.size(), -1); // vector holding the previous users
    std::vector<std::size_t> out;

    if (from == to) {
        out.push_back(from);
        return out;
    }

    q.push(from);

    // start traversing the graph
    while (q.size() > 0) {
        // visit the next user in the graph
        std::size_t curr = q.front();
        q.pop();

        if (visited[curr]) {
            continue;
        }
        // mark the current user as visited
        visited[curr] = true;

        // add all of the user's friends to the queue
        for (int i = 0; i < users_[curr]->getFriends().size(); i++) {
            q.push(users_[curr]->getFriends()[i]);
            if (previous[i] == -1 && i != from) {
                previous[i] = curr;
            }
        }
    }
    // fill the out vector with the pathway
    std::size_t i = to;
    while (i != -1) {
        out.push_back(i);
        i = previous[i];
    }
    // make sure that the starting point is the first term
    std::reverse(out.begin(), out.end());
    return out;
}

// pre: there is a connection between the users
// post: returns a vector of the path between 2 users within a certain distance
std::vector<std::size_t> Network::distanceUser(std::size_t from, std::size_t& to, std::size_t distance) {
    std::queue<std::size_t> q;
    std::vector<bool> visited(users_.size(), 0); // vector tracking of which users have already been visited
    std::vector<std::size_t> previous(users_.size(), -1); // vector holding the previous users
    std::vector<std::size_t> dist(users_.size(), 0); // vector tracking the distance each user is from the source
    std::vector<std::size_t> out;

    q.push(from);

    // start traversing the graph
    while (q.size() > 0) {
        // visit the next user in the graph
        std::size_t curr = q.front();
        q.pop();

        if (visited[curr]) {
            continue;
        }

        // mark the current user as visited
        visited[curr] = true;

        // add all of the user's friends to the queue
        for (int i = 0; i < users_[curr]->getFriends().size(); i++) {
            q.push(users_[curr]->getFriends()[i]);
            dist[users_[curr]->getFriends()[i]] += 1; // somethings wrong here
            if (previous[i] == -1 && i != from) {
                previous[i] = curr;
            }
        }
    }

    to = -1;

    // find the user indices that match the distance
    for (int i = 0; i < dist.size(); i++) {
        std::cout << dist[i] << std::endl;
        if (dist[i] == distance) {
            to = i;
        }
    }

    if (to == -1) {
        return out;
    }

    // fill the out vector with the pathway
    std::size_t j = to;
    while (j != -1) {
        out.push_back(j);
        j = previous[j];
    }

    // make sure that the starting point is the first term
    std::reverse(out.begin(), out.end());
    return out;
}


// pre: none
// post: return a list of the ids of users who have the score
std::vector<std::size_t> Network::suggestFriends(std::size_t who, std::size_t& score) {
    std::vector<std::size_t> count(users_.size(), 0);
    score = 0;

    // look at who's friends of friends
    for (int i = 0; i < users_[who]->getFriends().size(); i++) {
        // get who's friends
        User* ptr = getUser(users_[who]->getFriends()[i]);

        // iterate through who's friend's friends list
        for (int j = 0; j < ptr->getFriends().size(); j++) {
            User* ptr1 = getUser(ptr->getFriends()[j]);

            // iterate through who's friend's friend's friends list
            for (int k = 0; k < ptr1->getFriends().size(); k++) {
                // increment the count if the users have mutual friends
                if (ptr1->getFriends()[k] == users_[who]->getFriends()[i]) {
                    count[k]++;
                }
            }
        }
    }

    // find the users who have the highest score
    std::vector<std::size_t> userids;
    for (int i = 0; i < count.size(); i++) {
        if (count[i] > score) {
            score = count[i];
        }
    }

    for (int i = 0; i < count.size(); i++) {
        if (count[i] == score) {
            userids.push_back(i);
        }
    }

    if (score == 0) {
        score = -1;
    }

    return userids;
}

// pre: none
// post: outputs a vector with all of the groups within the Network
std::vector<std::vector<std::size_t> > Network::groups() {
    // use DFS
    std::vector<std::vector<std::size_t>> output;
    for (int i = 0; i < numUsers(); i++){
        std::vector<std::size_t> out;
        std::vector<std::size_t> stack;
        std::vector<bool> visited(numUsers(), 0);

        stack.push_back(numUsers());

        while (stack.size() > 0) {
            // visit the next user
            std::size_t curr = stack[stack.size() - 1];
            stack.pop_back();

            if (visited[curr]) {
                continue;
            }
            visited[curr] = true;

            // add the current user to the current connection
            out.push_back(curr);

            // add their friends to the stack
            for (int i = 0; i < users_[curr]->getFriends().size(); i++) {
                stack.push_back(users_[curr]->getFriends()[i]);
                out.push_back(i);
            }
        }

        // add the cycle
        for (int i = 0; i < out.size(); i++) {
            output.push_back(out);
        }
    }


    return output;
}

// pre: the specified user has posts
// post: return a string containing the most recent posts of a particular user
std::string Network::displayPosts(std::string name, std::size_t howMany, bool showOnlyPublic) {
    std::string out;
    // find the user in the users_ array
    std::size_t userid = getId(name);
    User* ptr;
    for (int i = 0; i < users_.size(); i++) {
        if (userid == i) {
            ptr = users_[i];
        }
    }

    // using the User::displayPosts function
    out = ptr->displayPosts(howMany, showOnlyPublic);
    return out;
}

// pre: none
// post: adds the post to the user's messages_ list
void Network::addPost(std::size_t ownerId, std::string message, std::vector<std::string> likes, std::vector<std::string> laughs, std::vector<std::string> loves, std::vector<std::string> lives, bool incoming, std::size_t author, bool IsPublic) {
    // find the user in the Network
    User* ptr;
    for (int i = 0; i < users_.size(); i++) {
        if (ownerId == i) {
            ptr = users_[i];
        }
    }

    // find the id of the messsage
    std::size_t message_id = ptr->getMessages().size() + 1;

    // check if the Post is incoming or not
    Post* p;
    if (incoming) {
        User* u = getUser(author);
        std::string author_name = u->getName();
        p = new IncomingPost(message_id, message, likes, laughs, loves, lives, IsPublic, author_name);
    }
    else {
        p = new Post(message_id, message, likes, laughs, loves, lives);
    }

    // add the post to the user's page
    ptr->addPost(p);
}


// pre: none
// post: reads in the posts from a file
// int Network::readPosts(char* filename) {
// 	std::ifstream file;
// 	file.open(filename);

// 	// check if the file was opened properly
// 	if (!file.is_open()) {
// 		return -1;
// 	}

// 	int n;
// 	file >> n; // read in the number of posts
// 	for (int i = 0; i < n; i++) {
// 		std::size_t id;
// 		std::string message_text;
// 		int owner_user_id;
// 		int num_likes;
// 		bool is_public;
// 		std::string author_name;

// 		file >> id;
// 		file >> message_text;
// 		file >> owner_user_id;
// 		file >> num_likes;
// 		file >> is_public;

// 		Post* p;
// 		bool incoming;
// 		std::string line;
// 		std::getline(file, line);
// 		if (line == "\n") {
// 			p = new Post(id, message_text, num_likes);
// 			incoming = false;
// 		}
// 		else {
// 			file >> author_name;
// 			p = new IncomingPost(id, message_text, num_likes, is_public, author_name);
// 			incoming = true;
// 		}

// 		// add the post
// 		std::size_t author_id = getId(author_name);
// 		addPost(id, message_text, num_likes, incoming, author_id, is_public);
// 	}
// 	return 0;
// }
