#ifndef XMLMINIFIER_H
#define XMLMINIFIER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Function declarations
string minifyXML(const string& xmlContent);
string readXMLFile(const string& fileName);
void writeXMLToFile(const string& fileName, const string& xmlContent);

#endif 
