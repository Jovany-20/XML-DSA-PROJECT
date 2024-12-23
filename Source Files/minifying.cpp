#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;  
/*
    This function removes unnecessary whitespace outside XML tags.

    Parameters:
    xmlContent (const string&): The input XML string to be minified.

    Returns:
    string: The minified XML content.
*/
string minifyXML(const string& xmlContent) {
    string minifiedContent;
    bool insideTag = false;

    for (size_t i = 0; i < xmlContent.size(); i++) {
        char currentChar = xmlContent[i];

        if (currentChar == '<') {
            insideTag = true;
            minifiedContent += currentChar;
        } else if (currentChar == '>') {
            insideTag = false;
            minifiedContent += currentChar;
        } else if (insideTag) {
            minifiedContent += currentChar;
        } else if (!insideTag) {
            if (!(isspace(currentChar) && (minifiedContent.empty() || minifiedContent.back() == '>'))) {
                minifiedContent += currentChar;
            }
        }
    }

    return minifiedContent;
}

/*
    This function reads the content of an XML file into a string.

    Parameters:
    fileName (const string&): The name of the file to be read.

    Returns:
    string: The content of the file as a string.
*/
string readXMLFile(const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error: Unable to open input file: " << fileName << endl;
        return "";
    }

    ostringstream buffer;
    buffer << inFile.rdbuf();
    return buffer.str();
}

/*
    This function writes the minified XML content to an output file.

    Parameters:
    fileName (const string&): The name of the output file.
    xmlContent (const string&): The minified XML content to write.

    Returns:
    void
*/
void writeXMLToFile(const string& fileName, const string& xmlContent) {
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error: Unable to open output file: " << fileName << endl;
        return;
    }

    outFile << xmlContent;
    outFile.close();
    cout << "XML Minification complete. Minified file: " << fileName << endl;
}

/*
    Main function to handle XML minification from input to output files.

    Parameters:
    None

    Returns:
    int: Exit status (0 for success, 1 for failure).
*/
int main() {
    string inputFileName = "input.xml";
    string outputFileName = "output.xml";

    string xmlContent = readXMLFile(inputFileName);
    if (xmlContent.empty()) {
        return 1;
    }

    string minifiedContent = minifyXML(xmlContent);

    writeXMLToFile(outputFileName, minifiedContent);

    return 0;
}
