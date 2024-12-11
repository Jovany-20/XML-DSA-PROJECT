```vector<int> tokensLines;
vector<int> tokensIndex;

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
