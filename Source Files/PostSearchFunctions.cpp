#include "SearchFunctions.h"
#include <regex>
#include <sstream>

using namespace std;

string searchWord(const string& word, const string& input) {
    /*
    This function is used to search for a specific word inside the body content of an XML string.
    It uses regular expressions to extract the contents inside `<body>` tags and checks if the 
    specified word is present in any of the `<body>` sections.

    Parameters:
    word (const std::string&): The word to search for in the body content.
    input (const std::string&): The XML string containing the `<body>` sections.

    Returns:
    std::string: A result string containing all the body sections where the word is found.
                 If no matches are found, it returns "No matches found."
*/
    string result;
    regex bodyRegex(R"(<body[^>]*>([\s\S]*?)</body>)", regex::icase);
    smatch match;

    result += "Bodies mentioning the word \"" + word + "\":\n";

    string::const_iterator searchStart(input.cbegin());
    bool found = false;

    while (regex_search(searchStart, input.cend(), match, bodyRegex)) {
        string bodyContent = match[1].str(); // Extract the content inside <body> tags

        if (bodyContent.find(word) != string::npos) {
            result += bodyContent + "\n";
            found = true;
        }

        searchStart = match.suffix().first; // Advance to the next match
    }

    return found ? result : "No matches found.\n";
}

string searchTopic(const string& topic, const string& input) {
    string result;
    regex postRegex(R"(<post>([\s\S]*?)</post>)", regex::icase); // Match entire <post> blocks
    regex topicRegex(R"(<topic[^>]*>(.*?)</topic>)", regex::icase); // Match individual <topic> tags
    smatch postMatch;

    result += "Posts mentioning the topic \"" + topic + "\":\n";

    string::const_iterator searchStart(input.cbegin());
    bool found = false;
    int postNumber = 0;

    while (regex_search(searchStart, input.cend(), postMatch, postRegex)) {
        string postContent = postMatch[1].str(); // Extract the full content of the <post>

        // Check if the topic is mentioned in this post
        smatch topicMatch;
        string::const_iterator topicSearchStart(postContent.cbegin());
        while (regex_search(topicSearchStart, postContent.cend(), topicMatch, topicRegex)) {
            if (topicMatch[1].str() == topic) {
                postNumber++;
                result += "Post " + to_string(postNumber) + ":\n" + postContent + "\n\n";
                found = true;
                break; // Stop checking topics in this post once the topic is found
            }
            topicSearchStart = topicMatch.suffix().first;
        }

        searchStart = postMatch.suffix().first; // Move to the next post
    }

    return found ? result : "No posts found for the topic \"" + topic + "\".\n";
}
