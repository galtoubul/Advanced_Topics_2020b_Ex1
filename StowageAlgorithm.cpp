#include "StowageAlgorithm.h"
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "Parser.h"

using std::string;
using std::cout;
using std::vector;
using std::tuple;
using std::endl;
using std::list;


vector<tuple<char,string,int,int,int,int,int,int>> runAlgorithmForPort(Port* port, vector<Container*> containersAwaitingAtPort, ShipPlan* shipPlan, ShipRoute* shipRoute, int currPortI){
    vector<tuple<char,string,int,int,int,int,int,int>> instructions;
    vector<Container*> containersToUnload = port->getContainersToUnload();
    for (Container* container : containersToUnload){
        unloadToPort(container, port, &instructions, shipPlan);
    }
    for (Container* container : containersAwaitingAtPort){ //TODO: give priority to containers of closer destinationd port
        loadToShip(container, port, &instructions, shipPlan, shipRoute);
    }
    return instructions;
}

void loadToShip(Container* container, Port* port, vector<tuple<char,string,int,int,int,int,int,int>>* instructions, ShipPlan* shipPlan, ShipRoute* shipRoute){
    if (!checkIfValidContainer(container)) {
        instructions->push_back(std::make_tuple('R', container->getId(), -1, -1, -1, -1, -1,
                                                -1)); //TODO: check why wasn't written that R doesn't need x,y,f parameters
        return;
    }
    for (int x = 0; x < shipPlan->getPivotXDimension(); x++){
        for (int y = 0; y < shipPlan->getPivotYDimension(); y++){
            for (int floor = 0; floor < shipPlan->getFloorNum(); floor++){
                if (shipPlan->getContainers()[x][y][floor]->isFutile() || shipPlan->getContainers()[x][y][floor] == nullptr)
                    continue;
                else{
                    shipPlan->insertContainer(container,x,y,floor); //for now put in the first free spot
                    instructions->push_back(std::make_tuple('L',container->getId(),floor,x,y,-1,-1,-1));
                    return;
                }
            }
        }
    }
}



void unloadToPort(Container* container, Port* port, vector<tuple<char,string,int,int,int,int,int,int>>* instructions, ShipPlan* shipPlan){
    int floorOfContainer = std::get<2>(container->getLocation());
    int x = std::get<0>(container->getLocation());
    int y = std::get<1>(container->getLocation());
    int floor = shipPlan->getContainers()[x][y].size()-1; //start from highest floor of x,y
    vector<tuple<char,string,int,int,int,int,int,int>> containersToLoadBack;
    Container* currContainer;
    while(floor!= floorOfContainer){
        currContainer = shipPlan->getContainers()[std::get<0>(container->getLocation())][std::get<1>(container->getLocation())][floor];
      /*  if (currContainer->isFutile())
            continue;*/ //not relevant, no futile on top
        instructions->push_back(std::make_tuple('U',currContainer->getId(),floor,x,y,-1,-1,-1));
        containersToLoadBack.push_back(std::make_tuple('L',currContainer->getId(),floor-1,x,y,-1,-1,-1));
        }
        floor--;
    instructions->push_back(std::make_tuple('U',currContainer->getId(),floor,x,y,-1,-1,-1));
    shipPlan->removeContainer(x,y, floor);
    int i = 0;
    floor++;
    while (floor!= shipPlan->getContainers()[x][y].size() && i<containersToLoadBack.size()) {
        currContainer = shipPlan->getContainers()[x][y][floor];
        /*if (currContainer->isFutile())
            break;*/
        currContainer->setLocation(x,y,floor-1);
        shipPlan->setContainers(x,y,floor-1, currContainer);
        instructions->push_back(containersToLoadBack[i]);
        i++;
        floor++;
    }
}