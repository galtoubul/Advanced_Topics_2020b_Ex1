#include <string>
#include <iostream>

using std::string;

class Container{
    int weight;
    string destination;
    string id;
    bool futile;
    int floorNum;

public:
    Container(int _weight, string _destination, string _id, bool futile = false, int _floorNum = -1);

    Container ();

    Container (const Container& other);

    int getWeight ();

    string getDestination () const;

    string getId () const;

    bool isFutile ();

    int  getFloorNum ();

    void setDestination (string newDestination);

    friend std::ostream&operator<<(std::ostream& out, const Container& container);

    };