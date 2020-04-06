#include <sstream>
#include <string>
#include <iostream>
#include "Port.h"
#include "Parser.h"
using std::string;
using std::cout;
using std::vector;
using std::tuple;
using std::endl;
using std::list;

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

vector<tuple<int, int, int>> parseShipPlan(ifstream& inputFile) {
    vector<tuple<int, int, int>> shipPlan;
    string line;
    if (inputFile.is_open()){
        while (getline(inputFile,line)){
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
        inputFile.close();
    }
    else cout << "Unable to open file";

    return shipPlan;
}

list<Port> parsePortsList (ifstream& inputFile){
    string line;
    list<Port> portsList;
    if (inputFile.is_open()){
        while (getline(inputFile,line)){
             //TODO: validate
            portsList.push_back(Port(line));
        }
        inputFile.close();
    }
    else cout << "Unable to open file";

    return portsList;
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
