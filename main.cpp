#include <cstdlib>
#include "ShipPlan.h"
#include "ShipRoute.h"
#include "Parser.h"
#include <vector>
#include <tuple>
//#include "Port.h"
using std::cout;
using std::endl;

int main() {
    Container container1(1000 , "ILASH", "051065196581", false);
    cout << container1.getWeight() << endl;
    cout << container1.getDestination() << endl;
    cout << container1.getId() << endl;
    cout << container1.isFutile() << endl;
    cout << container1.getFloorNum() << endl;

    cout << "----------------------------------------------------------" << '\n';

    auto container2(container1);
    cout << "container2'd destination: " << container2.getDestination() << endl;
    container1.setDestination("hello");
    cout << "container1'd destination: " << container1.getDestination() << endl;
    cout << "container2'd destination: " << container2.getDestination() << endl;

    cout << "----------------------------------------------------------" << '\n';

    ShipPlan shipPlan1(4, 4, 4);
    cout << shipPlan1.getFloorNum() << endl;
    cout << shipPlan1.getPivotXDimension() << endl;
    cout << shipPlan1.getPivotYDimension() << endl;

    cout << "----------------------------------------------------------" << '\n';

    shipPlan1.insertContainer(container1,0,0,0);
    cout << shipPlan1.getContainers()[0][0][0]<< endl;

    cout << "----------------------------------------------------------" << '\n';

    ifstream inputFile ("C:\\example.txt");
    std::vector<std::tuple<int, int, int>> vec = parseShipPlan(inputFile);
    for (int i = 0; i < vec.size(); i++){
        cout << std::get<0>(vec[i]) << endl;
        cout << std::get<1>(vec[i]) << endl;
        cout << std::get<2>(vec[i]) << endl;

    }
//
//    Port port = new  Port("asdf", vec);
//    std::cout << port.getPortId() << std::endl;
//    std::cout << port.getContainersToLoad() << std::endl;

    return EXIT_SUCCESS;
}
