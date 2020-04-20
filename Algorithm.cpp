#include <string>
#include <iostream>
#include "Algorithm.h"
using std::string;
using std::cout;
using std::vector;
using std::tuple;
using std::endl;
using std::list;
using std::get;
size_t Algorithm::currPortIndex;

Algorithm* Algorithm::createAlgorithm (int algorithmNum){
    switch (algorithmNum){
        case algorithm1:
            return new Algorithm1();
        default:
            cout << "Algorithm name doesn't match any algorithm name." << endl;
            return new Algorithm1();
    }
}

void Algorithm::setWeightBalanceCalculator(WeightBalanceCalculator& _calculator){
    this->calculator = _calculator;
}

void Algorithm1::getInstructionsForCargo(const string& inputFileName, const string& outputFileName){
    vector<Container*> containersAwaitingAtPort;
    readContainersAwaitingAtPort(inputFileName, containersAwaitingAtPort);

    vector<INSTRUCTION> instructions;
    getUnloadingInstructions(instructions);
    bool isFinalPort = currPortIndex == shipRoute.getPortsList().size();
    if (!isFinalPort)
        getLoadingInstructions(instructions, containersAwaitingAtPort);

    ofstream instructionsForCargoFile (outputFileName);
    writeInstructionsToFile(instructions, instructionsForCargoFile);
}

void Algorithm1::getUnloadingInstructions(vector<INSTRUCTION> instructions){
    for (Container* container : shipRoute.getPortsList()[currPortIndex].getContainersToUnload()){
        std::cout << "unloading "<< container->getId() << std::endl;
        unloadToPort(container, instructions);
    }
}

void Algorithm1::unloadToPort(Container* container, vector<INSTRUCTION>& instructions){
    size_t floorOfContainer, x, y;
    std::tie(x, y, floorOfContainer) = container->getLocation();
    // std::cout << "loc is "<< x<< y << floorOfContainer << std::endl;

    size_t currFloor = this->shipPlan.getContainers()[x][y].size() - 1; //start from highest floor of x,y
    vector<INSTRUCTION> containersToLoadBack;
    Container* currContainer;

    // unloading all containers above the desired container
    while(currFloor != floorOfContainer){ //TODO: simulation + balance calculator check of moves
        currContainer = this->shipPlan.getContainers()[x][y][currFloor];
        if (currContainer == nullptr){
            currFloor--;
            continue;
        }
        // std::cout << "not yet "<< currContainer->getId() << std::endl;
        instructions.emplace_back('U',currContainer->getId(), currFloor, x, y);
        containersToLoadBack.emplace_back('L', currContainer->getId(), currFloor - 1, x, y);
        currFloor--;
    }

    //if (currContainer == nullptr){}
    currContainer = this->shipPlan.getContainers()[x][y][currFloor];
    instructions.emplace_back('U', currContainer->getId(), currFloor, x, y);
    //std::cout << "took it "<< currContainer->getId() << std::endl;
    this->shipPlan.removeContainer(x, y, currFloor);

    int i = containersToLoadBack.size() - 1;
    currFloor++;
    while (currFloor != this->shipPlan.getContainers()[x][y].size() && i >= 0) {
        currContainer = this->shipPlan.getContainers()[x][y][currFloor];
        //   std::cout << "put back "<< currContainer->getId() << std::endl;
        currContainer->setLocation(x,y,currFloor - 1);
        this->shipPlan.setContainers(x,y,currFloor - 1, currContainer);
        instructions.push_back(containersToLoadBack[i]);
        i--;
        currFloor++;
    }
    this->shipPlan.setContainers(x,y,currFloor - 1, nullptr);
}

void Algorithm1::getLoadingInstructions(vector<INSTRUCTION> instructions, vector<Container*> containersAwaitingAtPort){
    for (Container* container : containersAwaitingAtPort){ //TODO: give priority to containers of closer destination port
        std::cout << "loading "<< container->getId() << std:: endl;
        loadToShip(container, instructions);
    }
}

void Algorithm1::loadToShip(Container* container, vector<INSTRUCTION>& instructions){
    string portDest = container->getDestination();
    if (!portInRoute(this->shipRoute, portDest)) {
        instructions.emplace_back('R', container->getId(), NOT_IN_ROUTE, NOT_IN_ROUTE, NOT_IN_ROUTE);
        return;
    }
    for (int x = 0; x < this->shipPlan.getPivotXDimension(); x++){
        for (int y = 0; y < this->shipPlan.getPivotYDimension(); y++){
            for (int floor = 0; floor < this->shipPlan.getFloorsNum(); floor++){
                if (this->shipPlan.getContainers()[x][y][floor] != nullptr){
                    continue;
                }
                else{
                    this->shipPlan.setContainers(x, y, floor, container); //for now put in the first free spot
                    container->setLocation(x, y, floor);
                    instructions.emplace_back('L', container->getId(), floor, x, y);
                    (const_cast<Port&>(shipRoute.getPortsList()[currPortIndex])).addContainerToUnloadToPort(container);
                    return;
                }
            }
        }
    }
}

bool portInRoute(ShipRoute& shipRoute, string& portId){ //TODO: check the scenario of a port which was already visited
    for (int i = Algorithm::currPortIndex; (size_t)i < shipRoute.getPortsList().size() - 1; i++) {
        if (shipRoute.getPortsList()[i].getPortId() == portId)
            return true;
    }
    cout << portId << " is not in route" << endl;
    return false;
}