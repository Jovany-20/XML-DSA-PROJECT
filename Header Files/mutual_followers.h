#ifndef MUTUALFOLLOWERS_H
#define MUTUALFOLLOWERS_H


#include<iostream>
#include<string>
#include<stack>
#include <vector>
#include<map>
#include <algorithm>


#include "Graph.h" // Include the Graph class header

using namespace std;

// Function declaration

/*        mutualFollowersBetween_n_Users function:

        This function finds and returns the mutual followers between a given list of users.
        Parameters:
         - users: A map where the key is a user's ID (string) and the value is a vector of follower IDs (vector<string>).
         - userIds: A vector of user IDs (vector<string>) for which mutual followers are to be determined.

        Returns:
         - A string containing the IDs of the mutual followers separated by spaces. If there are no mutual followers,
           it returns "None". If there are fewer than two users in the userIds vector, it returns "Not enough users to compare."
*/
string mutualFollowersBetween_n_Users(map<string, vector<string>> users, vector<string> userIds);

#endif