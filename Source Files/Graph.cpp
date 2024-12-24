#include "../Header Files/Graph.h" // Adjust path to include the header


void NetworkAnalysis(map<string, vector<string>>& users, vector<string> data) {
    string currentUserId = "";       // To store the current user's ID
    vector<string> followers;        // To store the followers of the current user
    bool isInsideUser = false;       // Flag to indicate if we're inside a user block
    bool isInsideFollower = false;   // Flag to indicate if we're inside a follower block

    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] == "<user>") {
            isInsideUser = true;
            currentUserId = "";      // Reset for the next user
            followers.clear();       // Clear the followers for the next user
        } else if (data[i] == "</user>") {
            isInsideUser = false;
            if (!currentUserId.empty()) {
                users[currentUserId] = followers; // Add the user and their followers to the map
            }
        } else if (data[i] == "<id>" && isInsideUser && !isInsideFollower) {
            currentUserId = data[i + 1]; // Extract the user ID
        } else if (data[i] == "<follower>") {
            isInsideFollower = true;
        } else if (data[i] == "</follower>") {
            isInsideFollower = false;
        } else if (data[i] == "<id>" && isInsideFollower) {
            followers.push_back(data[i + 1]); // Extract and store the follower ID
        }
    }
}