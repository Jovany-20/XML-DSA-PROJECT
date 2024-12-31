#include  "../Header Files/decompression.h"

bool decodeFromFile(const std::string& fileName, const std::string& outputFile) {
    /*
This Function is used to decode a file using LZW compression algorithm.

Parameters:
fileName (const std::string&): The name of the file to be decoded.
outputFile (const std::string&): The name of the file to save the decoded data.

Returns:
bool: Returns true if decoding is successful, otherwise returns false.
*/
    std::cout << "\nDecoding:\n";

    // Initialize the dictionary with single-character entries
    std::unordered_map<int, std::string> dictionary;
    for (int i = 0; i <= 255; i++) {
        dictionary[i] = std::string(1, char(i));
    }

    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << fileName << std::endl;
        return false;
    }

    std::vector<int> encoded;
    int code;
    while (inFile.read(reinterpret_cast<char*>(&code), sizeof(int))) {
        encoded.push_back(code);
    }
    inFile.close();

    if (encoded.empty()) {
        std::cerr << "Error: No data found in file: " << fileName << std::endl;
        return false;
    }

    int old_code = encoded[0];
    std::string current = dictionary[old_code];
    std::string result = current;
    std::string character = "";
    character += current[0];
    int code_index = 256;

    std::cout << result;

    for (size_t i = 1; i < encoded.size(); i++) {
        int new_code = encoded[i];
        std::string entry;

        if (dictionary.find(new_code) != dictionary.end()) {
            entry = dictionary[new_code];
        } else {
            entry = dictionary[old_code] + character;
        }

        result += entry;
        std::cout << entry;

        character = "";
        character += entry[0];

        dictionary[code_index++] = dictionary[old_code] + character;
        old_code = new_code;
    }
    // Write the decoded data to the output file
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << outputFile << std::endl;
        return false;
    }  
    outFile << result;
    outFile.close();
  return true;
}
