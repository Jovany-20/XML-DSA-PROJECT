#ifndef FIX_XML_H
#define FIX_XML_H

#include <string>

// Function to fix missing close tags
std::string fix_missing_close_tag(const std::string& input);

// Function to fix missing open tags
std::string fix_missing_open_tag(const std::string& input);

#endif 
