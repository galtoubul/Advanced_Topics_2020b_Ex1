#pragma once

#include <vector>
#include <tuple>
#include <string>
#include "../Algorithm/_308394642_a.h"
using std::vector;
using std::tuple;

class Simulator{
    ShipPlan shipPlan;
    ShipRoute shipRoute;
    WeightBalanceCalculator calculator;

public:
    static int algorithmActionsCounter;

    static size_t currPortIndex;

    Simulator() : shipPlan(), shipRoute() {}

    void initSimulation (int algorithmNum, int travelNum);

    void setWeightBalanceCalculator(WeightBalanceCalculator& _calculator);

    void getInput(const string& shipPlanFileName, const string& shipRouteFileName);

    int startTravel (AbstractAlgorithm* algorithm, const string& travelName);

    friend std::ostream& operator<<(std::ostream& out, const Simulator& simulator);

    const ShipPlan& getShipPlan () const;

    const ShipRoute& getShipRoute() const;

    int freeSlotsInShip ();

    int checkAndCountAlgorithmActions(vector<Container*>& containersAwaitingAtPort,
            const string& outputFileName, const string& portSymbol);

    int checkLoadInstruction(int x, int y, int floor, Container* container);

    int checkUnloadInstruction(int x, int y, int floor, Container* container,
            vector<Container*>& containersAwaitingAtPort);
};
