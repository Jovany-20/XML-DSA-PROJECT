#include "mostActiveUser.h"

vector<string> mostActiveUser(const map<string, vector<string>>& users) {
   map<string, int> followerCount;  
    for (const auto& user : users) {
        for (const string& follower : user.second) {
            followerCount[follower]++;  // Increment the follower count
        }
    }

    vector<string> mostActiveUsers;
    int maxFollowers = 0;
    for (const auto& entry : followerCount) {
        if (entry.second > maxFollowers) {
            mostActiveUsers.clear();  
            mostActiveUsers.push_back(entry.first);
            maxFollowers = entry.second;
        }
        else if (entry.second == maxFollowers) {
            mostActiveUsers.push_back(entry.first);  
        }
    }

    return mostActiveUsers; 
}
