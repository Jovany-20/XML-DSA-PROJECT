#ifndef XML_VALIDATOR_H
#define XML_VALIDATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// Global vectors
extern vector<string> tokens;
extern vector<int> tokensLines;
extern vector<int> tokensIndex;

extern vector<string> errors_found;
extern vector<int> errors_locations;
extern vector<int> errors_index;
extern vector<int> error_type;

// Function declarations
void XMLTags(string input);
void ERROR_VIEWER(vector<string> errors_found, vector<int> errors_locations, vector<int> error_type);
string readXMLFile(const string& fileName);
bool ValidateXML(string input);


#endif // XML_VALIDATOR_H
