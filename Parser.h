#include <fstream>
#include <vector>
#include <list>
#include <tuple>

using std::ifstream;
using std::ofstream;
using std::tuple;

std::vector<tuple<int, int, int>> readShipPlan(const string& full_path_and_file_name);

std::list<Port> readShipRoute(const string& full_path_and_file_name);

std::vector<Container*> parseContainerVecOfPort (ifstream& inputFile);

string extPortIdFromFileName(string input_full_path_and_file_name);

bool checkIfValidPortId(string port);

bool checkIfValidContainer(Container* container);

void writeInstructionsToFile( vector<tuple<char,string,int,int,int,int,int,int>>& instructions, ofstream& instructionsForCargoFile);