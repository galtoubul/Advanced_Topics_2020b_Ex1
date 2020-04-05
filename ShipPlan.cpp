#include "ShipPlan.h"

ShipPlan::ShipPlan(int _floorNum, int _dimX, int _dimY) :
        floorNum(_floorNum), dimX(_dimX), dimY(_dimY)  {
    Container*** containers = 0;
    containers = new Container** [dimX];
            for (int i = 0; i<dimX; i++){
                containers[i] = new Container* [dimY];
                for (int j = 0; j<dimY; j++){
                    containers[i][j] = new Container(0, nullptr, nullptr, true);
                }
            }
}

int ShipPlan::getFloorNum(){
    return floorNum;
}

int ShipPlan::getPivotXDimension(){
    return dimX;
}

int ShipPlan::getPivotYDimension(){
    return dimY;
}

Container*** ShipPlan::getContainers() { /*TODO: make the returned value const*/
    return containers;
}

ShipPlan::ShipPlan(const ShipPlan& other){
    *this = other;
}

ShipPlan& ShipPlan::operator=(const ShipPlan& other){
    if (this != &other){
        delete containers;
        floorNum = other.floorNum;
        dimX = other.dimX;
        dimY = other.dimY;

        for(int i = 0; i < this->dimX; i++) {
            for (int j = 0; j < this->dimY; j++) {
                for (int h = 0; h < this->floorNum; h++){
                    containers[i][j][h] = other.containers[i][j][h];
                }
            }
        }
    }
    return *this;
}

ShipPlan::~ShipPlan() {
    for (int i = 0; i < dimX; ++i)
        for (int j = 0; j < dimY; ++j)
            delete[] containers[i][j];
}

//std::ostream&operator<<(std::ostream& out, const ShipPlan& shipPlan){
//    for(int i = 0; i < shipPlan.maxHeight; i++){
//        for(int j = 0; j < shipPlan.maxHeight; j++){
//            out << shipPlan.containers[i][j].pop();
//        }
//    }
//}

