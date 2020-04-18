#include <tuple>
#include <string>
#include <vector>
#include "Parser.h"
using std::vector;
using std::tuple;
using std::string;

class Algorithm {

ShipPlan shipPlan;
ShipRoute shipRoute;
WeightBalanceCalculator calculator;

public:
    enum algorithmName {algorithm1 = 1};

    Algorithm () : shipPlan(), shipRoute(), calculator() {}

    static Algorithm* createAlgorithm (int algorithmNum);

    void getInput(const string& shipPlanFileName, const string& shipRouteFileName){
        readShipPlan(this->shipPlan, shipPlanFileName);
        readShipRoute(this->shipRoute, shipRouteFileName);
    }

//    void readShipRoute(const std::string& full_path_and_file_name);
    void setWeightBalanceCalculator(WeightBalanceCalculator& _calculator);

    void getInstructionsForCargo(const string& inputFileName, const string& outputFileName);

    };

class Algorithm1 : public Algorithm {

public:
    Algorithm1() : Algorithm() {}
};

//vector<tuple<char,string,int,int,int,int,int,int>> runAlgorithmForPort(Port* port, vector<Container*> containersAwaitingAtPort, ShipPlan* shipPlan, ShipRoute* shipRoute, int  currPortI);
//
//void unloadToPort(Container* container, Port* port, vector<tuple<char,string,int,int,int,int,int,int>>* instructions, ShipPlan *shipPlan);
//
//void loadToShip(Container* container, Port* port, vector<tuple<char,string,int,int,int,int,int,int>>* instructions, ShipPlan *shipPlan, ShipRoute* shipRoute);



