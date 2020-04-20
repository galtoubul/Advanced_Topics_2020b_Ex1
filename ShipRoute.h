#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Port.h"
using std::vector;

class ShipRoute{
    vector<Port> portsList;

public:
    ShipRoute () : portsList() {}

    //ShipRoute(list<Port> _portList) : portList(_portList) {}

    //const Port& getNextPort() const;

    const vector<Port>& getPortsList() const;

    void addPort(const string& portId);

    friend std::ostream& operator<<(std::ostream& out, const ShipRoute& shipRoute);

};

