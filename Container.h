#include <cstring>
#include <iostream>

class Container{
    int weight;
    const char* destination;
    const char* id;
    bool futile;
    int floorNum;

public:
    Container(int _weight, const char* _destination, const char* _id, bool futile, int _floorNum = -1);

    int getWeight ();

    const char* getDestination ();

    const char* getId ();

    bool isFutile ();

    int  getFloorNum ();

    friend std::ostream&operator<<(std::ostream& out, const Container& container);

    };