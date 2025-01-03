#include "..\Header Files\minifying.h"
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

