#include <stack>
#include "Container.h"

class ShipPlan{
    int floorNum;
    int maxHeight;
    int maxWidth;
    std::stack<Container>** containers;

public:
    ShipPlan(int _floorNum, int _maxHeight, int _maxWidth);

    int getFloorNum();

    int getMaxHeight();

    int getMaxWidth();

    std::stack<Container>**& getContainers ();

    ~ShipPlan();
};
