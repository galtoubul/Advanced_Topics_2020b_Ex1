#include <iostream>
#include <cstdlib>
#include <vector>


#include "ShipPlan.h"
#include "ShipRoute.h"
#include "Port.h"


int main() {
    Container* container1 = new Container (1000 , "ILASH", "051065196581", false);
    std::cout << container1->getWeight() << std::endl;
    std::cout << container1->getDestination() << std::endl;
    std::cout << container1->getId() << std::endl;
    std::cout << container1->isFutile() << std::endl;
    std::cout << container1->getFloorNum() << std::endl;

    std::cout << "----------------------------------------------------------" << '\n';

    ShipPlan* shipPlan1 = new ShipPlan (4, 4, 4);
    std::cout << shipPlan1->getFloorNum() << std::endl;
  //  std::cout << shipPlan1->getMaxHeight() << std::endl;
  //  std::cout << shipPlan1->getMaxWidth() << std::endl;

    std::cout << "----------------------------------------------------------" << '\n';

    shipPlan1->getContainers()[0][0].push(container1);
    std::cout << shipPlan1->getContainers()[0][0][0]<< std::endl;
    std::vector<Container>* vec = new std::vector<Container> (3){};
    vec[0] = new Container (1000 , "ABC", "123", false);
    vec[1] = new Container (1000 , "CEE", "234", false);
    vec[2] = new Container (1000 , "SDF", "456", false);

    Port port = new  Port("asdf", vec);
    std::cout << port.getPortId() << std::endl;
    std::cout << port.getContainersToLoad() << std::endl;

    return EXIT_SUCCESS;
}
