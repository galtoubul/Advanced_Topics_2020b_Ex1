#include "Container.h"

Container::Container(int _weight, string _destination, string _id, bool _futile, int _floorNum) :
        weight(_weight), destination(_destination), id(_id), futile(_futile), floorNum(_floorNum) {}

Container::Container() :
        weight(0), destination(""), id(""), futile(true), floorNum(-1) {}

Container::Container (const Container& other) :
        weight(other.weight), destination(other.destination), id(other.id), futile(other.futile), floorNum(other.floorNum) {}

int  Container::getWeight (){
    return weight;
}

string Container:: getDestination () const{
    return destination;
}

string Container:: getId () const{
    return id;
}

bool Container:: isFutile (){
    return futile;
}

int  Container::getFloorNum () {
    return floorNum;
}

void Container::setDestination (string newDestination){
    this->destination = newDestination;
}

std::ostream&operator<<(std::ostream& out, const Container& container){
    if(container.futile)
        out << "futile container";
    else
        out << "id: " << container.id << ", destination: " << container.destination << ", weight: " << container.weight;
}









