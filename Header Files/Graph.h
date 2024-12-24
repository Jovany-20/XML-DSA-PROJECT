#ifndef GRAPH_H
#define GRAPH_H

#include "../Header Files/format.h" // Adjust path to include the header

#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <map>
using namespace std;

// Function declarations
void NetworkAnalysis(map<string, vector<string>>& users, vector<string> data);
#endif // GRAPH_H