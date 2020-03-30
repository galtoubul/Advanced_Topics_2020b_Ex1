#include "ShipPlan.h"

ShipPlan::ShipPlan(int _floorNum, int _maxHeight, int _maxWidth) :
    floorNum(_floorNum), maxHeight(_maxHeight), maxWidth(_maxWidth)  {
    containers = new std::stack<Container>* [maxHeight];
    for (int i = 0; i < maxWidth; i++)
        containers[i] = new std::stack<Container> [maxWidth];
}

int ShipPlan::getFloorNum(){
    return floorNum;
}

int ShipPlan::getMaxHeight(){
    return maxHeight;
}

int ShipPlan::getMaxWidth(){
    return maxWidth;
}

std::stack<Container>**& ShipPlan::getContainers(){ /*TODO: make the returned value const*/
    return containers;
}

ShipPlan::~ShipPlan() {
    for (int i = 0; i < maxHeight; i++)
        delete[] containers[i];
    delete [] containers;
}