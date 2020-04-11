#include <string>
#include <iostream>
#include <tuple>

using std::string;
using std::tuple;

class Container{
    int weight;
    string destination;
    string id;
    bool futile;
   // int floorNum;
    tuple<int,int,int> loc;

public:
    /*Container(int _weight, string _destination, string _id, bool futile = false, int _floorNum = -1);

    Container ();

    Container (const Container& other);*/


    Container(int _weight, string _destination, string _id, bool futile = false, int _x = -1, int y=-1, int _floor = -1);

    Container ();

    Container (const Container& other);

    int getWeight ();

    string getDestination () const;

    string getId () const;

    bool isFutile ();

//    int  getFloorNum ();
    tuple<int,int,int> getLocation();

    void setLocation(int x, int y, int floor);

    void setDestination (string newDestination);

    friend std::ostream&operator<<(std::ostream& out, const Container& container);

    };