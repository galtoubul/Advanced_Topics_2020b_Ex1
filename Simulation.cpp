#include <string>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include "Simulation.h"
using std::vector;
using std::tuple;
using std::get;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;
#define BEFORE_FIRST_PORT -1

void Simulator::initSimulation (int algorithmNum, int travelNum){
    string travelName = "Travel" + std::to_string(travelNum);
    std::cout << "Starting travel: "<< travelName << std:: endl;

    string shipPlanPath = travelName +  std::string(1, std::filesystem::path::preferred_separator) + "Ship Plan.txt";
    string shipRoutePath = travelName + std::string(1, std::filesystem::path::preferred_separator) + "Route.txt";
    this->getInput(shipPlanPath, shipRoutePath);

    Algorithm* algorithm = Algorithm::createAlgorithm(algorithmNum);
    algorithm->getInput(shipPlanPath, shipRoutePath);

    WeightBalanceCalculator calculator;
    algorithm->setWeightBalanceCalculator(calculator);

    startTravel(algorithm, travelName);
    std::cout << "End of travel: "<< travelName << std:: endl;
}

void Simulator::getInput(const string& shipPlanFileName, const string& shipRouteFileName){
    readShipPlan(this->shipPlan, shipPlanFileName);
    readShipRoute(this->shipRoute, shipRouteFileName);
}

void Simulator::startTravel (Algorithm* algorithm, const string& travelName){
    size_t currPortIndex = BEFORE_FIRST_PORT;
    for (const Port& port : this->shipRoute.getPortsList()){
        cout << "now in port " << port.getPortId() << endl;
        cout << "just for removing uyused wraning " << algorithm->currPortIndex << endl;

        Algorithm::currPortIndex = ++currPortIndex;
        cout << "currportindex " << algorithm->currPortIndex << " " << Algorithm::currPortIndex << " " << currPortIndex << endl;

        string inputFileName, outputFileName;
        bool isFinalPort = (size_t)currPortIndex == this->shipRoute.getPortsList().size()-1;
        getPortFilesName(inputFileName, outputFileName, port.getPortId(), currPortIndex, travelName, isFinalPort);

        vector<Container*> containersAwaitingAtPort;
        if (!isFinalPort)
            readContainersAwaitingAtPort(inputFileName, containersAwaitingAtPort);
        cout << "Simulator -- There are "<< containersAwaitingAtPort.size() << " containers awaiting at port " << port.getPortId() << " :" << endl;
        for (Container* container : containersAwaitingAtPort)
            std::cout << *container << std:: endl;
        if (isFinalPort && !containersAwaitingAtPort.empty())
            cout << "Warning: " << port.getPortId() << " is the last port at the ship a route, but it has containers to unload.\n"
                                                       "All of these containers won't be unloaded from port." << endl;
        int slots = freeSlotsInShip();
        for (Container* container : containersAwaitingAtPort){
            if (slots == 0)
                break;
            string destPort = container->getDestination();
            int indexOfDestPort = findPortIndex(this->shipRoute, destPort, currPortIndex);
            cout << "dest is "<< indexOfDestPort <<  endl;
            if (indexOfDestPort == NOT_IN_ROUTE)
                continue;
            (const_cast<Port&>(this->shipRoute.getPortsList()[indexOfDestPort])).addContainerToUnloadToPort(container);
            slots--;
        }

        cout << "Simulator -- There are "<< port.getContainersToUnload().size() << " containers to unload to port " << port.getPortId() << " :" << endl;
        for (Container* container : port.getContainersToUnload())
            cout << *container << endl;

        algorithm->getInstructionsForCargo(inputFileName, outputFileName);
    }
}

const ShipPlan& Simulator::getShipPlan () const{
    return this->shipPlan;
}

const ShipRoute& Simulator::getShipRoute() const{
    return this->shipRoute;
}

std::ostream& operator<<(std::ostream& out, const Simulator& simulator){
    out << "Ship Plan: " << '\n';
    simulator.getShipPlan().printShipPlan();
    out << simulator.getShipRoute() << '\n';
    return out;
}

int Simulator::freeSlotsInShip() {
    int counter = 0;
    for (int x = 0; x < this->shipPlan.getPivotXDimension(); x++)
        for (int y = 0; y < this->shipPlan.getPivotYDimension(); y++)
            for (int floor = 0; floor < this->shipPlan.getFloorsNum(); floor++)
                if (this->shipPlan.getContainers()[x][y][floor] == nullptr)
                    counter++;
    return counter;
}