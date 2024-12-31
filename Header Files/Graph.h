#ifndef GRAPH_H
#define GRAPH_H

#include "../Header Files/format.h" // Adjust path to include the header

#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <map>
using namespace std;


// Declare the global map
// Map to store the user ID , 
//this will get filled by visulize function (will call NetworkAnalysis)
//and rest of tasks will only use this map drectly yo save memory.
extern map<string, vector<string>> global_map; 

// Function declarations
// the visulize function will call this function to fill the global map 
// like this : NetworkAnalysis(global_map, data);
// it should be called only once by the visulize function. 
// it must pass the global map to the map parameter.
void NetworkAnalysis(map<string, vector<string>>& users, vector<string> data);
#endif // GRAPH_H