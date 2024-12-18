#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>

// save to file the encoded code 
bool encodeAndSave(const std::string& input, const std::string& fileName);

#endif 
