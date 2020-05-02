#include <string>
#include <iostream>
#include <filesystem>
#include "Simulation.h"

using std::vector;
using std::tuple;
using std::get;
using std::ofstream;
using std::string;
using std::cout;
using std::endl;
#define ERROR -1
#define VALID 1

int Simulator::algorithmActionsCounter;
size_t Simulator::currPortIndex;

inline void clearData(ShipPlan& shipPlan, ShipRoute& shipRoute){
    const_cast<VVVC&>(shipPlan.getContainers()).clear();
    const_cast<vector<Port>&>(shipRoute.getPortsList()).clear();
}

void Simulator::initSimulation (int algorithmNum, int travelNum){
    string travelName = "Travel" + std::to_string(travelNum);
    std::cout << "Starting "<< travelName << ": for algorithm" << algorithmNum << std:: endl;

    string shipPlanPath = travelName +  std::string(1, std::filesystem::path::preferred_separator) + "Ship Plan.txt";
    string shipRoutePath = travelName + std::string(1, std::filesystem::path::preferred_separator) + "Route.txt";
    this->getInput(shipPlanPath, shipRoutePath);

    Algorithm1* algorithm = new Algorithm1(); // TODO: use polymorphism
    algorithm->readShipPlan(shipPlanPath);
    algorithm->readShipRoute(shipRoutePath);

    WeightBalanceCalculator _calculator;
    algorithm->setWeightBalanceCalculator(_calculator);
    setWeightBalanceCalculator(_calculator);

    int status = startTravel(algorithm, travelName);

    if (status == ERROR)
        cout << travelName << " was ended with an error for algorithm" << algorithmNum
        << " .The number of algorithm operations: " << algorithmActionsCounter << endl;
    else
        cout << travelName << " was ended successfully for algorithm" << algorithmNum
        << " .The number of algorithm operations: " << algorithmActionsCounter << endl;

    clearData(this->shipPlan, this->shipRoute);
}

void Simulator::setWeightBalanceCalculator(WeightBalanceCalculator& _calculator){
    this->calculator = _calculator;
}

void Simulator::getInput(const string& shipPlanFileName, const string& shipRouteFileName){
    Parser::readShipPlan(this->shipPlan, shipPlanFileName);
    Parser::readShipRoute(this->shipRoute, shipRouteFileName);
}

int Simulator::checkLoadInstruction(int x, int y, int floor, Container* container){
    if(shipPlan.getContainers()[x][y][floor] != nullptr && shipPlan.getContainers()[x][y][floor]->isFutile()){
        NOT_LEGAL_OPERATION("Loading", container->getId(), floor, x, y, "this location is blocked")
        return ERROR;
    } else if (shipPlan.getContainers()[x][y][floor] != nullptr && !shipPlan.getContainers()[x][y][floor]->isFutile()){
        NOT_LEGAL_OPERATION("Loading", container->getId(), floor, x, y, "this location is occupied by another container")
        cout << shipPlan.getContainers()[x][y][floor]->getId() << endl;
        return ERROR;
    }else if (shipPlan.getContainers()[x][y][floor - 1] == nullptr){
        NOT_LEGAL_OPERATION("Loading", container->getId(), floor, x, y, "there isn't any container under the loaded container")
        return ERROR;
    } else if (calculator.tryOperation('L', container->getWeight(), x, y) != WeightBalanceCalculator::APPROVED){
        NOT_LEGAL_OPERATION("Loading", container->getId(), floor, x, y, "the operation isn't approved by the weight balance calculator")
        return ERROR;
    }
    else{
        this->shipPlan.setContainers(x, y, floor, new Container(container));
        delete(container);
        return VALID;
    }
}

int Simulator::checkUnloadInstruction(int x, int y, int floor, Container* container, vector<Container*>& containersAwaitingAtPort){
    if (shipPlan.getContainers()[x][y][floor]->isFutile()){
        NOT_LEGAL_OPERATION("Unloading", container->getId(), floor, x, y, "this location is blocked")
        return ERROR;
    } else if (floor != (int)shipPlan.getContainers()[x][y].size() - 1 && shipPlan.getContainers()[x][y][floor + 1] != nullptr){
        NOT_LEGAL_OPERATION("Unloading", container->getId(), floor, x, y, "there are containers above the unloaded container")
        return ERROR;
    } else if (calculator.tryOperation('L', container->getWeight(), x, y) != WeightBalanceCalculator::APPROVED){
        NOT_LEGAL_OPERATION("Unloading", container->getId(), floor, x, y, "the operation isn't approved by the weight balance calculator")
        return ERROR;
    }
    else {
        this->shipPlan.setContainers(x, y, floor, nullptr);
        containersAwaitingAtPort.push_back(new Container(container));
        return VALID;
    }
}

inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

