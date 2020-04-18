#include <fstream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include "Common.h"
using std::ifstream;
using std::ofstream;
using std::tuple;

void readShipPlan (ShipPlan& shipPlan, const string& shipPlanFileName);

void readShipRoute(ShipRoute& shipRoute, const string& shipPlanFileName);

void readContainersAwaitingAtPort (const string& inputFileName, vector<Container*>& containersAwaitingAtPort, const ShipRoute& shipRoute);

string extPortIdFromFileName(string input_full_path_and_file_name);

bool checkIfValidContainer(Container* container);

void writeInstructionsToFile( vector<tuple<char,string,int,int,int,int,int,int>>& instructions, ofstream& instructionsForCargoFile);

void getPortFilesName(string& inputFileName, string& outputFileName, const string& portId, const int currPortIndex, const string& travelName);




