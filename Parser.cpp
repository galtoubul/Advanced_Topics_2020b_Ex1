#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "Port.h"
#include "Parser.h"
#include "Container.h"


using std::string;
using std::cout;
using std::vector;
using std::tuple;
using std::endl;
using std::list;
using std::ofstream;

template <typename Out>
void split(const string &s, char delim, Out result) {
    std::istringstream iss(s);
    string item;
    while (std::getline(iss, item, delim)) {
        if (!item.empty())
            *result++ = item;
    }
}

vector<string> split(const string &s, char delim) {
    vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


vector<tuple<int, int, int>> readShipPlan(const string& full_path_and_file_name){
    ifstream shipPlanInputFile (full_path_and_file_name);
    vector<tuple<int, int, int>> shipPlan;
    string line;
    if (shipPlanInputFile.is_open()){
        while (getline(shipPlanInputFile,line)){
            vector<string> temp = split(line, ',');
            if (temp[0][0] == '#')
                continue;
            if (temp.size() != 3)
                std::cout << "error" << std::endl;
            else{
                tuple <int, int, int> tempTuple;
                try{
                    tempTuple = std::make_tuple (stoi(temp[0]), stoi(temp[1]), stoi(temp[2]));
                }
                catch(std::invalid_argument& e){
                    cout<< "invalid_argument" << endl;
                }
                catch(std::out_of_range& e){
                    // if the converted value would fall out of the range of the result type
                    // or if the underlying function (std::strtol or std::strtoull) sets errno
                    // to ERANGE.
                    cout<< "out_of_range" << endl;
                }
                catch(...) {
                    cout<< "everything else" << endl;
                }
                shipPlan.push_back(tempTuple);
            }
        }
        shipPlanInputFile.close();
    }
    else cout << "Unable to open file";

    return shipPlan;
}

std::list<Port> readShipRoute(const string& full_path_and_file_name){
    ifstream shipRouteInputFile (full_path_and_file_name);
    string line;
    list<Port> portsList;
    if (shipRouteInputFile.is_open()){
        while (getline(shipRouteInputFile,line)){
            if (checkIfValidPortId(line)){ //have to be in model of: XX XXX - size 6
                std::transform(line.begin(), line.end(), line.begin(),
                               [](unsigned char c){ return std::toupper(c); });
                portsList.push_back(Port(line));
            }
        }
        shipRouteInputFile.close();
    }
    else cout << "Unable to open file";

    return portsList;
}



vector<Container*> parseContainerVecOfPort (ifstream& inputFile){
    string line;
    list<Container*> containerList;
    if (inputFile.is_open()){
        while (getline(inputFile,line)){
            vector<string> temp = split(line, ',');
            if (temp[0][0] == '#')
                continue;
            if (temp.size() != 3)
                std::cout << "error" << std::endl;
            //TODO: validate strings
            if (!checkIfValidPortId(temp[2]))
                continue; //TODO: warning message / exception
            else {
                Container *container;
                try {
                    std::transform(temp[2].begin(), temp[2].end(), temp[2].begin(),
                                   [](unsigned char c){ return std::toupper(c); }); //port id to uppercase
                    container = new Container(stoi(temp[1]), temp[2], temp[0]);
                }
                catch (std::invalid_argument &e) {
                    cout << "invalid_argument" << endl;
                }
                catch (std::out_of_range &e) {
                    // if the converted value would fall out of the range of the result type
                    // or if the underlying function (std::strtol or std::strtoull) sets errno
                    // to ERANGE.
                    cout << "out_of_range" << endl;
                }
                catch (...) {
                    cout << "everything else" << endl;
                }
                containerList.push_back(container);
            }
        }
        inputFile.close();
    }
    else cout << "Unable to open file";


}




void writeInstructionsToFile( vector<tuple<char,string,int,int,int,int,int,int>>& instructions, ofstream& instructionsForCargoFile)
{
    for (tuple<char,string,int,int,int,int,int,int> instruction : instructions){
        instructionsForCargoFile << get<0>(instruction) <<", " << get<1>(instruction);
        if (get<0>(instruction) == 'R'){
            instructionsForCargoFile << "\n";
            break;
        }
        instructionsForCargoFile << ", " << get<2>(instruction) <<", "
                                 << get<3>(instruction) << ", "<< get<4>(instruction);
        if (get<0>(instruction) != 'M'){
            instructionsForCargoFile << "\n";
            break;
        }
        else {
            instructionsForCargoFile << ", " << get<5>(instruction) << ", "
                                     << get<6>(instruction) << ", " << get<7>(instruction) << "\n";
        }
    }
    instructionsForCargoFile << std::endl;
    instructionsForCargoFile.close();
}


string extPortIdFromFileName(string input_full_path_and_file_name){ //for finding the next file needed after checking the next port
    vector<string> temp = split(input_full_path_and_file_name, '_');
    return temp[0];
}

bool checkIfValidPortId(string port){
    if (port.size()!=6) //have to be in model of: XX XXX - size 6
        return false;
    if (port.at(2) == ' ' && isalpha(port.at(0)) && isalpha(port.at(1)) && isalpha(port.at(3)) && isalpha(port.at(4)) && isalpha(port.at(5)))
        return true;
    return false;
}

bool checkIfValidContainer(Container* container){
    string id = container->getId();
    if (id.size() != 11)
        return false;
    for (int i = 0; i < 3; i++){
        if (isupper(id.at(i)) == 0)
            return false;
    }
    if (id.at(3) != 'U' && id.at(3) != 'J' && id.at(3) != 'Z')
        return false;

    for (int i = 4; i < 10; i++) {
        if (isdigit(id.at(i)) == 0)
            return false;
    }

    //TODO: check last digit
}

//vector<string> parseShipRoute (ifstream& inputFile){
//    string line;
//    vector<string> shipRoute;
//    if (inputFile.is_open()){
//        while (getline(inputFile,line))
//            shipRoute.push_back(line);
//        inputFile.close();
//    }
//    else cout << "Unable to open file";
//
//    return shipRoute;
//}
