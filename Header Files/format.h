#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <condition_variable>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>
#include <memory>
#include <stack>
#include "Tree.h" // Include the Tree class header

using namespace std;

// Function declarations
vector<string> parseXML(const string& input);
string formatWithTabsAndWordWrap(const std::string& str, size_t width);
Tree* buildTree(const vector<string>& xmlStrings);
string formatXML(Tree* node, int depth);

#endif // FORMAT_H
