#include <iostream>
#include <algorithm>
#include <regex>
#include <filesystem>
#include "Parser.h"
using std::string;
using std::cout;
using std::vector;
using std::tuple;
using std::endl;
using std::list;
using std::ofstream;
using std::get;
#define NOT_A_COMMENT_LINE 0
#define COMMENT_LINE 1

void split(vector<string>& elems, const string &s, char delim) {
    auto result = std::back_inserter(elems);
    std::istringstream iss(s);
    string item;
    while (std::getline(iss, item, delim)) {
        if (!item.empty())
            *result++ = item;
    }
}

void validateShipPlanLine (const string& line){
    const std::regex regex("\\s*[0-9]\\s*[,]\\s*[0-9]\\s*[,]\\s*[0-9]\\s*");
    if (!(std::regex_match(line, regex))){
        INVALID_INPUT("ship plan")
        exit(EXIT_FAILURE);
    }
}

int isCommentOrWS (const string& line){
    const std::regex regex("\\s*[#].*");
    const std::regex regexWS(R"(\s*\t*\r*\n*)"); //TODO maybe isspace is a better choice
    if (std::regex_match(line, regex) || std::regex_match(line, regexWS))
        return COMMENT_LINE;
    return NOT_A_COMMENT_LINE;
}

 void Parser::readShipPlan (ShipPlan& shipPlan, const string& shipPlanFileName){
    ifstream shipPlanInputFile(shipPlanFileName);
    vector<tuple<int, int, int>> vecForShipPlan;
    string line;
    if (shipPlanInputFile.is_open()) {
        while (getline(shipPlanInputFile, line)) {
            if(isCommentOrWS(line))
                continue;

            validateShipPlanLine(line);
            vector<string> temp;
            split(temp, line, ',');
            vecForShipPlan.emplace_back(stoi(temp[0]), stoi(temp[1]), stoi(temp[2]));
        }
        shipPlanInputFile.close();
    } else{
        UNABLE_TO_OPEN_FILE(shipPlanFileName)
        exit(EXIT_FAILURE);
    }
    int floorsNum, dimX, dimY;
    std::tie(floorsNum, dimX, dimY) = vecForShipPlan[0];
    shipPlan = ShipPlan(dimX, dimY, floorsNum);

    for (size_t i = 1; i < vecForShipPlan.size(); ++i) {
        int blockedFloors = floorsNum - get<2>(vecForShipPlan[i]);
        for (int j = 0; j < blockedFloors; j++){
            Container* futileContainer = new Container();
            shipPlan.setContainers(get<0>(vecForShipPlan[i]), get<1>(vecForShipPlan[i]), j, futileContainer);
        }
    }
}

void checkIfValidPortId(string port){
    //have to be in model of: XX XXX - size 6
    const std::regex regex("\\s*[a-zA-z]{2}[ ][a-zA-z]{3}\\s*");
    if (!(std::regex_match(port, regex))){
        NON_LEGAL_SEA_PORT_CODE(port)
        exit(EXIT_FAILURE);
    }
}

// trim white spaces from left
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim white spaces from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim white spaces from left & right
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}

void Parser::readShipRoute(ShipRoute& shipRoute, const string& shipPlanFileName){
    ifstream shipRouteInputFile (shipPlanFileName);
    string line;
    int currPortInd = 0;
    if (shipRouteInputFile.is_open()){
        while (getline(shipRouteInputFile,line)){
            if(isCommentOrWS(line))
                continue;

            line = trim(line);
            checkIfValidPortId(line); //have to be in model of: XX XXX - size 6
            std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c){ return std::toupper(c);});

            //the same port can't appear in two consecutive lines
            if(!shipRoute.getPortsList().empty() && line == shipRoute.getPortsList()[currPortInd - 1].getPortId()){
                SAME_PORT_AS_PREV
                exit(EXIT_FAILURE);
            }

            shipRoute.addPort(line);
        }
        shipRouteInputFile.close();
    }
    else{
        UNABLE_TO_OPEN_FILE(shipPlanFileName)
        exit(EXIT_FAILURE);
    }
}

inline bool fileExists (const std::string& fileName) {
    ifstream f(fileName);
    return f.good();
}

