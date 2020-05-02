#include "WeightBalanceCalculator.h"
WeightBalanceCalculator::BalanceStatus WeightBalanceCalculator::tryOperation(char loadUnload, int kg, int X, int Y){
    if(loadUnload || kg || X || Y)
        return APPROVED;
    else
        return APPROVED;
}

