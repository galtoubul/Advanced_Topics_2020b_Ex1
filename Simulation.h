#include <vector>
#include <tuple>
#include <string>
#include "ShipPlan.h"
#include "ShipRoute.h"
using std::vector;
using std::tuple;

void initSimulation (string shipPlanFileName, string shipRouteFileName);

void initShipPlan (ShipPlan *shipPlan, vector<tuple<int, int, int>> vecForShipPlan);

void initShipRoute (ShipRoute* shipRoute, vector<string> vecForShipRoute);

void getInstructionsForCargo(string input_full_path_and_file_name, string output_full_path_and_file_name);

