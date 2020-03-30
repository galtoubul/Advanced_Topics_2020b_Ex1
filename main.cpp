#include <iostream>
#include "ShipPlan.h"

int main() {
    Container* container1 = new Container (1000 , "ILASH", "051065196581", false);
    std::cout << container1->getWeight() << '\n';
    std::cout << container1->getDestination() << '\n';
    std::cout << container1->getId() << '\n';
    std::cout << container1->isFutile() << '\n';
    std::cout << container1->getFloorNum() << '\n';

    std::cout << "----------------------------------------------------------" << '\n';

    ShipPlan* shipPlan1 = new ShipPlan (4, 4, 4);
    std::cout << shipPlan1->getFloorNum() << '\n';
    std::cout << shipPlan1->getMaxHeight() << '\n';
    std::cout << shipPlan1->getMaxWidth() << '\n';


    return 0;
}
