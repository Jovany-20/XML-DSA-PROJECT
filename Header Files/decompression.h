#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>

// Function to decode a list of codes using LZW algorithm
bool decodeFromFile(const std::string& fileName);

#endif 
