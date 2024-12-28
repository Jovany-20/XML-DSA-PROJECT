
vector<string> suggestUsersToFollow(map<string, vector<string>> users, string userId) {

    if (users.find(userId) == users.end()) {
        return {}; // User does not exist, return an empty list
    }


    vector<string> currentFollowers = users[userId]; // the user's current followers
    set<string> suggestions; // a set to store suggestions without duplicates

    // Loop through all other users
    for (map<string, vector<string>>::iterator it = users.begin(); it != users.end(); ++it) {
        string otherUserId = it->first;                 // the user ID
        vector<string> otherFollowers = it->second;     // the followers

        if (otherUserId == userId) continue;            // Skip the current user

        // Check for shared followers
        for (vector<string>::iterator followerIt = currentFollowers.begin(); followerIt != currentFollowers.end(); ++followerIt)
        {
            if (find(otherFollowers.begin(), otherFollowers.end(), *followerIt) != otherFollowers.end())
            {
                suggestions.insert(otherUserId);        // Add this user as a suggestion as it has a similar connections to the main user
                break;
            }
        }
    }

    vector <string> SuggestionsVector= vector<string>(suggestions.begin(), suggestions.end());
    return SuggestionsVector;
}
