#include <iostream>
#include <string>
#include <list>
#include "Port.h"
using std::list;
using std::vector;

class ShipRoute{
    list<Port*> portList;

public:
    ShipRoute () : portList() {}

    ShipRoute(list<Port*> _portList) : portList(_portList) {}

    Port* getNextPort();

    list<Port*>& getPortList();

    friend std::ostream& operator<<(std::ostream& out, const ShipRoute& shipRoute);
};

