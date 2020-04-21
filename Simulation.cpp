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

void Simulator::initSimulation (int algorithmNum, int travelNum){
    string travelName = "Travel" + std::to_string(travelNum);
    std::cout << "Starting travel: "<< travelName << std:: endl;

    string shipPlanPath = travelName +  std::string(1, std::filesystem::path::preferred_separator) + "Ship Plan.txt";
    string shipRoutePath = travelName + std::string(1, std::filesystem::path::preferred_separator) + "Route.txt";
    this->getInput(shipPlanPath, shipRoutePath);

    Algorithm* algorithm = Algorithm::createAlgorithm(algorithmNum);
    algorithm->getInput(shipPlanPath, shipRoutePath);

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
}

void Simulator::setWeightBalanceCalculator(WeightBalanceCalculator& _calculator){
    this->calculator = _calculator;
}

void Simulator::getInput(const string& shipPlanFileName, const string& shipRouteFileName){
    readShipPlan(this->shipPlan, shipPlanFileName);
    readShipRoute(this->shipRoute, shipRouteFileName);
}

int Simulator::checkLoadInstruction(int x, int y, int floor, Container* container){
    cout << "inside checkLoadInstruction" << endl;
//    cout << container->getId() << endl;

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
    } else if (!calculator.tryOperation(LOAD, container->getWeight(), x, y)){
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
    if (shipPlan.getContainers()[x][y][floor] == nullptr){
        NOT_LEGAL_OPERATION("Unloading", container->getId(), floor, x, y, "this location isn't contain any container")
        return ERROR;
    } else if (shipPlan.getContainers()[x][y][floor]->isFutile()){
        NOT_LEGAL_OPERATION("Unloading", container->getId(), floor, x, y, "this location is blocked")
        return ERROR;
    } else if (floor != (int)shipPlan.getContainers()[x][y].size() - 1 && shipPlan.getContainers()[x][y][floor + 1] != nullptr){
        NOT_LEGAL_OPERATION("Unloading", container->getId(), floor, x, y, "there are containers above the unloaded container")
        return ERROR;
    } else if (!calculator.tryOperation(LOAD, container->getWeight(), x, y)){
        NOT_LEGAL_OPERATION("Unloading", container->getId(), floor, x, y, "the operation isn't approved by the weight balance calculator")
        return ERROR;
    }
    else {
        this->shipPlan.setContainers(x, y, floor, nullptr);
        containersAwaitingAtPort.push_back(new Container(container));
        return VALID;
    }
}

//Todo: consider exploring the source of the trimming bug instead of just hardcoding
// trim white spaces from left
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
        Simulator::algorithmActionsCounter++;
        char instructionType;
        string containerId;
        int x, y, floor;
        std::tie(instructionType, containerId, floor, x, y) = instruction;

        Container *container = nullptr;

        switch (instructionType) {
            case LOAD: {
//                cout << "searching for container ." << ltrim(containerId) << ". :" << endl;
                for (Container *_container : containersAwaitingAtPort) {
//                    cout << "   " << *_container << endl;
                    if (_container->getId() == ltrim(containerId)) {
                        container = _container;
                        break;
                    }
//                    else
//                        cout << "   ." << _container->getId() << ". != ." << ltrim(containerId) << "." << endl;
                }
                if (container == nullptr) {
                    NOT_LEGAL_OPERATION("Loading", containerId, floor, x, y,
                                        "this container isn't exist at " + currPortSymbol)
                    return ERROR;
                }
                return checkLoadInstruction(x, y, floor, container);
            }
            case UNLOAD: {
                container = shipPlan.getContainers()[x][y][floor];
                return checkUnloadInstruction(x, y, floor, container, containersAwaitingAtPort);
            }
        }
    }

    for (Container* _container : containersAwaitingAtPort) {
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
                if (this->shipPlan.getContainers()[x][y][floor]->getDestination() == currPortSymbol){
                    CONTAINER_WASNT_DROPPED(currPortSymbol)
                    return ERROR;
                }
            }
        }
    }
    return VALID;

//    for (int i = instructions.size() - 1; i > 0; i--){
//        if(get<0>(instructions[i]) == UNLOAD &&
//           shipPlan.getContainers()[get<4>(instructions[i])][get<2>(instructions[i])][get<3>(instructions[i])]->getDestination() != currPortSymbol){
//            CONTAINER_FORGOTTEN(currPortSymbol)
//            return ERROR;
//        }
//    }
}

int Simulator::startTravel (Algorithm* algorithm, const string& travelName){
    size_t currPortIndex = BEFORE_FIRST_PORT;
    Simulator::algorithmActionsCounter = 0;
    for (const Port& port : this->shipRoute.getPortsList()){
        cout << "now in port " << port.getPortId() << endl;

        Algorithm::currPortIndex = ++currPortIndex;
        cout << "Algorithm's currPortIndex: " << Algorithm::currPortIndex << " Simulator's currPortIndex:" << currPortIndex << endl;

        string inputFileName, outputFileName;
        bool isFinalPort = (size_t)currPortIndex == this->shipRoute.getPortsList().size() - 1;
        getPortFilesName(inputFileName, outputFileName, port.getPortId(), currPortIndex, travelName, isFinalPort);

        vector<Container*> containersAwaitingAtPort;
        readContainersAwaitingAtPort(inputFileName, containersAwaitingAtPort);

        cout << "Simulator -- There are "<< containersAwaitingAtPort.size() << " containers awaiting at port " << port.getPortId() << " :" << endl;
        for (Container* container : containersAwaitingAtPort)
            std::cout << *container << std:: endl;

        if (isFinalPort && !containersAwaitingAtPort.empty())
            LAST_PORT_WARNING

        //????????
//        int slots = freeSlotsInShip();
//        for (Container* container : containersAwaitingAtPort){
//            if (slots == 0)
//                break;
//
//            string destPort = container->getDestination();
//            int indexOfDestPort = findPortIndex(this->shipRoute, destPort, currPortIndex);
//            if (indexOfDestPort == NOT_IN_ROUTE)
//                continue;
//
//            (const_cast<Port&>(this->shipRoute.getPortsList()[indexOfDestPort])).addContainerToUnloadToPort(container);
//            slots--;
//        }

        cout << "Simulator -- There are "<< port.getContainersToUnload().size() << " containers to unload to port " << port.getPortId() << " :" << endl;
        for (Container* container : port.getContainersToUnload())
            cout << *container << endl;

        algorithm->getInstructionsForCargo(inputFileName, outputFileName);
        this->shipPlan.printShipPlan();
        int status = checkAndCountAlgorithmActions(containersAwaitingAtPort, outputFileName, port.getPortId());
        cout << "after checkAndCountAlgorithmActions" << endl;
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