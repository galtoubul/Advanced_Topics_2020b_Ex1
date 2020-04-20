#include <fstream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include "ShipRoute.h"
#include "ShipPlan.h"
#include "WeightBalanceCalculator.h"
#define INSTRUCTION tuple<char,string,int,int,int>
using std::ifstream;
using std::ofstream;
using std::tuple;

void readShipPlan (ShipPlan& shipPlan, const string& shipPlanFileName);

void readShipRoute(ShipRoute& shipRoute, const string& shipPlanFileName);

void readContainersAwaitingAtPort (const string& inputFileName, vector<Container*>& containersAwaitingAtPort);

string extPortIdFromFileName(string input_full_path_and_file_name);

//bool checkIfValidContainer(Container* container);

bool portInRoute(ShipRoute& shipRoute, string& portId);

void writeInstructionsToFile(vector<INSTRUCTION>& instructions, ofstream& instructionsForCargoFile);

void getPortFilesName(string& inputFileName, string& outputFileName, const string& portId, const int currPortIndex, const string& travelName);




