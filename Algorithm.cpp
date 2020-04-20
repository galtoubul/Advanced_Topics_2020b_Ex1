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
    vector<INSTRUCTION> instructions;
    getUnloadingInstructions(instructions);
    bool isFinalPort = currPortIndex == shipRoute.getPortsList().size() -1;
    if (!isFinalPort) {
        vector<Container*> containersAwaitingAtPort;
        readContainersAwaitingAtPort(inputFileName, containersAwaitingAtPort);
        getLoadingInstructions(instructions, containersAwaitingAtPort);
    }

    ofstream instructionsForCargoFile (outputFileName);
    writeInstructionsToFile(instructions, instructionsForCargoFile);
}

void Algorithm1::getUnloadingInstructions(vector<INSTRUCTION> instructions){
    cout << "algo -- There are "<< shipRoute.getPortsList()[currPortIndex].getContainersToUnload().size() << " containers to unload to port " << shipRoute.getPortsList()[currPortIndex].getPortId() << " :" << endl;
    for (Container* container : shipRoute.getPortsList()[currPortIndex].getContainersToUnload()){
        std::cout << "unloading "<< container->getId() << std::endl;
        unloadToPort(container, instructions);
    }
}

void Algorithm1::unloadToPort(Container* container, vector<INSTRUCTION>& instructions){
    size_t floorOfContainer, x, y;
    std::tie(x, y, floorOfContainer) = container->getLocation();

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
        if(this->calculator.tryOperation(UNLOAD, currContainer->getWeight(), x, y)){
            instructions.emplace_back(UNLOAD,currContainer->getId(), currFloor, x, y);
            containersToLoadBack.emplace_back(LOAD, currContainer->getId(), currFloor - 1, x, y);
            currFloor--;
        }
    }

    currContainer = this->shipPlan.getContainers()[x][y][currFloor];
    instructions.emplace_back(UNLOAD, currContainer->getId(), currFloor, x, y);
    this->shipPlan.removeContainer(x, y, currFloor);

    int i = containersToLoadBack.size() - 1;
    currFloor++;
    while (currFloor != this->shipPlan.getContainers()[x][y].size() && i >= 0) {
        currContainer = this->shipPlan.getContainers()[x][y][currFloor];
        currContainer->setLocation(x,y,currFloor - 1);
        this->shipPlan.setContainers(x,y,currFloor - 1, currContainer);
        instructions.push_back(containersToLoadBack[i]);
        i--;
        currFloor++;
    }
    this->shipPlan.setContainers(x,y,currFloor - 1, nullptr);
}



void Algorithm1::getLoadingInstructions(vector<INSTRUCTION> instructions, vector<Container*> containersAwaitingAtPort){
    vector<Container*> sortedContainersAwaitingAtPort = orderContainersByDest(containersAwaitingAtPort, shipRoute, currPortIndex);
    for (Container* container : sortedContainersAwaitingAtPort){ //TODO: give priority to containers of closer destination port
        std::cout << "loading "<< container->getId() << std:: endl;
        loadToShip(container, instructions);
    }
}

void Algorithm1::loadToShip(Container* container, vector<INSTRUCTION>& instructions){
    string portDest = container->getDestination();
    if (findPortIndex(this->shipRoute, portDest, currPortIndex) == NOT_IN_ROUTE) {
        instructions.emplace_back(REJECT, container->getId(), NOT_IN_ROUTE, NOT_IN_ROUTE, NOT_IN_ROUTE);
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
                    if(this->calculator.tryOperation(UNLOAD, container->getWeight(), x, y)){
                        instructions.emplace_back(LOAD, container->getId(), floor, x, y);
                        (const_cast<Port&>(shipRoute.getPortsList()[findPortIndex(this->shipRoute, portDest, currPortIndex)])).addContainerToUnloadToPort(container);
                        return;
                    }
                }
            }
        }
    }
}


