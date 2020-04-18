#include <iostream>
#include <vector>
#include "Container.h"
using std::vector;
typedef vector<Container*> VC;
typedef vector<vector<Container*>> VVC;
typedef vector<vector<vector<Container*>>> VVVC;
#define UNINITIALIZED -1

class ShipPlan{
    int dimX;
    int dimY;
    int floorsNum;
    VVVC containers;

public:
    explicit ShipPlan() : dimX(UNINITIALIZED), dimY(UNINITIALIZED), floorsNum(UNINITIALIZED) {}

    ShipPlan(int _dimX, int _dimY, int _floorsNum) :
            dimX(_dimX), dimY(_dimY), floorsNum(_floorsNum),
            containers(dimX, VVC(dimY, VC (_floorsNum, nullptr))) {}

    ShipPlan(const ShipPlan& other) = delete;

    int getFloorsNum();

    int getPivotXDimension();

    int getPivotYDimension();

    const VVVC& getContainers();

    void setContainers(int x, int y, int floor, Container* container);

    void removeContainer (int x, int y, int floorNum);

    void printShipPlan () const;


    //   std::stack<Container*>**& getContainers ();

//    friend std::ostream&operator<<(std::ostream& out, const ShipPlan& shipPlan);

    // ~ShipPlan();
};
