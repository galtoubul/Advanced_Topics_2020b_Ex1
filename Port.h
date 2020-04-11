#include <iostream>
#include <string>
#include <vector>
class Container;
using std::string;
using std::vector;

class Port {
    string id;
    vector<Container*> containersToUnload; // changed to unload

public:
    Port(string _portId);

    string getPortId();

    void addContainersToUnload(vector<Container*> _containersToUnload);

    vector<Container*>getContainersToUnload();

    friend std::ostream&operator<<(std::ostream& out, const Port& port);

};
