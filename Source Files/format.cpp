#include "../Header Files/format.h" // Adjust path to include the header
#include "../Header Files/Tree.h"   // Include Tree class header from the correct folder

string format (string xmlData){
    /////////////////// this is the function used in the gui/////////////////////////
        // @breif this function takes an unformatted xml string and return the formatted string
        // @param xmlData as a string 
        // @return formatted xml string
   vector<string> parsingxml= parseXML(xmlData);
   Tree * xmlTREE = buildTree(parsingxml);
   return formatXML(xmlTREE, 0);

}



vector<string> parseXML(const string& input) {
    /*  @breif this function parses the xml string into tokens and saves it as a vector with opening and closing tags
               and contents of the xml file
        @param input string of the unformatted xml file 
        @return vector of tokens of scanned xml file
    */
    vector<string> result;
    size_t pos = 0;
    size_t len = input.length();

    while (pos < len) {
        // Find the next tag
        size_t tagStart = input.find('<', pos);

        if (tagStart == string::npos) {
          
            break;  // End of parsing
        }

        // If there's text before the tag, capture it
        if (tagStart > pos) {
            string textBeforeTag = input.substr(pos, tagStart - pos);
            textBeforeTag.erase(0, textBeforeTag.find_first_not_of(" \n\t"));  // Trim leading spaces
            textBeforeTag.erase(textBeforeTag.find_last_not_of(" \n\t") + 1);  // Trim trailing spaces
            // Remove all occurrences of '\n' and '\t' from the middle of the string
            textBeforeTag.erase(std::remove(textBeforeTag.begin(), textBeforeTag.end(), '\n'), textBeforeTag.end());
            textBeforeTag.erase(std::remove(textBeforeTag.begin(), textBeforeTag.end(), '\t'), textBeforeTag.end());

            if (!textBeforeTag.empty()) {
                result.push_back(textBeforeTag);
            }
        }

        
        size_t tagEnd = input.find('>', tagStart);
        

        string tag = input.substr(tagStart, tagEnd - tagStart + 1);  // Include the '>'
        result.push_back(tag);

        // Move the position past the tag
        pos = tagEnd + 1;
    }

    return result;
}





Tree* buildTree(const vector<string>& xmlStrings) {
    /* this function takes in the string vector containing the xml tokens
    (opening tags,closing tag or content) and turns it into a tree where 
    each node is an opening tag and the content is root node and closing tag is 
    ignored for it to become a proper tree.  */
  
    stack<Tree*> nodeStack;   // Stack to keep track of current node hierarchy
    Tree* root = nullptr;     // Root of the tree

    for (const string& str : xmlStrings) {
        if (str[0] == '<') {
            if (str[1] == '/') {
                // Closing tag: pop from stack
                nodeStack.pop();
            }
            else {
                // Opening tag: create a new node
                string tag = str.substr(1, str.find('>') - 1); // Extract the tag name
                Tree* newNode = new Tree(tag);

                if (nodeStack.empty()) {
                    // If the stack is empty, this node is the root
                    root = newNode;
                }
                else {
                    // Otherwise, add it as a child of the current top node
                    nodeStack.top()->addChild(newNode);
                }
                nodeStack.push(newNode);
            }
        }
        else {
            // Content: create a leaf node
            Tree* contentNode = new Tree(str);

            // Add it as a child of the current top node
            if (!nodeStack.empty()) {
                nodeStack.top()->addChild(contentNode);
            }
        }
    }

    return root;
}





string formatXML(Tree* node, int depth ) {
/*this function is used to turn the tree back to a string with the proper
indentation depending on the level of the node using recursion*/
    if (!node) {  return ""; }
    string outFile = "";
    // Print the current node value with indentation
    if(size(node->pointers))
    outFile += string(depth * 4, ' ') + "<" + node->val +">" + "\n";
    else {
        stringstream ss(formatWithTabsAndWordWrap(node->val, 40));
        string line;

        // Write each line with the spaces applied
        while (getline(ss, line)) {
            outFile += string(depth * 4, ' ') + line + "\n";
        }
    }
    // Recursively print child nodes
    for (Tree* child : node->pointers) {
        outFile+= formatXML(child, depth + 1);
    }
    if (size(node->pointers)) outFile += string(depth * 4, ' ') + "</" + node->val + ">" + "\n";
    return outFile;
}



string formatWithTabsAndWordWrap(const string& str, size_t width) {
    /*
        @breif this is a helper function that turns a long string (the posts ) into formatted multilines string with a certain width size
        @param str the string post 
        @param width width of each line (set to 40 when you call this function)
        @return a string that contains multi line string
    */
    istringstream stream(str); // Split the string into words
    string word;
    string currentLine = ""; // Start each line with a tab
    string result; // Store the formatted string

    while (stream >> word) {
        // Check if adding the word exceeds the line width
        if (currentLine.length() + word.length() + 1 > width) {
            result += currentLine + "\n"; // Add the current line to the result with a newline
            currentLine =  word; // Start a new line with the current word
        }
        else {
            // Add the word to the current line
            if (currentLine != "\t") {
               if(size(currentLine))  currentLine += " "; // Add a space between words
                
            }
            currentLine += word;
        }
    }

    // Add the last line to the result if it contains text
    if (!currentLine.empty()) {
        result += currentLine;
    }

    return result;
}

