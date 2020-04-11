#include <cstdlib>
#include <vector>
#include <tuple>
#include "Simulation.h"
#include "Parser.h"
using std::cout;
using std::endl;

int main() {
    Container container1(1000 , "ILASH", "051065196581", false);
    cout << container1.getWeight() << endl;
    cout << container1.getDestination() << endl;
    cout << container1.getId() << endl;
    cout << container1.isFutile() << endl;
   // cout << container1.getFloorNum() << endl;

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

 //   shipPlan1.insertContainer(container1,0,0,0);
    cout << *shipPlan1.getContainers()[0][0][0]<< endl;

    cout << "----------------------------------------------------------" << '\n';

    ifstream inputFile ("C:\\example.txt");
    std::vector<std::tuple<int, int, int>> vec = parseShipPlan(inputFile);
    for (int i = 0; i < vec.size(); i++){
        cout << "shipPlan [" << i << "][0] = " <<std::get<0>(vec[i]) << ", ";
        cout << "shipPlan [" << i << "][1] = " <<std::get<1>(vec[i]) << ", ";
        cout << "shipPlan [" << i << "][2] = " <<std::get<2>(vec[i]) << endl;
    }

    cout << "----------------------------------------------------------" << '\n';

    string shipPlanFileName = "C:\\example.txt";
    string shipRouteFileName = "C:\\example2.txt";
    initSimulation(shipPlanFileName, shipRouteFileName);

    cout << "----------------------------------------------------------" << '\n';

    Container* cont1 = new Container(25, "X", "fiufie");
    Container* cont2 = new Container(35, "Y", "dsjhdvsu");
    vector<Container*> vec2;
    vec2.push_back(cont1);
    vec2.push_back(cont2);
    Port port("asdf");
    port.addContainersToUnload(vec2);
    cout << port.getPortId() << endl;

    free(cont1);
    free(cont2);

    return EXIT_SUCCESS;
}
