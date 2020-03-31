#include "ShipPlan.h"

ShipPlan::ShipPlan(int _floorNum, int _maxHeight, int _maxWidth) :
        floorNum(_floorNum), maxHeight(_maxHeight), maxWidth(_maxWidth)  {
    containers = new std::stack<Container*>* [maxHeight];
    for (int i = 0; i < maxWidth; i++)
        containers[i] = new std::stack<Container*> [maxWidth];
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

std::stack<Container*>**& ShipPlan::getContainers() { /*TODO: make the returned value const*/
    return containers;
}

ShipPlan::ShipPlan(const ShipPlan& other){
    *this = other;
}

ShipPlan& ShipPlan::operator=(const ShipPlan& other){
    if (this != &other){
        delete containers;
        floorNum = other.floorNum;
        maxHeight = other.maxHeight;
        maxWidth = other.maxWidth;

        for(int i = 0; i < this->maxHeight; i++) {
            for (int j = 0; j < this->maxHeight; j++) {
                this->containers[i][j] = other.containers[i][j]; // TODO: is stack default copy is a deep copy?
            }
        }
    }
    return *this;
}

//std::ostream&operator<<(std::ostream& out, const ShipPlan& shipPlan){
//    for(int i = 0; i < shipPlan.maxHeight; i++){
//        for(int j = 0; j < shipPlan.maxHeight; j++){
//            out << shipPlan.containers[i][j].pop();
//        }
//    }
//}


ShipPlan::~ShipPlan() {
    for (int i = 0; i < maxHeight; i++)
        delete[] containers[i];
    delete [] containers;
}