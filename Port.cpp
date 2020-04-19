#include "Port.h"
using std::vector;

const string& Port::getPortId() const{
    return this->id;
}

void Port::addContainerToUnloadToPort(Container* container){
    containersToUnload.push_back(container);
    //std::cout << "container was added to port "<< this->id << " num containers to unload to port are:" <<  containersToUnload.size() << std:: endl;
  /*  for (Container* container1 : containersToUnload)
        std::cout << container1->getId() << std:: endl;*/
}

const vector<Container*>& Port::getContainersToUnload() {
    return containersToUnload;
}

void Port::unloadedAllContainers(){
    containersToUnload.clear();
}
std::ostream&operator<<(std::ostream& out, const Port& port){
    out << "id: " << port.id;
    return out;
}