int Simulator::checkAndCountAlgorithmActions(vector<Container*>& containersAwaitingAtPort, const string& outputFileName,
                                              const string& currPortSymbol){
    vector<INSTRUCTION> instructions;
    getInstructionsForPort(outputFileName, instructions);
    for (INSTRUCTION instruction : instructions) {
        char instructionType;
        string containerId;
        int x, y, floor;
        std::tie(instructionType, containerId, floor, x, y) = instruction;

        Container *container = nullptr;

            if (instructionType == 'L'){
                algorithmActionsCounter++;
                vector<Container*> currContainersAwaitingAtPort = containersAwaitingAtPort;
                int locInVec = -1;
                for (Container *_container : currContainersAwaitingAtPort) {
                    locInVec++;
                    if (_container->getId() == ltrim(containerId)) {
                        container = _container;
                        break;
                    }
                }
                containersAwaitingAtPort.erase(containersAwaitingAtPort.begin()+locInVec);
                if (container == nullptr) {
                    NOT_LEGAL_OPERATION("Loading", containerId, floor, x, y,"this container isn't exist at " + currPortSymbol)
                    return ERROR;
                }
                if (checkLoadInstruction(x, y, floor, container) == ERROR)
                    return ERROR;
                continue;
            }
            else if (instructionType == 'U'){
                algorithmActionsCounter++;
                container = shipPlan.getContainers()[x][y][floor];
                if (container == nullptr) {
                    NOT_LEGAL_OPERATION("Unloading", containerId, floor, x, y,"this container isn't exist at Ship")
                    return ERROR;
                }
                if (checkUnloadInstruction(x, y, floor, container, containersAwaitingAtPort) == ERROR)
                    return ERROR;
            }
        }

    for (Container* _container : containersAwaitingAtPort) {
        if (findPortIndex(shipRoute, currPortSymbol, currPortIndex) == NOT_IN_ROUTE)
            continue;
        if (_container->getDestination() != currPortSymbol){
            if(freeSlotsInShip() > 0){
                CONTAINER_FORGOTTEN(currPortSymbol)
                return ERROR;
            }
        }
    }

    for (int x = 0; x < this->shipPlan.getPivotXDimension(); x++){
        for (int y = 0; y < this->shipPlan.getPivotYDimension(); y++){
            for (int floor = 0; floor < this->shipPlan.getFloorsNum(); floor++){
                if (this->shipPlan.getContainers()[x][y][floor] != nullptr &&
                this->shipPlan.getContainers()[x][y][floor]->getDestination() == currPortSymbol){
                    CONTAINER_WASNT_DROPPED(currPortSymbol)
                    return ERROR;
                }
            }
        }
    }
    return VALID;
}

int Simulator::startTravel (AbstractAlgorithm* algorithm, const string& travelName){
    Simulator::currPortIndex = 0;
    Simulator::algorithmActionsCounter = 0;
    for (const Port& port : this->shipRoute.getPortsList()){
        Simulator::currPortIndex++;
        string inputFileName, outputFileName;
        bool isFinalPort = currPortIndex == this->shipRoute.getPortsList().size();

        //finding portVisitNum
        int portVisitNum = 0;
        for (size_t i = 0; i <= Simulator::currPortIndex; ++i) {
            if (this->shipRoute.getPortsList()[i].getPortId() == port.getPortId())
                portVisitNum++;
        }

        getPortFilesName(inputFileName, outputFileName, port.getPortId(), portVisitNum, travelName, isFinalPort);

        vector<Container*> containersAwaitingAtPort;
        // TODO: readContainersAwaitingAtPort even if final port -> and if it isn't empty mark as error
        if (!isFinalPort)
            readContainersAwaitingAtPort(inputFileName, containersAwaitingAtPort);

        algorithm->getInstructionsForCargo(inputFileName, outputFileName);
        int status = checkAndCountAlgorithmActions(containersAwaitingAtPort, outputFileName, port.getPortId());
        if (status == VALID)
            continue;
    }
    return VALID;
}

const ShipPlan& Simulator::getShipPlan () const{
    return this->shipPlan;
}

const ShipRoute& Simulator::getShipRoute() const{
    return this->shipRoute;
}

std::ostream& operator<<(std::ostream& out, const Simulator& simulator){
    out << "Ship Plan: " << '\n';
    simulator.getShipPlan().printShipPlan();
    out << simulator.getShipRoute() << '\n';
    return out;
}

int Simulator::freeSlotsInShip() {
    int counter = 0;
    for (int x = 0; x < this->shipPlan.getPivotXDimension(); x++)
        for (int y = 0; y < this->shipPlan.getPivotYDimension(); y++)
            for (int floor = 0; floor < this->shipPlan.getFloorsNum(); floor++)
                if (this->shipPlan.getContainers()[x][y][floor] == nullptr)
                    counter++;
    return counter;
}