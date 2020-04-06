#include <fstream>
#include <vector>
#include <list>
#include <tuple>

using std::ifstream;

std::vector<std::tuple<int, int, int>> parseShipPlan(ifstream& inputFile);

std::list<Port> parsePortsList (ifstream& inputFile);
