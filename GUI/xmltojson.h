#ifndef XMLTOJSON_H
#define XMLTOJSON_H

#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Function to remove extra spaces, newlines, tabs, and carriage returns from the XML input.
string RemoveSpaces(string rawXML);

// Function to process an opening tag in the XML string.
string processOpeningTag(string& xmlData, int& i, stack<string>& openTags,
                         stack<string>& unmatchedTags, stack<bool>& isOpeningTag,
                         stack<string>& bracketStack, stack<int>& arrayStartIndices,
                         string& jsonResult, int& jsonIndex, int& arrayIndex,
                         string& lastClosedTag, string& lastBracket);

// Function to process a closing tag in the XML string.
void processClosingTag(string& xmlData, int& i, stack<string>& unmatchedTags,
                       stack<bool>& isOpeningTag, stack<string>& bracketStack,
                       string& jsonResult, int& jsonIndex, stack<int>& arrayStartIndices,
                       string& lastClosedTag, string& lastBracket, int& arrayIndex);

// Function to process the data content between XML tags.
void processData(string& xmlData, int& i, string& jsonResult, int& jsonIndex);

// Function to convert XML string data into a JSON string format.
string convertXMLToJSON(string xmlData);

#endif // XMLTOJSON_H
