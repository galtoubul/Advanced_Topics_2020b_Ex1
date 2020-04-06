#include "Port.h"
using std::vector;

Port::Port(string _portId) : id(_portId){};

string Port::getPortId() {
    return id;
}

void Port::addContainersToLoad(vector<Container*> _containersToLoad){
    containersToLoad = _containersToLoad;
}

vector<Container*> Port::getContainersToLoad() {
    return containersToLoad;
}

std::ostream&operator<<(std::ostream& out, const Port& port){
    out << "id: " << port.id;
}

