#include <tuple>
#define UNLOAD 'U'
#define LOAD 'L'
class WeightBalanceCalculator{
public:
    WeightBalanceCalculator() {}
    bool tryOperation(char command, int weight, int x, int y);
};