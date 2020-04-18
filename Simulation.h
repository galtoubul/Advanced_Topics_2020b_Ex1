#include <vector>
#include <tuple>
#include <string>
#include "StowageAlgorithm.h"
using std::vector;
using std::tuple;

class Simulator{
    ShipPlan shipPlan;
    ShipRoute shipRoute;
public:
    Simulator () : shipPlan(), shipRoute() {}

    void initSimulation (int algorithmNum, int travelNum);

    void getInput(const string& shipPlanFileName, const string& shipRouteFileName);

    void startTravel ( Algorithm* algorithm, const string& travelName);

    friend std::ostream& operator<<(std::ostream& out, const Simulator& simulator);

    const ShipPlan& getShipPlan () const;

    const ShipRoute& getShipRoute() const;

};

//void initSimulation (string shipPlanFileName, string shipRouteFileName);
//
//void initShipPlan (ShipPlan *shipPlan, vector<tuple<int, int, int>> vecForShipPlan);
//
//void initShipRoute (ShipRoute* shipRoute, vector<string> vecForShipRoute);

