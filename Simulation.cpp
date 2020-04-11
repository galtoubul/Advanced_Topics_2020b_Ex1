#include <sstream>
#include <string>
#include <iostream>

#include "Simulation.h"
#include "Parser.h"
#include "StowageAlgorithm.h"

using std::vector;
using std::tuple;
using std::get;
using std::ofstream;

ShipPlan* shipPlan;
ShipRoute* shipRoute;
Port* currPort;


void travel(string shipPlanFileName, string shipRouteFileName){
    initSimulation(shipPlanFileName, shipRouteFileName);
    for (Port port : shipRoute->getPortList()){
        currPort = &port;
        input_full_path_and_file_name = ;// find the proper file using extPortIdFromFileName
        getInstructionsForCargo(input_full_path_and_file_name, output_full_path_and_file_name); //figure out what they want the output file to be
    }
}


void initSimulation (string shipPlanFileName, string shipRouteFileName){
    vector<tuple<int, int, int>> vecForShipPlan = readShipPlan(shipPlanFileName);
    int dimX = get<0>(vecForShipPlan[0]);
    int dimY = get<1>(vecForShipPlan[0]);
    int floorsNum = get<2>(vecForShipPlan[0]);
    shipPlan = new ShipPlan(dimX, dimY, floorsNum);
    initShipPlan(shipPlan, vecForShipPlan);
    shipPlan->printShipPlan();

    list<Port> portsList = readShipRoute(shipRouteFileName);
    shipRoute = new ShipRoute(portsList);
}


void initShipPlan (ShipPlan* shipPlan, vector<tuple<int, int, int>> vecForShipPlan){
    int floorsNum = get<0>(vecForShipPlan[0]);
    for (int i = 1; i < vecForShipPlan.size(); ++i) {
        int actualFloorNum = floorsNum - get<2>(vecForShipPlan[i]);
        for (int j = 0; j < actualFloorNum; j++){
            /*Container futileContainer{};
            shipPlan.insertContainer(futileContainer, get<0>(vecForShipPlan[i]), get<1>(vecForShipPlan[i]), j);*/
            Container* futileContainer = new Container{};
            shipPlan->insertContainer(futileContainer, get<0>(vecForShipPlan[i]), get<1>(vecForShipPlan[i]), j);
        }
    }
}

void getInstructionsForCargo(string input_full_path_and_file_name, string output_full_path_and_file_name){ //check const and &?
    ifstream containersAwaitingAtPortFile (input_full_path_and_file_name);
    vector<Container*> containersAwaitingAtPort = parseContainerVecOfPort(containersAwaitingAtPortFile);
//    string portId = extPortIdFromFileName(input_full_path_and_file_name);
    ofstream instructionsForCargoFile (output_full_path_and_file_name);
    vector<tuple<char,string,int,int,int,int,int,int>> instructions = runAlgorithmForPort(currPort, containersAwaitingAtPort, shipPlan);
    writeInstructionsToFile(instructions, instructionsForCargoFile);
}



