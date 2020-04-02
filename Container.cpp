#include "Container.h"

Container::Container(int _weight, const char* _destination, const char* _id, bool _futile, int _floorNum) :
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
// try
bool Container:: isFutile (){
    return futile;
}

int  Container::getFloorNum () {
    return floorNum;
}

std::ostream&operator<<(std::ostream& out, const Container& container){
    out << "id: " << container.id << ", destination" << container.destination << ", weight: " << container.weight;
}