void getPortFilesName(string& inputFileName, string& outputFileName, const string& portId, const int portVisitNum, const string& travelName, bool isFinalPort){
    string str;
    inputFileName = travelName + string(1, std::filesystem::path::preferred_separator) +
                    portId + "_" + std::to_string(portVisitNum) + ".cargo_data.txt";
    if (!fileExists(inputFileName) && !isFinalPort) {
        PORT_FILE_NAME_ISNT_MATCHING(inputFileName)
        exit (EXIT_FAILURE);
    }
    if (fileExists(inputFileName) && isFinalPort)
        LAST_PORT_WARNING
    outputFileName = travelName +  std::string(1, std::filesystem::path::preferred_separator) +
                     portId + '_' + std::to_string(portVisitNum) + ".instructions_for_cargo.txt";
}

void validateContainerId (const string& line){
    const std::regex regex("\\s*[A-Z]{3}[UJZ][0-9]{7}\\s*");
    if (!(std::regex_match(line, regex))){
        CONTAINER_ERROR("id")
        exit(EXIT_FAILURE);
    }
}

void validateWeight (const string& line){
    const std::regex regex("\\s*[0-9]*\\s*");
    if (!(std::regex_match(line, regex))){
        CONTAINER_ERROR("weight")
        exit(EXIT_FAILURE);
    }
}

bool validateContainersAwaitingAtPortLine (vector<string>& line) {
    if (line.size() != 3) {
        INVALID_INPUT("Containers awaiting at port")
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 3; ++i)
        trim(line[i]);
    validateContainerId(line[0]);
    validateWeight(line[1]);
    checkIfValidPortId(line[2]);
 //   return portInRoute(shipRoute, line[2]);
    return true;
}

void readContainersAwaitingAtPort (const string& inputFileName, vector<Container*>& containersAwaitingAtPort, bool isFinalPort){
    ifstream inputFile (inputFileName);
    string line;
    if (inputFile.is_open()){
        while (getline(inputFile, line)){
            vector<string> temp;
            split(temp, line, ',');
            if(isCommentOrWS(line))
                continue;

            if(!validateContainersAwaitingAtPortLine(temp))
                continue;

            //port id to uppercase
            std::transform(temp[2].begin(), temp[2].end(), temp[2].begin(),
                           [](unsigned char c){ return std::toupper(c);});
            containersAwaitingAtPort.push_back(new Container(stoi(temp[1]), temp[2], temp[0], false));
        }
        inputFile.close();
    }
    else if (!isFinalPort){
        UNABLE_TO_OPEN_FILE(inputFileName)
        exit(EXIT_FAILURE);
    }
}

void writeInstructionsToFile(vector<INSTRUCTION>& instructions, ofstream& instructionsForCargoFile)
{
    for (INSTRUCTION instruction : instructions){
        instructionsForCargoFile << get<0>(instruction) <<", " << get<1>(instruction);
        if (get<0>(instruction) == 'R'){
            instructionsForCargoFile << "\n";
            continue;
        }
        instructionsForCargoFile << ", " << get<2>(instruction) <<", "
                                 << get<3>(instruction) << ", "<< get<4>(instruction) << "\n";
    }
    instructionsForCargoFile << std::endl;
    instructionsForCargoFile.close();
}

int findPortIndex(const ShipRoute& shipRoute, const string& portSymbol, int currPortIndex){
    for (int i = currPortIndex +1; (size_t)i < shipRoute.getPortsList().size(); i++) {
        if (shipRoute.getPortsList()[i].getPortId() == portSymbol)
            return i;
    }
    return NOT_IN_ROUTE;
}

vector<Container*> orderContainersByDest(vector<Container*>& containersAwaitingAtPort, ShipRoute& shipRoute, int currPortIndex){
    vector<Container*> newContainersAwaitingAtPort;
    for (size_t i = currPortIndex + 1; i < shipRoute.getPortsList().size(); i++){
        for (Container* container : containersAwaitingAtPort){
            string destPort = container->getDestination();
            if (findPortIndex(shipRoute, destPort, (int)currPortIndex) == (int)i)
                newContainersAwaitingAtPort.push_back(container);
        }
    }
    return newContainersAwaitingAtPort;
}

void getInstructionsForPort(const string& outputFileName, vector<INSTRUCTION>& instructions) {
    ifstream outputFile(outputFileName);
    string line;
    if (outputFile.is_open()) {
        while (getline(outputFile, line)) {
            vector<string> temp;
            split(temp, line, ',');
            if(temp.size() < 5)
                continue;
            instructions.emplace_back(temp[0]. at(0), temp[1], stoi(temp[2]), stoi(temp[3]), stoi(temp[4]));
        }
        outputFile.close();
    } else {
        UNABLE_TO_OPEN_FILE(outputFileName)
        exit(EXIT_FAILURE);
    }
}