#include <iostream>
#include <string>
#include <vector>
#include "Container.h"

class Port {
    char* id;
    std::vector<Container> containersToLoad;
public:
    Port(char* _portId, std::vector<Container> _containersToLoad);

    char* getPortId();

    std::vector<Container>getContainersToLoad();

    friend std::ostream&operator<<(std::ostream& out, const Port& port);

};
