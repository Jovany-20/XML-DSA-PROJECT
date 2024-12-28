
vector<string> suggestUsersToFollow(map<string, vector<string>> users, string userId) {
    
    /* 
    -SuggestUsersToFollow Function :

         This function is used to find the suggested user to a specific user by finding the mutual connections between them,

         
         Parameters :
                    users (map<string, vector<string>> : hashmap "the network graph that contains the users and their connections to each others".
                    UserId (string) argument that specifies which user in the graph or the hashmap that we want to find his suggested users .

        
        -Returns : vector<string> suggested users
    */
    

    if (users.find(userId) == users.end()) {
        return {}; // User does not exist, return an empty list
    }


    vector<string> currentFollowers = users[userId]; // the user's current followers
    set<string> suggestions; // a set to store suggestions without duplicates

    // Loop through all other users
     // it iterates over the hashmap/graph ->first iterator : the key (every single user , string users) and see his following users in 
     //the ->second iterator : the value (vector<string> users)
    for (map<string, vector<string>>::iterator it = users.begin(); it != users.end(); ++it) {
        string otherUserId = it->first;                 // the user ID
        vector<string> otherFollowers = it->second;     // the followers

        if (otherUserId == userId) continue;            // Skip the current user

        // Check for shared followers
        //compare if their is any mutual connection between userId and the user in otherUserId string 
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
