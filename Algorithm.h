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
Port* currPort;
WeightBalanceCalculator calculator;
bool isFinalPort = false;

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

    void setCurrPort(Port* port);

    Port* getCurrPort();

    void getInstructionsForCargo(const string& inputFileName, const string& outputFileName);

    vector<tuple<char,string,int,int,int,int,int,int>> runAlgorithmForPort(vector<Container*> containersAwaitingAtPort);

    void unloadToPort(Container* container, vector<tuple<char,string,int,int,int,int,int,int>>* instructions);

    void loadToShip(Container* container, vector<tuple<char,string,int,int,int,int,int,int>>* instructions);

    Port * findPortFromId(const string& portId);


};

class Algorithm1 : public Algorithm {

public:
    Algorithm1() : Algorithm() {}
};




