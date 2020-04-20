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
        string inputFileName, outputFileName;
        bool isFinalPort = (size_t)currPortIndex == this->shipRoute.getPortsList().size()-1;
        getPortFilesName(inputFileName, outputFileName, port.getPortId(), currPortIndex, travelName);
//        if (isFinalPort){
//            std::cout << "final port: " << port.getPortId() << std::endl;
//            std::cout << "Simulator -- There are "<< algorithm->getCurrPort()->getContainersToUnload().size() << " containers to unload to port" << algorithm->getCurrPort()->getPortId() << " :" << std:: endl;
//            for (Container* container : algorithm->getCurrPort()->getContainersToUnload())
//                std::cout << *container << std:: endl;
//            algorithm->getInstructionsForCargo("finalPort", outputFileName);
//            continue; //==break;
//        }
        vector<Container*> containersAwaitingAtPort;
        readContainersAwaitingAtPort(inputFileName, containersAwaitingAtPort);

        if (isFinalPort && !containersAwaitingAtPort.empty())
            cout << "Warning: " << port.getPortId() << " is the last port at the ship a route, but it has containers to unload.\n"
                                                       "All of these containers won't be unloaded from port." << endl;

        cout << "Simulator -- There are "<< containersAwaitingAtPort.size() << " containers awaiting at port " << port.getPortId() << " :" << endl;
        for (Container* container : containersAwaitingAtPort)
            std::cout << *container << std:: endl;

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

/*Port* Simulator::findPortFromId(const string& portId){
    for (Port* port : this->shipRoute.getPortList()) {
        if (port->getPortId() == portId)
            return port;
    }
    return nullptr; //won't reach there
}*/