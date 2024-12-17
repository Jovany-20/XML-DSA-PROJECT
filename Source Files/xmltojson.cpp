
#include "../Header Files/xmltojson.h"

string processOpeningTag(string& xmlData, int& i, stack<string>& openTags,
    stack<string>& unmatchedTags, stack<bool>& isOpeningTag,
    stack<string>& bracketStack, stack<int>& arrayStartIndices,
    string& jsonResult, int& jsonIndex, int& arrayIndex,
    string& lastClosedTag, string& lastBracket) {


/*
This Function processes an opening tag in the XML string, updates the JSON result string, and manages various stacks that track open tags, unmatched tags, and formatting states.

Parameters:
- xmlData (string&): The input XML string being processed.
- i (int&): The current index being read from the XML string.
- openTags (stack<string>&): Stack storing currently open XML tags.
- unmatchedTags (stack<string>&): Stack storing unmatched XML tags.
- isOpeningTag (stack<bool>&): Stack indicating whether the last tag processed was an opening tag.
- bracketStack (stack<string>&): Stack managing the brackets used for JSON formatting ("{" and "}").
- arrayStartIndices (stack<int>&): Stack storing indices for array elements in the JSON result.
- jsonResult (string&): The resulting JSON string being built.
- jsonIndex (int&): The current index of the JSON string being modified.
- arrayIndex (int&): The start index of the current JSON array.
- lastClosedTag (string&): The last tag that was closed in the XML.
- lastBracket (string&): The last bracket inserted into the JSON string.

Returns:
- string: The name of the opening tag that was processed.
*/

    string tempWord = ""; // Temporary variable to store the tag name
    string currentChar = std::string(1, xmlData[i]); // Read the current character

    // Loop to read the tag name until '>' is encountered
    while (currentChar != ">") {
        tempWord += currentChar; // Append character to the tag name
        i++; // Move to the next character
        currentChar = std::string(1, xmlData[i]);
    }

    // Check if the current tag is the last closed tag
    if (tempWord == lastClosedTag) {
        // Remove the redundant tag content and replace it with an array bracket '['
        jsonResult.erase(arrayIndex - ((bracketStack.size() + 1)) - 2, tempWord.length() + 6 + ((bracketStack.size() + 1)));
        jsonIndex -= (tempWord.length() + 6 + ((bracketStack.size() + 1)));
        jsonResult.insert(arrayIndex - ((bracketStack.size() + 1)) - 2, "[\n");
        jsonIndex += 2;

        bracketStack.pop();      // Pop the last bracket
        bracketStack.push("]");  // Replace with a closing square bracket ']'

        // Manage array indices for JSON arrays
        if (!arrayStartIndices.empty()) {
            arrayStartIndices.pop();
            if (!arrayStartIndices.empty()) {
                arrayIndex = arrayStartIndices.top();
            }
        }

        i++; // Move past the closing '>'
        openTags.push(tempWord);       // Push the tag onto the open tags stack
        unmatchedTags.push(tempWord);  // Push to unmatched tags
        isOpeningTag.push(true);       // Mark it as an opening tag
        jsonResult += "\n";
        jsonIndex++;
        return tempWord; // Return the tag name
    }

    // Add a new line if open tags stack is empty
    if (openTags.empty()) {
        jsonResult += "\n";
    }
    // Otherwise, check if the previous tag was not an opening tag
    else if (!isOpeningTag.top()) {
        jsonResult += "\n";
        jsonIndex++;
    }
    // Handle formatting for nested tags
    else {
        for (int t = bracketStack.size() + 1; t > 0; t--) {
            jsonResult += " "; // Add appropriate indentation
            jsonIndex++;
        }
        jsonResult += "{\n"; // Start a new JSON object
        jsonIndex += 2;

        // Check if the current tag indicates the start of a JSON array
        if (tempWord + "s" == openTags.top()) {
            arrayIndex = jsonIndex + bracketStack.size() + 3;
            arrayStartIndices.push(arrayIndex);
        }
        bracketStack.push("}"); // Push closing curly bracket
    }

    // Add the tag name as a JSON key
    for (int t = bracketStack.size() + 1; t > 0; t--) {
        jsonResult += " ";
        jsonIndex++;
    }
    jsonResult += "\"" + tempWord + "\": ";
    jsonIndex += tempWord.length() + 4;

    openTags.push(tempWord);       // Push the tag onto the open tags stack
    unmatchedTags.push(tempWord);  // Mark it as unmatched
    isOpeningTag.push(true);       // Mark it as an opening tag
    i++; // Move past the closing '>'
    return tempWord; // Return the tag name
}

