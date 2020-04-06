#include <iostream>
#include <string>
#include <vector>
class Container;
using std::string;
using std::vector;

class Port {
    string id;
    vector<Container*> containersToLoad;

public:
    Port(string _portId);

    string getPortId();

    void addContainersToLoad(vector<Container*> _containersToLoad);

    vector<Container*>getContainersToLoad();

    friend std::ostream&operator<<(std::ostream& out, const Port& port);

};
