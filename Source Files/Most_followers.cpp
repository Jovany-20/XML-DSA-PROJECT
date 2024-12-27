#include "../Header Files/Most_followers.h"

vector<string> mostFollowers(const map<string, vector<string>>& users) {
    /*
    Function to find the users with the most followers in a given map of users and their followers

    Paramters:
    users (map<string, vector<string>>): A map of users and their followers

    Returns:
    vector<string>: A vector of users with the most followers
    */
    vector<string> mostFollowedUsers;
    size_t maxFollowers = 0;

    for (const auto& user : users) {
        size_t numFollowers = user.second.size();
        if (numFollowers > maxFollowers) {
            maxFollowers = numFollowers;
            mostFollowedUsers.clear();
            mostFollowedUsers.push_back(user.first);
        } else if (numFollowers == maxFollowers) {
            mostFollowedUsers.push_back(user.first);
        }
    }

    return mostFollowedUsers;
}