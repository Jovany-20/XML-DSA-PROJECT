#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "../Header Files/format.h"
#include "../Header Files/Graph.h"
#include "../Header Files/Most_followers.h"
#include "../Header Files/Tree.h"
#include "../Header Files/XML_Fix.h"
#include "../Header Files/XML_Validator.h"
#include "../Header Files/mutual_followers.h"
#include "../Header Files/xmltojson.h"

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
    cout << "Usage: xml_editor <command> -i <input_file> [options]\n";
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
    string inputFlag = argv[2];
    string inputFile = argv[3];

    if (inputFlag != "-i") {
        cerr << "Error: Invalid option. Use '-i' to specify the input file.\n";
        showUsage();
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
        // Verify XML consistency
        bool isValid = ValidateXML(xmlData); 
        while(!isValid){
            cout << "XML is not valid, fixing it...\n";
            xmlData = fix_missing_open_tag(xmlData);
            xmlData = fix_missing_close_tag(xmlData);
            isValid = ValidateXML(xmlData);
            cout << "XML is fixed\n";
        }

    } else if (command == "format") {
        // Format (prettify) XML
        string formattedXML = format(xmlData);
        cout << formattedXML;

    } else if (command == "json") {
        cout <<"json start";
        // Clean and process XML
        string cleanedXML = RemoveSpaces(xmlData);
        string jsonOutput = convertXMLToJSON(cleanedXML);

        // Output JSON
        cout << jsonOutput << endl;
        //save output to file
        ofstream jsonFile("output_file.json");
        jsonFile << jsonOutput;
        jsonFile.close();


    } else if (command == "mini") {
        // Minify XML
        cout << "Minification is not implemented yet.\n";


    } else if (command == "compress") {
        // Compress XML
        cout << "Compression is not implemented yet.\n";


    } else if (command == "decompress") {
        // Decompress XML
        cout << "Decompression is not implemented yet.\n";


    } else if (command == "draw") {
        // Represent XML in graph
        cout << "Graph visualization is not implemented yet.\n";


    } else if (command == "most_active") {
        // Find the most active user
        cout << "Most active user logic is not implemented yet.\n";


    } else if (command == "most_influencer") {

        // Find the most influencer user
        map<string, vector<string>> users;
        vector<string> parsedXML = parseXML(xmlData);
        NetworkAnalysis(users, parsedXML);
        vector<string> mostInfluencers = mostFollowers(users);
        cout << "Most Influencer User(s): ";
        for (const auto& user : mostInfluencers) {
            cout << user << " ";
        }
        cout << endl;

    } else if (command == "mutual") {
        // Find mutual followers between users
        map<string, vector<string>> users;
        vector<string> parsedXML = parseXML(xmlData);
        NetworkAnalysis(users, parsedXML);
        printUsers(users);
        string firstUser = "2";
        string secondUser = "3";
        vector<string> userIds = {"1", "2", "3"};

        string result = mutualFollowersBetween_n_Users(users, userIds);
        cout << "Mutual followers between Users:";
        for(int i =0 ; i<userIds.size();i++)
        {
            cout<<userIds[i]<<" ";

        }

        cout <<"is " << result << endl;
        // cout << "Mutual followers between User " << firstUser << " and User " << secondUser << ": " << mutual << endl;



    } else if (command == "suggest") {
        // Suggest users to follow
        cout << "User suggestions logic is not implemented yet.\n";
        
    } else if (command == "search") {
        // Search posts by word or topic
        cout << "Post search logic is not implemented yet.\n";
    } else {
        cerr << "Error: Unknown command '" << command << "'.\n";
        showUsage();
        return 1;
    }

    return 0;
}
