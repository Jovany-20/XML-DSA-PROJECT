#ifndef DRAW_GRAPH_H
#define DRAW_GRAPH_H

#include <vector>
#include <map>
#include <string>

void save_graph_to_dot(const std::map<std::string, std::vector<std::string>>& users, const std::string& filename);

void generate_image(const std::string& dot_file, const std::string& output_image);

#endif  // DRAW_GRAPH_H
