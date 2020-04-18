#include <sstream>
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
#define BEFORE_FIRST_PORT -1
//ShipPlan* shipPlan;
//ShipRoute* shipRoute;
Port* currPort;
int currPortIndex;
//
//
//void travel(string shipPlanFileName, string shipRouteFileName){
//    initSimulation(shipPlanFileName, shipRouteFileName);
//    currPortI = -1;
//    for (Port port : shipRoute->getPortList()){
//        currPortI++;
//        currPort = &port;
//        input_full_path_and_file_name = ;// find the proper file using extPortIdFromFileName
//        getInstructionsForCargo(input_full_path_and_file_name, output_full_path_and_file_name); //figure out what they want the output file to be
//    }
//}

void Simulator::startTravel (Algorithm* algorithm, const string& travelName){
    currPortIndex = BEFORE_FIRST_PORT;
    for (Port port : this->shipRoute.getPortList()){
        currPortIndex++;
        currPort = &port;

        string inputFileName, outputFileName;
        getPortFilesName(inputFileName, outputFileName, currPort->getPortId(), currPortIndex, travelName);

        vector<Container*> containersAwaitingAtPort;
        readContainersAwaitingAtPort(inputFileName, containersAwaitingAtPort, this->shipRoute);

        std::cout << "Simulator -- There are "<< containersAwaitingAtPort.size() << " containers awaiting at port" << port.getPortId() << " :" << std:: endl;
        for (Container* container : containersAwaitingAtPort)
            std::cout << *container << std:: endl;

        algorithm->getInstructionsForCargo(inputFileName, outputFileName);
    }
}

void Simulator::initSimulation (int algorithmNum, int travelNum){
    string travelName = "Travel" + std::to_string(travelNum);

    string shipPlanPath = travelName +  std::string(1, std::filesystem::path::preferred_separator) + "Ship Plan.txt";
    string shipRoutePath = travelName + std::string(1, std::filesystem::path::preferred_separator) + "Route.txt";
    this->getInput(shipPlanPath, shipRoutePath);

    Algorithm* algorithm = Algorithm::createAlgorithm(algorithmNum);
    algorithm->getInput(shipPlanPath, shipRoutePath);

    WeightBalanceCalculator calculator;
    algorithm->setWeightBalanceCalculator(calculator);

    startTravel(algorithm, travelName);
}

void Simulator::getInput(const string& shipPlanFileName, const string& shipRouteFileName){
    readShipPlan(this->shipPlan, shipPlanFileName);
    readShipRoute(this->shipRoute, shipRouteFileName);
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
