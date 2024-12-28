#include  "../Header Files/compression.h"

bool encodeAndSave(const std::string& input, const std::string& fileName) {
    /*
    This Function is used to encode a given string using LZW compression and save the output codes to a binary file.(the input string in our case is XML file)
    
    Parameters:
    input (const std::string&): The input string that needs to be compressed.
    fileName (const std::string&): The name of the binary file where the encoded output will be saved.
    
    Returns:
    bool: Returns true if encoding and saving are successful, otherwise returns false.
    */

    //std::cout << "Encoding:\n";

    // Initialize the dictionary with single-character entries 
    std::unordered_map<std::string, int> dictionary;
    for (int i = 0; i <= 255; i++) {
        dictionary[std::string(1, char(i))] = i;
    }

    std::string current = "", next = "";
    current += input[0];
    int code = 256;
    std::vector<int> output_codes;

   // std::cout << "String\tOutput_Code\tAddition\n";
    for (size_t i = 0; i < input.length(); i++) {
        if (i != input.length() - 1)
            next += input[i + 1];

        if (dictionary.find(current + next) != dictionary.end()) {
            current += next;
        } else {
            std::cout << current << "\t" << dictionary[current] << "\t\t"
                      << current + next << "\t" << code << "\n";

            output_codes.push_back(dictionary[current]);
            dictionary[current + next] = code++;
            current = next;
        }
        next = "";
    }

    // Output the code for the last string
   //  std::cout << current << "\t" << dictionary[current] << "\n";
    output_codes.push_back(dictionary[current]);
   /* Print the string with codes
    std::cout << "\nGenerated Codes: ";
    for (int code : output_codes) {
        std::cout << code << " ";
    }
    std::cout << std::endl;*/
  
    // Save the encoded output to a file
    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << fileName << std::endl;
        return false;
    }

    for (int code : output_codes) {
        outFile.write(reinterpret_cast<const char*>(&code), sizeof(int));
    }

    outFile.close();
    return true;
}
