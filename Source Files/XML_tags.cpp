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
