#include <iostream>
#include <string>
#include <vector>
#include "ShipRoute.h"
using std::list;

ShipRoute::ShipRoute(list<Port> _portList) : portList(_portList) {}

//TODO: validity check port name is where we get the input

Port& ShipRoute::getNextPort(){
    return portList.front();
}

std::ostream&operator<<(std::ostream& out, const ShipRoute& shipRoute) {
    out << "route: ";
    for (auto const& p : shipRoute.portList)
        out << p << ' ';
}

