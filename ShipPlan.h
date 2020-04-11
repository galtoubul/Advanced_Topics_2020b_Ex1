#include <iostream>
#include <vector>
#include "Container.h"
using std::vector;
typedef vector<Container*> VC;
typedef vector<vector<Container*>> VVC;
typedef vector<vector<vector<Container*>>> VVVC;

class ShipPlan{
    int dimX = 0;
    int dimY = 0;
    int floorNum = 0;
    VVVC containers;

public:
    ShipPlan(int _dimX, int _dimY, int _numFloor);

    ShipPlan(const ShipPlan& other) = delete;

    ShipPlan& operator=(const ShipPlan& other) = delete;

    int getFloorNum();

    int getPivotXDimension();

    int getPivotYDimension();

    const VVVC& getContainers();

    void setContainers(int x, int y, int floor, Container* container);

    //void insertContainer (Container newContainer, int x, int y, int floorNum);

    void insertContainer (Container* newContainer, int x, int y, int floorNum);

    void removeContainer (int x, int y, int floorNum);

    void printShipPlan () const;


 //   std::stack<Container*>**& getContainers ();

//    friend std::ostream&operator<<(std::ostream& out, const ShipPlan& shipPlan);

   // ~ShipPlan();
};
