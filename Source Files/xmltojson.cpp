
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


    string tempWord = "";
    string currentChar = std::string(1, xmlData[i]);



    while (currentChar != ">") {
        tempWord += currentChar;
        i++;
        currentChar = std::string(1, xmlData[i]); // Fixed issue here
    }

    if (tempWord == lastClosedTag) {
        jsonResult.erase(arrayIndex - ((bracketStack.size() + 1)) - 2, tempWord.length() + 6 + ((bracketStack.size() + 1)));
        jsonIndex -= (tempWord.length() + 6 + ((bracketStack.size() + 1)));
        jsonResult.insert(arrayIndex - ((bracketStack.size() + 1)) - 2, "[\n");
        jsonIndex += 2;
        bracketStack.pop();
        bracketStack.push("]");
        if (!arrayStartIndices.empty()) {
            arrayStartIndices.pop();
            if (!arrayStartIndices.empty()) {
                arrayIndex = arrayStartIndices.top();
            }
        }
        i++;
        openTags.push(tempWord);
        unmatchedTags.push(tempWord);
        isOpeningTag.push(true);
        jsonResult += "\n";
        jsonIndex++;
        return tempWord;
    }

    if (openTags.empty()) {
        jsonResult += "\n";
    }
    else if (!isOpeningTag.top()) {
        jsonResult += "\n";
        jsonIndex++;
    }
    else {
        for (int t = bracketStack.size() + 1; t > 0; t--) {
            jsonResult += " ";
            jsonIndex++;
        }
        jsonResult += "{\n";
        jsonIndex += 2;

        if (tempWord + "s" == openTags.top()) {
            arrayIndex = jsonIndex + bracketStack.size() + 3;
            arrayStartIndices.push(arrayIndex);
        }
        bracketStack.push("}");
    }

    for (int t = bracketStack.size() + 1; t > 0; t--) {
        jsonResult += " ";
        jsonIndex++;
    }
    jsonResult += "\"" + tempWord + "\": ";
    jsonIndex += tempWord.length() + 4;

    openTags.push(tempWord);
    unmatchedTags.push(tempWord);
    isOpeningTag.push(true);
    i++;
    return tempWord;
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
    string tempWord = "";
    string currentChar = std::string(1, xmlData[i]); // Fixed issue here

    while (currentChar != ">") {
        i++;
        currentChar = std::string(1, xmlData[i]); // Fixed issue here
        tempWord += currentChar;
    }
    tempWord.pop_back();

    if (tempWord == unmatchedTags.top()) {
        lastClosedTag = tempWord;
        unmatchedTags.pop();

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

    if (!isOpeningTag.top()) {
        string back = std::string(1, jsonResult.back()); // Fixed issue here

        if ((bracketStack.top() == "]" && lastBracket == "}") ||
            (bracketStack.top() == "}" && back == ",") ||
            (bracketStack.top() == "]" && back == ",")) {
            jsonResult.pop_back();
            jsonIndex--;
        }
        jsonResult += "\n";
        jsonIndex++;

        for (int t = bracketStack.size(); t > 0; t--) {
            jsonResult += " ";
            jsonIndex++;
        }
        jsonResult += bracketStack.top();
        lastBracket = bracketStack.top();
        jsonIndex++;
        bracketStack.pop();
        if (!bracketStack.empty()) {
            jsonResult += ",";
            jsonIndex++;
        }
    }
    i++;
    isOpeningTag.push(false);
}
