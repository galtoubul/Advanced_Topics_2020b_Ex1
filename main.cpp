#include <cstdlib>
#include <vector>
#include <tuple>
#include <iostream>
#include <typeinfo>
#include "Simulation.h"
#include "main.h"
using std::cout;
using std::cin;
using std::endl;
#define NOT_LEGAL -1

int main() {
//    Container* container1 = new Container(1000 , "ILASH", "051065196581", false);
//    cout << "container1: " << *container1 << endl;
//
//    cout << "----------------------------------------------------------" << '\n';
//
//    Container* container2 = new Container(container1);
//    cout << "container2: " << *container2 << endl;
//    container1->setDestination("hello");
//    cout << "changing container1's destination to hello " << endl;
//    cout << "container1: " << *container1 << endl;
//    cout << "container2: " << *container2 << endl;
//
//    cout << "----------------------------------------------------------" << '\n';
//
//    cout << "creating shipPlan1 and printing its dimensions: " << endl;
//    ShipPlan shipPlan1(4, 4, 4);
//    cout << shipPlan1.getFloorsNum() << endl;
//    cout << shipPlan1.getPivotXDimension() << endl;
//    cout << shipPlan1.getPivotYDimension() << endl;
//
//    cout << "----------------------------------------------------------" << '\n';
//
//    cout << "setting shipPlan1's containers with: container1 and container2 and printing it: " << endl;
//    shipPlan1.setContainers(0, 0, 0, container1);
//    shipPlan1.setContainers(0, 0, 1, container2);
//    shipPlan1.printShipPlan();
//
//    cout << "removing shipPlan1's container[0][0][0] and printing it: " << endl;
//    shipPlan1.removeContainer(0,0,0);
//    shipPlan1.printShipPlan();
//
//    cout << "----------------------------------------------------------" << '\n';
//
//    cout << "creating containersToUnload with: container1 and container2" << endl;
//    vector<Container*> containersToUnload;
//    containersToUnload.push_back(container1);
//    containersToUnload.push_back(container2);
//
//    cout << "creating ILASH port and addContainersToUnloadToPort(containersToUnload)" << endl;
//    Port port1("ILASH");
//    port1.addContainersToUnloadToPort(containersToUnload);
//
//    cout << "printing port1.getContainersToUnload(): " << endl;
//    for(auto it = port1.getContainersToUnload().begin();
//        it != port1.getContainersToUnload().end(); ++it) {
//        cout << **it  << endl;
//    }
//
//    cout << "printing containersToUnload: " << endl;
//    for(std::vector<Container*>::iterator it = containersToUnload.begin(); it != containersToUnload.end(); ++it) {
//        cout << **it << endl;
//    }
//
//    cout << "containersToUnload[1]->setDestination(ILHIF)" << endl;
//    containersToUnload[1]->setDestination("ILHIF");
//
//    cout << "printing port1.getContainersToUnload(): " << endl;
//    for(auto it = port1.getContainersToUnload().begin();
//        it != port1.getContainersToUnload().end(); ++it) {
//        cout << **it << endl;
//    }
//
//    cout << "printing containersToUnload: " << endl;
//    for(std::vector<Container*>::iterator it = containersToUnload.begin(); it != containersToUnload.end(); ++it) {
//        cout << **it << endl;
//    }
//
//    cout << "----------------------------------------------------------" << '\n';

//    cout << "Welcome to Stowage Algorithm Simulator" << endl;
//    cout << "How many algorithms would you like to test?" << endl;
//    int algorithmsNum, travelsNum;
//    do{
//        cin >> algorithmsNum;
//    } while (check(algorithmsNum, "algorithmsNum") == NOT_LEGAL);
//    cout << "How many travels would you like to test?" << endl;
//    do{
//        cin >> travelsNum;
//    } while (check(travelsNum, "travelsNum") == NOT_LEGAL);
//
    Simulator simulator;
    int algorithmsNum = 1, travelsNum = 1;

    for (int i = 1; i <= algorithmsNum; ++i) {
        for (int j = 1; j <= travelsNum; ++j) {
            simulator.initSimulation(i, j); //Todo: change to vector?
        }
    }













//    ifstream inputFile ("C:\\example.txt");
//    std::vector<std::tuple<int, int, int>> vec = parseShipPlan(inputFile);
//    for (int i = 0; i < vec.size(); i++){
//        cout << "shipPlan [" << i << "][0] = " <<std::get<0>(vec[i]) << ", ";
//        cout << "shipPlan [" << i << "][1] = " <<std::get<1>(vec[i]) << ", ";
//        cout << "shipPlan [" << i << "][2] = " <<std::get<2>(vec[i]) << endl;
//    }
//
//    cout << "----------------------------------------------------------" << '\n';
//
//    string shipPlanFileName = "C:\\example.txt";
//    string shipRouteFileName = "C:\\example2.txt";
//    initSimulation(shipPlanFileName, shipRouteFileName);
//
//    cout << "----------------------------------------------------------" << '\n';
//
//    Container* cont1 = new Container(25, "X", "fiufie");
//    Container* cont2 = new Container(35, "Y", "dsjhdvsu");
//    vector<Container*> vec2;
//    vec2.push_back(cont1);
//    vec2.push_back(cont2);
//    Port port("asdf");
//    port.addContainersToUnload(vec2);
//    cout << port.getPortId() << endl;
//
//    free(cont1);
//    free(cont2);

    return EXIT_SUCCESS;
}
