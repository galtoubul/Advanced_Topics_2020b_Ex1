
#include "Port.h"

Port::Port(char* _portId, std::vector<Container> _containersToLoad) :
            id(_portId), containersToLoad(_containersToLoad){};


char* Port::getPortId() {
    return id;
}

std::vector<Container> Port::getContainersToLoad() {
    return containersToLoad;
}


std::ostream&operator<<(std::ostream& out, const Port& port){
    out << "id: " << port.id;
}

