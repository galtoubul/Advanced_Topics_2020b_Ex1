#include <sstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include <filesystem>
#include "Parser.h"
#define NOT_A_COMMENT_LINE 0
#define COMMENT_LINE 1
using std::string;
using std::cout;
using std::vector;
using std::tuple;
using std::endl;
using std::list;
using std::ofstream;
using std::get;

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
        cout << "ship plan input isn't valid. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

int isComment (const string& line){
    const std::regex regex("\\s*[#].*");
    if (std::regex_match(line, regex))
        return COMMENT_LINE;
    return NOT_A_COMMENT_LINE;
}

void readShipPlan (ShipPlan& shipPlan, const string& shipPlanFileName){
    ifstream shipPlanInputFile(shipPlanFileName);
    vector<tuple<int, int, int>> vecForShipPlan;
    string line;
    if (shipPlanInputFile.is_open()) {
        while (getline(shipPlanInputFile, line)) {
            if(isComment(line))
                continue;

            validateShipPlanLine(line);
            vector<string> temp;
            split(temp, line, ',');
            vecForShipPlan.emplace_back(stoi(temp[0]), stoi(temp[1]), stoi(temp[2]));
        }
        shipPlanInputFile.close();
    } else{
        cout << "Unable to open file: " << shipPlanFileName << " Exiting..." << endl;
        exit(EXIT_FAILURE); //TODO: change some of exits to return/exception
    }

    int dimX = get<1>(vecForShipPlan[0]);
    int dimY = get<2>(vecForShipPlan[0]);
    int floorsNum = get<0>(vecForShipPlan[0]);
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
//    return port.size() == 6 && port.at(2) == ' ' && isalpha(port.at(0)) && isalpha(port.at(1)) &&
//           isalpha(port.at(3)) && isalpha(port.at(4)) && isalpha(port.at(5));
    const std::regex regex("\\s*[a-zA-z]{2}[ ][a-zA-z]{3}\\s*");
    if (!(std::regex_match(port, regex))){
        cout << "Ship route input isn't valid. It contains a line with non legal seaport code: " << port << ". Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

//string trim(string& str){
//    size_t first = str.find_first_not_of(' ');
//    if (string::npos == first)
//        return str;
//
//    size_t last = str.find_last_not_of(' ');
//    return str.substr(first, (last - first + 1));
//}

inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}

void readShipRoute(ShipRoute& shipRoute, const string& shipPlanFileName){
    ifstream shipRouteInputFile (shipPlanFileName);
    string line;
    list<Port*> portsList;
    if (shipRouteInputFile.is_open()){
        while (getline(shipRouteInputFile,line)){
            if(isComment(line))
                continue;

            line = trim(line);
            checkIfValidPortId(line); //have to be in model of: XX XXX - size 6
            std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c){ return std::toupper(c);});
            //the same port can't appear in two consecutive lines
            if(portsList.size() > 0 && line == portsList.back()->getPortId()){
                cout << "Ship route input isn't valid. It contains the same port in two consecutive lines. Exiting..." << endl;
                exit(EXIT_FAILURE);
            }
            Port* existPrevPort = nullptr;
            for (Port* prevPort : portsList){
                if (prevPort->getPortId() == line){
                    existPrevPort = prevPort; //we want a pointer to the same port in memory
                    break;
                }
            }
            if (existPrevPort == nullptr){
                Port* newPort = new Port(line); //TODO: free allocations
                portsList.push_back(newPort);
            }
            else{
                portsList.push_back(existPrevPort);
            }
        }
        shipRouteInputFile.close();
    }
    else{
        cout << "Unable to open file: " << shipPlanFileName << " Exiting..." << endl;
        exit(EXIT_FAILURE); //TODO: change some of exits to return/exception
    }

    shipRoute = portsList;
}

bool fileExists (const std::string& fileName) { //TODO: try to make it an inline function without linkers errors
    ifstream f(fileName);
    return f.good();
}

