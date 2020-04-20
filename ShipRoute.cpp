#include <iostream>
#include <string>
#include "ShipRoute.h"
//using std::list;
using std::unordered_map;
using std::vector;
//TODO: validity check port name is where we get the input

//const Port& ShipRoute::getNextPort() const{
//    return portList.front();
//}

const vector<Port>& ShipRoute::getPortsList() const{
    return this->portsList;
}

void ShipRoute::addPort(const string& portId){
    this->portsList.emplace_back(portId);
}

std::ostream& operator<<(std::ostream& out, const ShipRoute& shipRoute) {
    out << "route: ";
    for (auto const& p : shipRoute.portsList)
        out << p.getPortId() << ' ';
    return out;
}

