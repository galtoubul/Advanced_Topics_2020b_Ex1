#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
class Container;

class Port {
    string id;
    vector<Container*> containersToUnload;

public:

    Port(const string& _portId = "UNINITIALIZED") : id(_portId) {}

    const string& getPortId() const;

    void addContainerToUnloadToPort(Container* container);

    const vector<Container*>& getContainersToUnload() const;

    friend std::ostream& operator<<(std::ostream& out, const Port& port);

};
