#include <stack>
#include "Container.h"

class ShipPlan{
    std::stack<Container>** containers;

    ShipPlan(int maxHeight, int maxWidth);


    ~ShipPlan();
};
