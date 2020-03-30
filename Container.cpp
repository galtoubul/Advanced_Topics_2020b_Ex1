#include "Container.h"

Container::Container(int _weight, char* _destination, char* _id, bool _futile, int _floorNum) :
        weight(_weight), destination(_destination), id(_id), futile(_futile), floorNum(_floorNum) {};

int  Container::getWeight (){
    return weight;
}

const char* Container:: getDestination (){
    return destination;
}

const char* Container:: getId (){
    return id;
}

bool Container:: isFutile (){
    return futile;
}

int  Container::getFloorNum () {
    return floorNum;
}








