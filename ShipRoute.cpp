#include <iostream>
#include <string>
#include <vector>
#include "ShipRoute.h"
using std::list;

//TODO: validity check port name is where we get the input

Port* ShipRoute::getNextPort(){
    return portList.front();
}

list<Port*>& ShipRoute::getPortList(){
    return this->portList;
}

std::ostream&operator<<(std::ostream& out, const ShipRoute& shipRoute) {
    out << "route: ";
    for (auto const& p : shipRoute.portList)
        out << p << ' ';
    return out;
}

