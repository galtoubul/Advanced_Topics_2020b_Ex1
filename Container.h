#include <string>

class Container{
    int weight;
    std::string destination;
    std::string id;
    bool futile;
    int floorNum;

public:
    Container(int _weight, std::string _destination, std::string _id, bool futile, int _floorNum = -1);

    int getWeight ();

    std::string getDestination ();

    std::string getId ();

    bool isFutile ();

    int  getFloorNum ();

    };