void processClosingTag(string& xmlData, int& i, stack<string>& unmatchedTags, stack<bool>& isOpeningTag,
    stack<string>& bracketStack, string& jsonResult, int& jsonIndex,
    stack<int>& arrayStartIndices, string& lastClosedTag, string& lastBracket,
    int& arrayIndex) {

/*
This Function processes a closing tag in the XML string, updates the JSON result string, and ensures proper handling of unmatched tags, brackets, and arrays.

Parameters:
- xmlData (string&): The input XML string being processed.
- i (int&): The current index being read from the XML string.
- unmatchedTags (stack<string>&): Stack storing unmatched XML tags.
- isOpeningTag (stack<bool>&): Stack indicating whether the last tag processed was an opening tag.
- bracketStack (stack<string>&): Stack managing the brackets used for JSON formatting ("{" and "}").
- jsonResult (string&): The resulting JSON string being built.
- jsonIndex (int&): The current index of the JSON string being modified.
- arrayStartIndices (stack<int>&): Stack storing indices for array elements in the JSON result.
- lastClosedTag (string&): The last tag that was closed in the XML.
- lastBracket (string&): The last bracket inserted into the JSON string.
- arrayIndex (int&): The start index of the current JSON array.

Returns:
- void
*/

    string tempWord = ""; // Temporary variable to store the tag name
    string currentChar = std::string(1, xmlData[i]);

    // Loop to read the tag name until '>' is encountered
    while (currentChar != ">") {
        i++;
        currentChar = std::string(1, xmlData[i]);
        tempWord += currentChar;
    }
    tempWord.pop_back(); // Remove the trailing '>'

    // Check if the tag matches the last unmatched tag
    if (tempWord == unmatchedTags.top()) {
        lastClosedTag = tempWord; // Update the last closed tag
        unmatchedTags.pop();      // Remove it from the unmatched tags stack

        // Handle array elements
        int count = lastClosedTag.length();
        string currentWord = std::string(1, jsonResult[arrayIndex + 1]);
        for (int L = arrayIndex + 2; L < arrayIndex + count; L++) {
            currentWord += jsonResult[L];
        }
        if (currentWord + "s" == lastClosedTag) {
            arrayStartIndices.pop();
            if (!arrayStartIndices.empty()) {
                arrayIndex = arrayStartIndices.top();
            }
        }
    }

    // Check formatting for closing tags
    if (!isOpeningTag.top()) {
        string back = std::string(1, jsonResult.back()); // Get the last character in JSON

        // Remove unnecessary trailing commas or spaces
        if ((bracketStack.top() == "]" && lastBracket == "}") ||
            (bracketStack.top() == "}" && back == ",") ||
            (bracketStack.top() == "]" && back == ",")) {
            jsonResult.pop_back();
            jsonIndex--;
        }
        jsonResult += "\n";
        jsonIndex++;

        // Add indentation and the closing bracket
        for (int t = bracketStack.size(); t > 0; t--) {
            jsonResult += " ";
            jsonIndex++;
        }
        jsonResult += bracketStack.top(); // Insert the correct bracket
        lastBracket = bracketStack.top();
        jsonIndex++;
        bracketStack.pop(); // Remove the last bracket

        // Add a trailing comma if needed
        if (!bracketStack.empty()) {
            jsonResult += ",";
            jsonIndex++;
        }
    }

    i++; // Move past the closing '>'
    isOpeningTag.push(false); // Mark it as a closing tag
}

