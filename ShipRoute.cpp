#include "ShipRoute.h"
#include "Port.h"
#include <iostream>
#include <string>
#include <vector>


ShipRoute::ShipRoute(int _portNum, std::vector<std::string> _portVec) :  portNum(_portNum),  portVec(_portVec){
 int currPortNum = -1;   //-1 = before first port
}
//validity check port name is where we get the input

int ShipRoute::getCurrentPortNumInRoute(){
    return currPortNum;
}

std::string ShipRoute::getNextPort(){
    return portVec[currPortNum+1];
}

int ShipRoute::getPortNum(){
    return portNum;
}

std::ostream&operator<<(std::ostream& out, const ShipRoute& shipRoute) {
    out << "route: ";
    for (auto const& p : shipRoute.portVec)
        out << p << ' ';
}

