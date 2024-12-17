
#include "../Header Files/xmltojson.h"

string processOpeningTag(string& xmlData, int& i, stack<string>& openTags,
    stack<string>& unmatchedTags, stack<bool>& isOpeningTag,
    stack<string>& bracketStack, stack<int>& arrayStartIndices,
    string& jsonResult, int& jsonIndex, int& arrayIndex,
    string& lastClosedTag, string& lastBracket) {
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
