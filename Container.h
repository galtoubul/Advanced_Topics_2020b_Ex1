/**
 * Container Summary:
 *
 * Contains the class of Container and its related functions:
 *
 * Container    -
 * calcVariables       -  an assistance function for createEntryTable.
 * destroyEntryTable   -  Frees all allocated memory related to the stack.
 * parseSol            -  inserts a Game into the top of the stack.
 * parseLPSol          -  returns the Game from the top of the stack and removes it from the Entry Table.
 * printEntryTable     -  for debugging purposes. Prints all relevant information about the entry table.
 */

#include <string>
#include <iostream>
#include <tuple>
using std::string;
using std::tuple;
#define NOT_ON_SHIP -1

class Container{
    int weight;
    string destination;
    string id;
    bool futile;
    tuple<int,int,int> loc;

public:
    Container(int _weight = 0, const string& _destination = "", const string& _id = "", bool _futile = true,
              int _x = NOT_ON_SHIP, int _y = NOT_ON_SHIP, int _floorNum = NOT_ON_SHIP) :
            weight(_weight), destination(_destination), id(_id), futile(_futile), loc(std::make_tuple(_x, _y, _floorNum)) {}

    explicit Container (const Container* other) :
            weight(other->weight), destination(other->destination), id(other->id), futile(other->futile), loc(other->loc) {}

    int getWeight ();

    string getDestination () const;

    string getId () const;

    bool isFutile ();

    tuple<int,int,int> getLocation();

    void setLocation(int x, int y, int floor);

    void setDestination (const string& newDestination);

    friend std::ostream& operator<<(std::ostream& out, const Container& container);
};
