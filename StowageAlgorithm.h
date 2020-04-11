#include <tuple>
#include <string>
#include "ShipPlan.h"
#include "ShipRoute.h"
using std::vector;
using std::tuple;

vector<tuple<char,string,int,int,int,int,int,int>> runAlgorithmForPort(Port* port, vector<Container*> containersAwaitingAtPort, ShipPlan* shipPlan);

void unloadToPort(Container* container, Port* port, vector<tuple<char,string,int,int,int,int,int,int>>* instructions, ShipPlan *shipPlan);

void loadToShip(Container* container, Port* port, vector<tuple<char,string,int,int,int,int,int,int>>* instructions, ShipPlan *shipPlan);



