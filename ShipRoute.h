#include <iostream>
#include <string>
#include <vector>

class ShipRoute{
    int portNum;
    std::vector<std::string> portVec;
    int currPortNum;

public:
    ShipRoute(int _portNum, std::vector<std::string> _portVec);
    std::string getNextPort();
    int getPortNum();
    int getCurrentPortNumInRoute();

    friend std::ostream&operator<<(std::ostream& out, const ShipRoute& shipRoute);


};

