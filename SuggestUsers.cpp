/* 
    -SuggestUsersToFollow Function :
         -inputs : hashmap users "the network graph that contains the users and their connections to each others"
                   String UserId argument that specifies which user in the graph or the hashmap that we want to find his suggested users 

        -How the function works ?
        it iterates over the hashmap/graph ->first iterator : the key (every single user , string users) and see his following users in 
        the ->second iterator : the value (vector<string> users)
        compare if their is any mutual connection between userId and the user in otherUserId  
        if any mutual connection found then this otherUserId will be pushed to set<string>suggestions as a suggested user.

        -Output : vector<string> suggested users that contains all the suggested user to the given user in the arguments userId
*/
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
