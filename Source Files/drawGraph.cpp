#include "../Header Files/drawGraph.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

void save_graph_to_dot(const std::map<std::string, std::vector<std::string>>& users, const std::string& filename) {
    std::ofstream ofs(filename);

    if (!ofs.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Start the directed graph (digraph) in DOT format
    ofs << "digraph G {\n";

    // Add nodes for all users, even if they don't have any connections
    for (const auto& user : users) {
        const std::string& user_id = user.first;
        ofs << "  \"" << user_id << "\";\n";  // Add each user as a node
    }

    // Add directed edges for all follow relationships
    for (const auto& user : users) {
        const std::string& user_id = user.first;
        const std::vector<std::string>& followers = user.second;

        for (const std::string& follower : followers) {
            ofs << "  \"" << follower << "\" -> \"" << user_id << "\";\n";  // Directed edge showing who follows whom
        }
    }

    ofs << "}\n";  // End of the graph
    ofs.close();
}

void generate_image(const std::string& dot_file, const std::string& output_image) {
    // Command to run Graphviz and generate the image
    std::string command = "dot -Tjpg " + dot_file + " -o " + output_image;
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "Image successfully generated: " << output_image << std::endl;
    } else {
        std::cerr << "Error generating image." << std::endl;
    }
}
