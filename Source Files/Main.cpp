#include "../Header Files/header.h"

using namespace std;

void printUsers(const map<string, vector<string>>& users) {
    for (const auto& pair : users) {
        cout << "User ID: " << pair.first << "\nFollowers: ";
        for (const auto& follower : pair.second) {
            cout << follower << " ";
        }
        cout << "\n\n";
    }
}

void showUsage() {
    cout << "Usage: xml_editor <command> [options]\n";
    cout << "Commands:\n";
    cout << "  verify        - Check XML consistency\n";
    cout << "  format        - Format (prettify) XML\n";
    cout << "  json          - Convert XML to JSON\n";
    cout << "  mini          - Minify XML\n";
    cout << "  compress      - Compress XML\n";
    cout << "  decompress    - Decompress XML\n";
    cout << "  draw          - Represent XML in graph\n";
    cout << "  most_active   - Find the most active user\n";
    cout << "  most_influencer - Find the most influencer user\n";
    cout << "  mutual        - Find mutual followers between users\n";
    cout << "  suggest       - Suggest users to follow\n";
    cout << "  search        - Search posts by word or topic\n";
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        showUsage();
        return 1;
    }

    string command = argv[1];
    string inputFile, outputFile;
    string word, topic;
    vector<string> userIds;

    // Parsing command-line arguments
    for (int i = 2; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-i" && i + 1 < argc) {
            inputFile = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
        } else if (arg == "-w" && i + 1 < argc) {
            word = argv[++i];
        } else if (arg == "-t" && i + 1 < argc) {
            topic = argv[++i];
        } else if (arg == "-ids" && i + 1 < argc) {
            while (i + 1 < argc && argv[i + 1][0] != '-') {
              userIds.push_back(argv[++i]);  // Add each ID with spaces between them
            }
        }else if(arg == "-id" && i + 1 < argc) {
            userIds.push_back(argv[++i]);  // Directly add single user ID
        }
        
        else {
            cerr << "Error: Unknown or incomplete option '" << arg << "'.\n";
            showUsage();
            return 1;
        }
    }

    if (inputFile.empty()) {
        cerr << "Error: Input file not specified.\n";
        return 1;
    }

    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << inputFile << endl;
        return 1;
    }

    string xmlData((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    if (command == "verify") {
        bool isValid = ValidateXML(xmlData); 
        while (!isValid) {
            cout << "XML is not valid, fixing it...\n";
            xmlData = fix_missing_open_tag(xmlData);
            xmlData = fix_missing_close_tag(xmlData);
            isValid = ValidateXML(xmlData);
            cout << "XML is fixed\n";
            if (!outputFile.empty()) {
                ofstream fixedFile(outputFile);
                fixedFile << xmlData;
                fixedFile.close();
            }
        }
    } 
    else if (command == "format") {
        string formattedXML = format(xmlData);
        cout << formattedXML;

        if (!outputFile.empty()) {
            ofstream formattedFile(outputFile);
            formattedFile << formattedXML;
            formattedFile.close();
        } else {
            cout << "Warning: No output file specified, displaying formatted XML.\n";
        }
    }
    else if (command == "json") {
        string cleanedXML = RemoveSpaces(xmlData);
        string jsonOutput = convertXMLToJSON(cleanedXML);
        cout << jsonOutput << endl;
        
        ofstream jsonFile(outputFile);
        jsonFile << jsonOutput;
        jsonFile.close();
        
            
    
    }
    else if (command == "mini") {
        string minifiedXML = RemoveSpaces(xmlData);
        
        ofstream minifiedFile(outputFile);
        minifiedFile << minifiedXML;
        minifiedFile.close();
        
        cout << minifiedXML;
        
    }
    else if (command == "compress") {
        string fileName = outputFile;
        if (!encodeAndSave(xmlData, fileName)) {
            cerr << "Encoding failed!" << endl;
        }
    }
    else if (command == "decompress") {
        string fileName = inputFile;
        if (!decodeFromFile(fileName, outputFile)) {
            cerr << "Decoding failed!" << endl;
        }

    }else if (command == "most_active") {
        // Find the most active user
        map<string, vector<string>> users;
        vector<string> parsedXML = parseXML(xmlData);
        NetworkAnalysis(users, parsedXML);
        printUsers(users);
        vector<string> result = mostActiveUser(users);
        cout << "Most Active User(s): ";
        for (const auto& user : result) {
            cout << user << " ";
        }
        cout << "\n\n";
        
    }else if (command == "draw") {
        cout << "Graph visualization is implemented in GUI.\n";
    }
    else if (command == "most_influencer") {
        map<string, vector<string>> users;
        vector<string> parsedXML = parseXML(xmlData);
        NetworkAnalysis(users, parsedXML);
        printUsers(users);
        vector<string> mostInfluencers = mostFollowers(users);
        cout << "Most Influencer User(s): ";
        for (const auto& user : mostInfluencers) {
            cout << user << " ";
        }
        cout << endl;
    }
    else if (command == "mutual") {
        if (userIds.empty()) {
            cerr << "Error: Missing user IDs for mutual command.\n";
            return 1;
        }

        map<string, vector<string>> users;
        vector<string> parsedXML = parseXML(xmlData);
        NetworkAnalysis(users, parsedXML);
        printUsers(users);

        string result = mutualFollowersBetween_n_Users(users, userIds);
        cout << "Mutual followers between Users: ";
        for (const auto& id : userIds) {
            cout << id << " ";
        }
        cout << "are " << result << endl;
    }else if (command == "suggest") {
            map<string, vector<string>> users;
            vector<string> parsedXML = parseXML(xmlData);
            NetworkAnalysis(users, parsedXML);
            printUsers(users);
            string firstUser = "2";
            string secondUser = "3";
            if (userIds.size() != 1) {
            cerr << "Error: Exactly one user ID must be specified with the -id option.\n";
                 return 1;
            }

            string userId = userIds[0];  // Use the single user ID passed with -id
            cout << "User ID: " << userId << " suggested: ";
            vector<string> suggested = suggestUsersToFollow(users, userId);

            for (const auto& suggestion : suggested) {
                cout << suggestion << ", ";
            }
            cout << endl;

        }else if (command == "search") {
        if (!word.empty()) {
            string wordResult = searchWord(word, xmlData);
            cout << "Search results for word '" << word << "':\n" << wordResult << endl;
        }

        if (!topic.empty()) {
            string topicResult = searchTopic(topic, xmlData);
            cout << "Search results for topic '" << topic << "':\n" << topicResult << endl;
        }

        if (word.empty() && topic.empty()) {
            cerr << "Error: No word or topic specified for search.\n";
            return 1;
        }
    }
    else {
        cerr << "Error: Unknown command '" << command << "'.\n";
        showUsage();
        return 1;
    }

    return 0;
}
