#include <fstream>
#include <vector>
#include <tuple>

using std::ifstream;

std::vector<std::tuple<int, int, int>> parseShipPlan(ifstream& inputFile);
