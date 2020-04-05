#include <iostream>
#include "Container.h"

class ShipPlan{
    int floorNum = 0;
    int dimX = 0;
    int dimY = 0;
    Container*** containers = nullptr; //check init thing

public:
    ShipPlan(int _numFloor, int _dimX, int _dimY);

    ShipPlan(const ShipPlan& other);

    ShipPlan& operator=(const ShipPlan& other);

    int getFloorNum();

    int getPivotXDimension();

    int getPivotYDimension();

    Container*** getContainers();
 //   std::stack<Container*>**& getContainers ();

//    friend std::ostream&operator<<(std::ostream& out, const ShipPlan& shipPlan);

    ~ShipPlan();
};
