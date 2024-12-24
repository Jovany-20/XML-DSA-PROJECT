#ifndef GRAPH_H
#define GRAPH_H

#include "../Header Files/format.h" // Adjust path to include the header
#include "../Header Files/Tree.h"   // Include Tree class header from the correct folder
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <unordered_map>
#include <stack>
#include <algorithm>
using namespace std;


class Node {
public:
    int id;                                         // User ID
    vector<shared_ptr<Node>> followers;             // List of followers (shared_ptr)

    // Constructor
    Node(int userId) : id(userId) {}

    // Add follower
    void addFollower(const shared_ptr<Node>& follower) {
        followers.push_back(follower);
    }
};

vector<shared_ptr<Node>> graphMaker(const string& XML);
#endif // GRAPH_H