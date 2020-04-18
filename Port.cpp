#include "Port.h"
using std::vector;

const string& Port::getPortId() const{
    return this->id;
}

void Port::addContainersToUnloadToPort(vector<Container*>& _containersToUnload){
    containersToUnload = _containersToUnload;
}

const vector<Container*>& Port::getContainersToUnload() {
    return containersToUnload;
}


std::ostream&operator<<(std::ostream& out, const Port& port){
    out << "id: " << port.id;
    return out;
}

