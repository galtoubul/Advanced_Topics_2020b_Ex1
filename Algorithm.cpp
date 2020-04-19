#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "Algorithm.h"

using std::string;
using std::cout;
using std::vector;
using std::tuple;
using std::endl;
using std::list;
using std::get;

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

void Algorithm::setCurrPort(Port* port){
    currPort = findPortFromId(port->getPortId());
    if (currPort == nullptr)
        cout << "Error - didn't find an existing port in the algorithm route." << endl; //won't get there - just to make sure
}

Port* Algorithm::getCurrPort(){
    return currPort;
}

void Algorithm::getInstructionsForCargo(const string& inputFileName, const string& outputFileName){
    vector<Container*> containersAwaitingAtPort;
    if (inputFileName == "finalPort"){
        this->isFinalPort = true;
        ofstream instructionsForCargoFile (outputFileName);
        vector<tuple<char,string,int,int,int,int,int,int>> instructions = runAlgorithmForPort(containersAwaitingAtPort);
        writeInstructionsToFile(instructions, instructionsForCargoFile);
        return;
    }
    readContainersAwaitingAtPort(inputFileName, containersAwaitingAtPort);

    ofstream instructionsForCargoFile (outputFileName);
    vector<tuple<char,string,int,int,int,int,int,int>> instructions = runAlgorithmForPort(containersAwaitingAtPort);
    writeInstructionsToFile(instructions, instructionsForCargoFile);
}

vector<tuple<char,string,int,int,int,int,int,int>> Algorithm::runAlgorithmForPort (vector<Container*> containersAwaitingAtPort){
    vector<tuple<char,string,int,int,int,int,int,int>> instructions;
    vector<Container*> containersToUnload = this->currPort->getContainersToUnload();
    for (Container* container : containersToUnload){
        std::cout << "unloading "<< container->getId() << std:: endl;
        unloadToPort(container, &instructions);
    }
    this->currPort -> unloadedAllContainers();
    if (this->isFinalPort)
        return instructions;
    for (Container* container : containersAwaitingAtPort){ //TODO: give priority to containers of closer destinationd port
        std::cout << "loading "<< container->getId() << std:: endl;
        loadToShip(container, &instructions);
    }
    return instructions;
}

void Algorithm::loadToShip(Container* container, vector<tuple<char,string,int,int,int,int,int,int>>* instructions){
    string portDest = container->getDestination();
    if (!portInRoute(this->shipRoute, portDest)) {
        instructions->push_back(std::make_tuple('R', container->getId(), -1, -1, -1, -1, -1,
                                                -1));
        return;
    }
    for (int x = 0; x < this->shipPlan.getPivotXDimension(); x++){
        for (int y = 0; y < this->shipPlan.getPivotYDimension(); y++){
            for (int floor = 0; floor < this->shipPlan.getFloorsNum(); floor++){
                if (this->shipPlan.getContainers()[x][y][floor] != nullptr){
                    continue;
                }
                else{
                    this->shipPlan.setContainers(x,y,floor,container); //for now put in the first free spot
                    container->setLocation(x,y,floor);
                    instructions->push_back(std::make_tuple('L',container->getId(),floor,x,y,-1,-1,-1));
                    Port* destPortForAlgorithm = findPortFromId(container->getDestination());
                    destPortForAlgorithm->addContainerToUnloadToPort(container);
                    return;
                }
            }
        }
    }
}



void Algorithm::unloadToPort(Container* container, vector<tuple<char,string,int,int,int,int,int,int>>* instructions){
    size_t floorOfContainer = std::get<2>(container->getLocation());
    int x = std::get<0>(container->getLocation());
    int y = std::get<1>(container->getLocation());
   // std::cout << "loc is "<< x<< y << floorOfContainer << std:: endl;

    size_t floor = this->shipPlan.getContainers()[x][y].size()-1; //start from highest floor of x,y
    vector<tuple<char,string,int,int,int,int,int,int>> containersToLoadBack;
    Container* currContainer;
    while(floor != floorOfContainer){ //TODO: simulation check of moves
        currContainer = this->shipPlan.getContainers()[x][y][floor];
        if (currContainer == nullptr){
            floor--;
            continue;
        }
       // std::cout << "not yet "<< currContainer->getId() << std:: endl;
        instructions->push_back(std::make_tuple('U',currContainer->getId(),floor,x,y,-1,-1,-1));
        containersToLoadBack.push_back(std::make_tuple('L',currContainer->getId(),floor-1,x,y,-1,-1,-1));
        floor--;
    }
    currContainer = this->shipPlan.getContainers()[x][y][floor];
    instructions->push_back(std::make_tuple('U',currContainer->getId(),floor,x,y,-1,-1,-1));
    //std::cout << "took it "<< currContainer->getId() << std:: endl;
    this->shipPlan.removeContainer(x,y, floor);
    size_t i = containersToLoadBack.size()-1;
    floor++;
    while (floor != this->shipPlan.getContainers()[x][y].size() && i < containersToLoadBack.size()) {
        currContainer = this->shipPlan.getContainers()[x][y][floor];
     //   std::cout << "put back "<< currContainer->getId() << std:: endl;
        currContainer->setLocation(x,y,floor-1);
        this->shipPlan.setContainers(x,y,floor-1, currContainer);
        instructions->push_back(containersToLoadBack[i]);
        i--; //TODO - check
        floor++;
    }
    this->shipPlan.setContainers(x,y,floor-1, nullptr);
}

Port* Algorithm::findPortFromId(const string& portId){
    for (Port* port : this->shipRoute.getPortList()) {
        if (port->getPortId() == portId)
            return port;
    }
    return nullptr; //won't reach there
}
