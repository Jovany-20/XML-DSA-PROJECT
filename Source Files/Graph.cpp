#include "../Header Files/Graph.h" // Adjust path to include the header


vector<shared_ptr<Node>> graphMaker(const string& XML) {
    /* @brief This function builds a graph from an XML string representing users and their relationships.
       @param XML string containing the XML data.
       @return A vector of shared_ptr<Node> representing the users in the graph.
    */

    vector<string> parsingxml = parseXML(XML);
    Tree* xmlTree = buildTree(parsingxml);

    vector<shared_ptr<Node>> nodes;                     // List of user nodes
    unordered_map<int, shared_ptr<Node>> idToNodeMap;   // Map to store users by ID for quick lookup

    // Find the <users> node
    Tree* usersNode = nullptr;
    for (Tree* child : xmlTree->pointers) {
        if (child->val == "users") {
            usersNode = child;
            break;
        }
    }

    if (!usersNode) {
        cout << "No <users> tag found in XML." << endl;
        delete xmlTree;
        return {};
    }

    // Iterate over each <user> node
    for (Tree* userNode : usersNode->pointers) {
        if (userNode->val != "user") continue;

        int userId = -1;
        vector<int> followerIds;

        // Extract user details
        for (Tree* userDetailNode : userNode->pointers) {
            if (userDetailNode->val == "id") {
                // Get user ID
                if (!userDetailNode->pointers.empty()) {
                    userId = stoi(userDetailNode->pointers[0]->val);
                }
            }
            else if (userDetailNode->val == "followers") {
                // Get followers
                for (Tree* followerNode : userDetailNode->pointers) {
                    if (followerNode->val == "follower") {
                        for (Tree* followerDetailNode : followerNode->pointers) {
                            if (followerDetailNode->val == "id") {
                                if (!followerDetailNode->pointers.empty()) {
                                    int followerId = stoi(followerDetailNode->pointers[0]->val);
                                    followerIds.push_back(followerId);
                                }
                            }
                        }
                    }
                }
            }
        }

        if (userId != -1) {
            // Create a new Node for the user if it doesn't exist
            shared_ptr<Node> userNodePtr;
            if (idToNodeMap.find(userId) == idToNodeMap.end()) {
                userNodePtr = make_shared<Node>(userId);
                idToNodeMap[userId] = userNodePtr;
                nodes.push_back(userNodePtr);
            }
            else {
                userNodePtr = idToNodeMap[userId];
            }

            // Add followers to the user
            for (int followerId : followerIds) {
                // Get or create follower node
                shared_ptr<Node> followerNode;
                if (idToNodeMap.find(followerId) == idToNodeMap.end()) {
                    followerNode = make_shared<Node>(followerId);
                    idToNodeMap[followerId] = followerNode;
                    nodes.push_back(followerNode);
                }
                else {
                    followerNode = idToNodeMap[followerId];
                }

                userNodePtr->addFollower(followerNode);
            }
        }
    }

    // Clean up the XML tree
    delete xmlTree;

    return nodes;
}