void getPortFilesName(string& inputFileName, string& outputFileName, const string& portId, const int currPortIndex, const string& travelName, bool isFinalPort){
    string str;
    inputFileName = travelName + string(1, std::filesystem::path::preferred_separator) +
                    portId + "_" + std::to_string(currPortIndex) + ".cargo_data.txt";
    if (!isFinalPort && !fileExists(inputFileName)) {
        std::cout << "There isn't any port file name matching " << inputFileName << " .Exiting..." << std::endl;
        exit (EXIT_FAILURE);
    }
    outputFileName = travelName +  std::string(1, std::filesystem::path::preferred_separator) +
                     portId + '_' + std::to_string(currPortIndex) + ".instructions_for_cargo.txt";
}

void validateContainerId (const string& line){
    const std::regex regex("\\s*[A-Z]{3}[UJZ][0-9]{7}\\s*");
    if (!(std::regex_match(line, regex))){
        cout << "Conatiner's id input isn't valid. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

void validateWeight (const string& line){
    const std::regex regex("\\s*[0-9]*\\s*");
    if (!(std::regex_match(line, regex))){
        cout << "Conatiner's weight input isn't valid. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

bool portInRoute(ShipRoute& shipRoute, string& portId){ //TODO: check the scenario of a port which was already visited
    for (Port* port : shipRoute.getPortList()) {
        if (port->getPortId() == portId)
            return true;
    }
    cout << portId << " is not in route" << endl;
    return false;
}

bool validateContainersAwaitingAtPortLine (vector<string>& line) {
    if (line.size() != 3) {
        cout << "Containers awaiting at port input isn't valid. Exiting..." << endl;
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

void readContainersAwaitingAtPort (const string& inputFileName, vector<Container*>& containersAwaitingAtPort){
    ifstream inputFile (inputFileName);
    string line;
    if (inputFile.is_open()){
        while (getline(inputFile, line)){
            vector<string> temp;
            split(temp, line, ',');
            if(isComment(line))
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
    else{
        cout << "Unable to open file: " << inputFileName << " Exiting..." << endl;
        exit(EXIT_FAILURE); //TODO: change some of exits to return/exception
    }
}

void writeInstructionsToFile( vector<tuple<char,string,int,int,int,int,int,int>>& instructions, ofstream& instructionsForCargoFile)
{
    for (tuple<char,string,int,int,int,int,int,int> instruction : instructions){
        instructionsForCargoFile << get<0>(instruction) <<", " << get<1>(instruction);
        if (get<0>(instruction) == 'R'){
            instructionsForCargoFile << "\n";
            continue;
        }
        instructionsForCargoFile << ", " << get<2>(instruction) <<", "
                                 << get<3>(instruction) << ", "<< get<4>(instruction);
        if (get<0>(instruction) != 'M'){
            instructionsForCargoFile << "\n";
            continue;
        }
        else {
            instructionsForCargoFile << ", " << get<5>(instruction) << ", "
                                     << get<6>(instruction) << ", " << get<7>(instruction) << "\n";
        }
    }
    instructionsForCargoFile << std::endl;
    instructionsForCargoFile.close();
}


//string extPortIdFromFileName(string input_full_path_and_file_name){ //for finding the next file needed after checking the next port
//    vector<string> temp = split(input_full_path_and_file_name, '_');
//    return temp[0];
//}

//
//bool checkIfValidContainer(Container* container){
//    string id = container->getId();
//    if (id.size() != 11)
//        return false;
//    for (int i = 0; i < 3; i++){
//        if (isupper(id.at(i)) == 0)
//            return false;
//    }
//    if (id.at(3) != 'U' && id.at(3) != 'J' && id.at(3) != 'Z')
//        return false;
//
//    for (int i = 4; i < 10; i++) {
//        if (isdigit(id.at(i)) == 0)
//            return false;
//    }
//
//    //TODO: check last digit - maybe change the validation to use regex
//    return true;
//}
