/**
 * ErrorsInterface Summary:
 * This module contains all program errors and messages to be printed.
 */

#define UNABLE_TO_OPEN_FILE(fileName)                       cout << "ERROR: Unable to open file: " << fileName << " Exiting..." << endl;

#define CONTAINER_ERROR(x)                                  cout << "ERROR: Conatiner's " << x << " input isn't valid. Exiting..." << endl;

#define INVALID_INPUT(x)                                    cout << "ERROR: " << x << "input isn't valid. Exiting..." << endl;

#define PORT_FILE_NAME_ISNT_MATCHING(fileName)              cout << "ERROR: There isn't any port file name matching " << fileName << " .Exiting..." << endl;

#define NON_LEGAL_SEA_PORT_CODE(port)                       cout << "ERROR: Ship route input isn't valid. It contains a line with non legal seaport code: " << port << ". Exiting..." << endl;
#define SAME_PORT_AS_PREV                                   cout << "ERROR: Ship route input isn't valid. It contains the same port in two consecutive lines. Exiting..." << endl;

#define NOT_LEGAL_OPERATION(C, id, floor, x, y, reason)     cout << "ERROR: " << C" " << id << " at floor: " << floor << " at indices: [" << x << "][" << y << "] isn't legal\nThe reason: " << reason << "\nLeaving current travel..." << endl;
#define CONTAINER_FORGOTTEN(currPortSymbol)                 cout << "ERROR: There is a Container whose destination isn't" << currPortSymbol << " and yet it was Forgotten there.\nLeaving current travel..." << endl;
#define CONTAINER_WASNT_DROPPED(currPortSymbol)             cout << "ERROR: There is a Container whose destination isn't" << currPortSymbol << "and yet it was Forgotten on ship.\nLeaving current travel..." << endl;

#define LAST_PORT_WARNING                                   cout << "Warning: This is the last port at the ship a route, but it has containers to unload.\nAll of these containers won't be unloaded from port." << endl;

#define TRAVELS_OR_ALGORITHMS_NUMBER_ERROR(x)               std::cout << "Number of " << x << " has to be positive." << std::endl;
