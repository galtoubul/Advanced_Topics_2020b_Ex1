#include <tuple>
#include <string>
#include <vector>
#include "Parser.h"
using std::vector;
using std::tuple;
using std::string;
#define BEFORE_FIRST_PORT -1

class Algorithm {

protected:
    ShipPlan shipPlan;
    ShipRoute shipRoute;
    WeightBalanceCalculator calculator;

public:
    static size_t currPortIndex;

    enum algorithmName {algorithm1 = 1};

    Algorithm () : shipPlan(), shipRoute(), calculator() {}

    static Algorithm* createAlgorithm (int algorithmNum);

    void getInput(const string& shipPlanFileName, const string& shipRouteFileName){
        readShipPlan(this->shipPlan, shipPlanFileName);
        readShipRoute(this->shipRoute, shipRouteFileName);
    }

    void setWeightBalanceCalculator(WeightBalanceCalculator& _calculator);

    virtual void getInstructionsForCargo(const string& inputFileName, const string& outputFileName)=0;

};

class Algorithm1 : public Algorithm {

public:
    Algorithm1() : Algorithm() {}

    void getInstructionsForCargo(const string& inputFileName, const string& outputFileName);

    void getUnloadingInstructions(vector<INSTRUCTION>& instructions);

    void getLoadingInstructions(vector<INSTRUCTION>& instructions, vector<Container*> containersAwaitingAtPort);

    void unloadToPort(Container* container, vector<INSTRUCTION>& instructions);

    void loadToShip(Container* container, vector<INSTRUCTION>& instructions);
};




