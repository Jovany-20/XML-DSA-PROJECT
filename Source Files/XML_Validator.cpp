#include "..\Header Files\XML_Validor.h"

vector<int> tokensLines;
vector<int> tokensIndex;
vector<string> tokens;
vector<string> errors_found;
vector<int> errors_locations;
vector<int> errors_index;
vector<int> error_type;

bool ValidateXML(string input) {
    /*
    This Function is used to validate the XML tags in the input string

    Parameters:
    input (string): The input string containing the XML tags

    Returns:
    bool: True if the XML tags are valid, False otherwise
     */
    XMLTags(input);
    errors_found.clear();
    errors_locations.clear();
    errors_index.clear();
    error_type.clear();

    stack<string> st_validate_tokens;
    stack<int> st_validate_tokensLines;
    stack<int> st_validate_tokensIndex;

    for (int i = 0; i < tokens.size(); i++) {
        string this_token = tokens[i];
        int this_token_index = tokensIndex[i];
        int this_token_line = tokensLines[i];

        if (this_token[0] == '<' && this_token[1] != '/') {
            st_validate_tokens.push(this_token);
            st_validate_tokensLines.push(this_token_line);
            st_validate_tokensIndex.push(this_token_index);
        } else if (this_token[1] == '/') {
            if (st_validate_tokens.empty()) {
                errors_found.push_back(this_token);
                errors_locations.push_back(this_token_line);
                errors_index.push_back(this_token_index);
                error_type.push_back(1);
            } else {
                string stackTop = st_validate_tokens.top();
                if (this_token.substr(2, this_token.length() - 3) == stackTop.substr(1, stackTop.length() - 2)) {
                    st_validate_tokens.pop();
                    st_validate_tokensLines.pop();
                    st_validate_tokensIndex.pop();
                } else {
                    errors_found.push_back(this_token);
                    errors_locations.push_back(this_token_line);
                    errors_index.push_back(this_token_index);
                    error_type.push_back(1);
                }
            }
        }
    }

    while (!st_validate_tokens.empty()) {
        errors_found.push_back(st_validate_tokens.top());
        errors_locations.push_back(st_validate_tokensLines.top());
        errors_index.push_back(st_validate_tokensIndex.top());
        error_type.push_back(2);
        st_validate_tokens.pop();
        st_validate_tokensLines.pop();
        st_validate_tokensIndex.pop();
    }

    if (errors_found.empty()) {
        cout << "VALID" << endl;
    } else {
        cout << "INVALID" << endl;
    }

    ERROR_VIEWER(errors_found, errors_locations, error_type);
    return errors_found.empty();
}

void ERROR_VIEWER(vector<string> errors_found, vector<int> errors_locations, vector<int> error_type) {
    /*
    This Function is used to view the errors found in the XML tags

    Parameters:
    errors_found (vector<string>): The vector containing the wrong tags
    errors_locations (vector<int>): The vector containing the error line numbers
    error_type (vector<int>): The vector containing the error types

    Returns:
    void
    */
    if (errors_found.empty()) return;
    cout << "Errors Found:" << endl;
    for (int i = 0; i < errors_found.size(); i++) {
        cout << "Tag: " << errors_found[i] << " Line: " << errors_locations[i] << " ,Error: ";
        switch (error_type[i]) {
            case 1:
                cout << "Unopened closed tag!" << endl;
                break;
            case 2:
                cout << "Unclosed tag!" << endl;
                break;
        }
    }
}
void XMLTags(string input) {
    /*
    This Function is used to seperate the tags from the input string

    Parameters:
    input (string): The input string containing the XML tags

    Returns:
    void
    */
    tokens.clear();
    tokensLines.clear();
    tokensIndex.clear();
    int line = 1;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '\n') line++;
        if (input[i] == '<') {
            tokensIndex.push_back(i);
            string token = "<";
            int j;
            for (j = i + 1; j < input.length(); j++) {
                if (input[j] == '>') {
                    token += input[j];
                    break;
                }
                token += input[j];
            }
            i = j;
            tokens.push_back(token);
            tokensLines.push_back(line);
        }
    }
}

string readXMLFile(const string& fileName) {
    /*
    This Function is used to read the content of an XML file

    Parameters:
    fileName (string): The name of the XML file to read

    Returns:
    string: The content of the XML file
    */
    ifstream ReadFile(fileName);
    if (!ReadFile.is_open()) {
        cerr << "Error: Unable to open file " << fileName << endl;
        exit(1);
    }
    string line, content;
    while (getline(ReadFile, line)) {
        content += line + "\n";
    }
    ReadFile.close();
    return content;
}