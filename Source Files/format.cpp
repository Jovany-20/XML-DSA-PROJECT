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

