#ifndef SEARCHFUNCTIONS_H
#define SEARCHFUNCTIONS_H

#include <string>
#include <iostream>
// Function to search for a word inside the body content of the XML
std::string searchWord(const std::string& word, const std::string& input);

// Function to search for posts mentioning a specific topic inside the XML
std::string searchTopic(const std::string& topic, const std::string& input);

#endif // SEARCHFUNCTIONS_H