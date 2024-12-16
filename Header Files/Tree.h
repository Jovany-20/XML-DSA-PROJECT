#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>

class Tree {
public:
    string val;                     // Node value
    vector<Tree*> pointers;         // Child nodes

    // Default constructor
    Tree() : val("") {}

    // Parameterized constructor
    Tree(const string& x) : val(x) {}

    // Destructor
    ~Tree() {
        // Recursively delete all child nodes
        for (Tree* child : pointers) {
            delete child;
        }
        pointers.clear();
    }

    // Add a child node
    void addChild(Tree* child) {
        pointers.push_back(child);
    }
};

#endif // TREE_H