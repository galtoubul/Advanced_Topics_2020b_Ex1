#include <tuple>
#define UNLOAD 'U'
#define LOAD 'L'
#pragma once

class WeightBalanceCalculator {
public:
    enum BalanceStatus {
        APPROVED , X_IMBALANCED , Y_IMBALANCED , X_Y_IMBALANCED
    };

    BalanceStatus tryOperation(char loadUnload, int kg, int X, int Y);
};