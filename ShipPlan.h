#include <stack>
#include <iostream>
#include "Container.h"

class ShipPlan{
    int floorNum = 0;
    int maxHeight = 0;
    int maxWidth = 0;
    std::stack<Container*>** containers = nullptr;

public:
    ShipPlan(int _floorNum, int _maxHeight, int _maxWidth);

    ShipPlan(const ShipPlan& other);

    ShipPlan& operator=(const ShipPlan& other);

    int getFloorNum();

    int getMaxHeight();

    int getMaxWidth();

    std::stack<Container*>**& getContainers ();

//    friend std::ostream&operator<<(std::ostream& out, const ShipPlan& shipPlan);

    ~ShipPlan();
};
