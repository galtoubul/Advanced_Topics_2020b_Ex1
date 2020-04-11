#include "Port.h"
using std::vector;

Port::Port(string _portId) : id(_portId){};

string Port::getPortId() {
    return id;
}

void Port::addContainersToUnload(vector<Container*> _containersToUnload){ //changed to unload, same meaning?
    containersToUnload = _containersToUnload;
}

vector<Container*> Port::getContainersToUnload() {
    return containersToUnload;
}


std::ostream&operator<<(std::ostream& out, const Port& port){
    out << "id: " << port.id;
}
