#include <cstring>

class Container{
    int weight;
    const char* destination;
    const char* id;
    bool futile;
    int floorNum;

public:
    Container(int _weight, char* _destination, char* _id, bool futile, int _floorNum = -1);

    int getWeight ();

    const char* getDestination ();

    const char* getId ();

    bool isFutile ();

    int  getFloorNum ();

    };