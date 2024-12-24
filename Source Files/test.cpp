#include <iostream>
#include "Graph.cpp"

using namespace std;

int main() {
    // Use the full XML data with additional information
    string xmlData = R"(
<users>
<user>
<id>1</id>
<name>Ahmed Ali</name>
<posts>
<post>
<body>
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
</body>
<topics>
<topic>
economy
</topic>
<topic>
finance
</topic>
</topics>
</post>
<post>
<body>
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
</body>
<topics>
<topic>
solar_energy
</topic>
</topics>
</post>
</posts>
<followers>
<follower>
<id>2</id>
</follower>
<follower>
<id>3</id>
</follower>
</followers>
</user>
<user>
<id>2</id>
<name>Yasser Ahmed</name>
<posts>
<post>
<body>
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
</body>
<topics>
<topic>
education
</topic>
</topics>
</post>
</posts>
<followers>
<follower>
<id>1</id>
</follower>
</followers>
</user>
<user>
<id>3</id>
<name>Mohamed Sherif</name>
<posts>
<post>
<body>
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
</body>
<topics>
<topic>
sports
</topic>
</topics>
</post>
</posts>
<followers>
<follower>
<id>1</id>
</follower>
</followers>
</user>
</users>
)";

    vector<shared_ptr<Node>> users = graphMaker(xmlData);

    // Print each user and their followers
    for (const auto& user : users) {
        cout << "User ID: " << user->id << endl;
        cout << "Followers: ";
        for (const auto& follower : user->followers) {
            cout << follower->id << " ";
        }
        cout << endl << "-----------------------" << endl;
    }

    return 0;
}