#include <fstream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include "ShipRoute.h"
#include "ShipPlan.h"
#include "WeightBalanceCalculator.h"
#include "ErrorsInterface.h"
using std::ifstream;
using std::ofstream;
using std::tuple;
#define INSTRUCTION tuple<char,string,int,int,int>
#define REJECT 'R'

void readShipPlan (ShipPlan& shipPlan, const string& shipPlanFileName);

void readShipRoute(ShipRoute& shipRoute, const string& shipPlanFileName);

void readContainersAwaitingAtPort (const string& inputFileName, vector<Container*>& containersAwaitingAtPort, bool isFinalPort = false);

void writeInstructionsToFile(vector<INSTRUCTION>& instructions, ofstream& instructionsForCargoFile);

void getPortFilesName(string& inputFileName, string& outputFileName, const string& portId, const int currPortIndex, const string& travelName, bool isFinalPort);

int findPortIndex(const ShipRoute& shipRoute, const string& portSymbol, int currPortIndex);

vector<Container*> orderContainersByDest(vector<Container*>& containersAwaitingAtPort, ShipRoute& shipRoute, int currPortIndex);

void getInstructionsForPort(const string& outputFileName, vector<INSTRUCTION>& instructions);
