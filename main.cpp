#include <cstdlib>
#include <tuple>
#include <iostream>
#include "Simulation.h"

using std::cout;
using std::cin;
using std::endl;
#define NOT_LEGAL -1
#define LEGAL 1

int check(int num, const std::string& mode){
    if (num < 0){
        TRAVELS_OR_ALGORITHMS_NUMBER_ERROR(mode)
        cout << "Please reenter the number you would like to test" << endl;
        return NOT_LEGAL;
    }
    return LEGAL;
}

int main() {
    cout << "Welcome to Stowage Algorithm Simulator" << endl;
    cout << "How many algorithms would you like to test?" << endl;
    int algorithmsNum, travelsNum;
    do{
        cin >> algorithmsNum;
    } while (check(algorithmsNum, "algorithms") == NOT_LEGAL);
    cout << "How many travels would you like to test?" << endl;
    do{
        cin >> travelsNum;
    } while (check(travelsNum, "travels") == NOT_LEGAL);

    ErrorsInterface::populateErrorsMap();

    Simulator simulator;

    for (int i = 1; i <= algorithmsNum; ++i) {
        for (int j = 1; j <= travelsNum; ++j) {
            simulator.initSimulation(i, j);
        }
    }

    return EXIT_SUCCESS;
}
