#include "Container.h"

Container::Container(int _weight, std::string _destination, std::string _id, bool _futile, int _floorNum) :
        weight(_weight), destination(_destination), id(_id), futile(_futile), floorNum(_floorNum) {};

int  Container::getWeight (){
    return weight;
}

std::string Container:: getDestination (){
    return destination;
}

std::string Container:: getId (){
    return id;
}

bool Container:: isFutile (){
    return futile;
}

int  Container::getFloorNum () {
    return floorNum;
}








