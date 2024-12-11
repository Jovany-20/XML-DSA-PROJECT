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
