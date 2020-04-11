#include "ShipPlan.h"

ShipPlan::ShipPlan(int _dimX, int _dimY, int _floorNum) :
        dimX(_dimX), dimY(_dimY), floorNum(_floorNum),
        containers(dimX, VVC(dimY, VC (floorNum, nullptr))) {}

int ShipPlan::getFloorNum(){
    return floorNum;
}

int ShipPlan::getPivotXDimension(){
    return dimX;
}

int ShipPlan::getPivotYDimension(){
    return dimY;
}

const VVVC& ShipPlan::getContainers() {
    return this->containers;
}

void ShipPlan::setContainers(int x, int y, int floor, Container* container) {
     this->containers[x][y][floor] = container;
}

/*void ShipPlan::insertContainer (Container newContainer, int x, int y, int floorNum){
    this->containers[x][y][floorNum] = new Container(newContainer);
}*/

//new

void ShipPlan::insertContainer (Container* newContainer, int x, int y, int floorNum){
    this->containers[x][y][floorNum] = newContainer;
    containers[x][y][floorNum]->setLocation(x,y,floorNum);
}

void ShipPlan::removeContainer (int x, int y, int floorNum){
    free(this->containers[x][y][floorNum]);
}

void ShipPlan::printShipPlan () const {
    for (int i = 0; i < containers.size(); ++i) {
        for (int j = 0; j < containers[0].size(); ++j) {
            for (int k = 0; k <containers[0][0].size() ; ++k) {
                if (containers[i][j][k] != nullptr)
                    std::cout << "containers[" << i << "][" << j << "][" << k << "] = " << *containers[i][j][k]<< std::endl;
            }
        }
    }
}

//ShipPlan& ShipPlan::operator=(const ShipPlan& other){
//    if (this != &other){
//        delete containers;
//        floorNum = other.floorNum;
//        dimX = other.dimX;
//        dimY = other.dimY;
//
//        for(int i = 0; i < this->dimX; i++) {
//            for (int j = 0; j < this->dimY; j++) {
//                for (int h = 0; h < this->floorNum; h++){
//                    containers[i][j][h] = other.containers[i][j][h];
//                }
//            }
//        }
//    }
//    return *this;
//}

//ShipPlan::~ShipPlan() {
//    for (int i = 0; i < dimX; ++i)
//        for (int j = 0; j < dimY; ++j)
//            delete[] containers[i][j];
//}

//std::ostream&operator<<(std::ostream& out, const ShipPlan& shipPlan){
//    for(int i = 0; i < shipPlan.maxHeight; i++){
//        for(int j = 0; j < shipPlan.maxHeight; j++){
//            out << shipPlan.containers[i][j].pop();
//        }
//    }
//}

