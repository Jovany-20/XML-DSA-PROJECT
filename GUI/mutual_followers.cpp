#include "../Header Files/mutual_followers.h"

//  mutualFollowers function
string mutualFollowersBetween_n_Users(map<string, vector<string>> users, vector<string> userIds) {
/*        mutualFollowersBetween_n_Users function:

        This function finds and returns the mutual followers between a given list of users.
        Parameters:
         - users: A map where the key is a user's ID (string) and the value is a vector of follower IDs (vector<string>).
         - userIds: A vector of user IDs (vector<string>) for which mutual followers are to be determined.

        Returns:
         - A string containing the IDs of the mutual followers separated by spaces. If there are no mutual followers,
           it returns "None". If there are fewer than two users in the userIds vector, it returns "Not enough users to compare."
*/
    string mutual;

    // Ensure there are at least two users to compare
    if (userIds.size() < 2) {
        return "Not enough users to compare.";
    }

    // Start with the followers of the first user
    vector<string> commonFollowers = users[userIds[0]];

    // Compare with the followers of each subsequent user
    for (size_t i = 1; i < userIds.size(); ++i) {
        vector<string> currentFollowers = users[userIds[i]];
        vector<string> temp;

        // Find common followers between commonFollowers and currentFollowers
        for (const auto& follower1 : commonFollowers) {
            for (const auto& follower2 : currentFollowers) {
                if (follower1 == follower2) {
                    temp.push_back(follower1);
                    break;
                }
            }
        }

        // Update commonFollowers to the intersection found so far
        commonFollowers = temp;
    }

    // Prepare the result
    if (commonFollowers.empty()) {
        return "None";
    }

    for (const auto& follower : commonFollowers) {
        mutual += follower + " ";
    }

    return mutual;
}








