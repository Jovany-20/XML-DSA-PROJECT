#include "decompression.h"
#include <sstream>


bool decodeFromFile(const std::string& inputOfCompression, std::string& decodedMessage ) {

    /*
This Function is used to decode a file using LZW compression algorithm.

Parameters:
fileName (const std::string&): The name of the file to be decoded.

Returns:
bool: Returns true if decoding is successful, otherwise returns false.
*/
    std::cout << "\nDecoding:\n";

    // Initialize the dictionary with single-character entries
    std::unordered_map<int, std::string> dictionary;
    for (int i = 0; i <= 255; i++) {
        dictionary[i] = std::string(1, char(i));
    }



        std::vector<int> encoded;
        std::istringstream iss(inputOfCompression);
        int num;

        while (iss >> num) {
        encoded.push_back(num);
        }






    //std::cout << "micho";

    int old_code = encoded[0];
    std::string current = dictionary[old_code];
    decodedMessage = current;
    std::string character = "";
    character += current[0];
    int code_index = 256;

    //std::cout << "micho";

    for (size_t i = 1; i < encoded.size(); i++) {
        int new_code = encoded[i];
        std::string entry;

        if (dictionary.find(new_code) != dictionary.end()) {
            entry = dictionary[new_code];
        } else {
            entry = dictionary[old_code] + character;
        }
        // save the decoded message in a string (optional)
        decodedMessage += entry;

        character = "";
        character += entry[0];

        dictionary[code_index++] = dictionary[old_code] + character;
        old_code = new_code;
        //std::cout << "micho"";
    }

    return true;
}
