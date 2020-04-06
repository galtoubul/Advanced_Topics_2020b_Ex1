#include "Simulation.h"
#include "Parser.h"
using std::vector;
using std::tuple;
using std::get;

void initSimulation (string shipPlanFileName, string shipRouteFileName){
    ifstream shipPlanInputFile (shipPlanFileName);
    vector<tuple<int, int, int>> vecForShipPlan = parseShipPlan(shipPlanInputFile);
    int dimX = get<0>(vecForShipPlan[0]);
    int dimY = get<1>(vecForShipPlan[0]);
    int floorsNum = get<2>(vecForShipPlan[0]);
    ShipPlan shipPlan(dimX, dimY, floorsNum);
    initShipPlan(shipPlan, vecForShipPlan);
    shipPlan.printShipPlan();

    ifstream shipRouteInputFile (shipRouteFileName);
    list<Port> portsList = parsePortsList(shipRouteInputFile);
    ShipRoute shipRoute (portsList);
}

void initShipPlan (ShipPlan& shipPlan, vector<tuple<int, int, int>> vecForShipPlan){
    int floorsNum = get<0>(vecForShipPlan[0]);
    for (int i = 1; i < vecForShipPlan.size(); ++i) {
        int actualFloorNum = floorsNum - get<2>(vecForShipPlan[i]);
        for (int j = 0; j < actualFloorNum; j++){
            Container futileContainer{};
            shipPlan.insertContainer(futileContainer, get<0>(vecForShipPlan[i]), get<1>(vecForShipPlan[i]), j);
        }
    }
}

void initShipRoute (ShipRoute& shipRoute, vector<string> vecForShipRoute) {

}
