#include "../Header Files/format.h" // Adjust path to include the header
#include "../Header Files/Tree.h"   // Include Tree class header from the correct folder

string format (string xmlData){
    /////////////////// this is the function used in the gui/////////////////////////
        // @breif this function takes an unformatted xml string and return the formatted string
        // @param xmlData as a string 
        // @output formatted xml string
   vector<string> parsingxml= parseXML(xmlData);
   Tree * xmlTREE = buildTree(parsingxml);
   return formatXML(xmlTREE, 0);

}