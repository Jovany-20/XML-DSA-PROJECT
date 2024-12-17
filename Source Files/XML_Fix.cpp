#include "../Header Files/XML_Fix.h"
#include <stack>

std::string fix_missing_close_tag(const std::string& input) {
    std::stack<std::string> tagStack;
    std::string correctedString;
    std::string currentTag;
    bool insideTag = false;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if (c == '<') {
            insideTag = true;
            currentTag = "<";
        } else if (c == '>') {
            insideTag = false;
            currentTag += c;

            if (currentTag[1] == '/') {
                std::string closingTag = currentTag.substr(2, currentTag.length() - 3);
                if (!tagStack.empty() && tagStack.top() == closingTag) {
                    correctedString += currentTag;
                    tagStack.pop();
                } else {
                    if (!tagStack.empty()) {
                        std::string expectedTag = tagStack.top();
                        correctedString += "</" + expectedTag + ">";
                        tagStack.pop();
                    }
                }
            } else {
                std::string openingTag = currentTag.substr(1, currentTag.length() - 2);
                tagStack.push(openingTag);
                correctedString += currentTag;
            }
        } else if (insideTag) {
            currentTag += c;
        } else {
            correctedString += c;
        }
    }

    while (!tagStack.empty()) {
        std::string unclosedTag = tagStack.top();
        correctedString += "</" + unclosedTag + ">";
        tagStack.pop();
    }

    return correctedString;
}

std::string fix_missing_open_tag(const std::string& input) {
    std::stack<std::string> tagStack;      // To track opened tags
    std::string correctedString;      // To store the corrected string
    std::string currentTag;           // To store the current tag being processed
    bool insideTag = false;      // Flag to track if inside a tag

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if (c == '<') {
            // Starting a tag
            insideTag = true;
            currentTag = "<";
        } else if (c == '>') {
            // Ending a tag
            insideTag = false;
            currentTag += c;

            if (currentTag[1] == '/') {
                // It's a closing tag
                std::string closingTag = currentTag.substr(2, currentTag.length() - 3); // Extract tag name
                if (!tagStack.empty() && tagStack.top() == closingTag) {
                    // Valid match, pop the stack and add the closing tag
                    tagStack.pop();
                    correctedString += currentTag;
                } else {
                    // Missing opening tag case: Add the opening tag before the closing tag
                    correctedString += "<" + closingTag + ">" + currentTag;
                }
            } else {
                // It's an opening tag
                std::string openingTag = currentTag.substr(1, currentTag.length() - 2); // Extract tag name
                tagStack.push(openingTag);
                correctedString += currentTag;
            }
        } else if (insideTag) {
            // Inside a tag, accumulate characters
            currentTag += c;
        } else {
            // Outside a tag, copy character to the output
            correctedString += c;
        }
    }

    // Handle any remaining unclosed tags in the stack
    while (!tagStack.empty()) {
        std::string unclosedTag = tagStack.top();
        correctedString += "</" + unclosedTag + ">"; // Close remaining tags properly
        tagStack.pop();
    }

    return correctedString;
}
