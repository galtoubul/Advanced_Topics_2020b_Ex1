COMP = g++-8.3.0
#put all your object files here
OBJS = main.o Container.o ShipPlan.o Port.o ShipRoute.o Common.o Parser.o Simulation.o StowageAlgorithm.o WeightBalanceCalculator.o

EXEC = ex1
CPP_COMP_FLAG = -std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp main.h Simulation.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Container.o: Container.cpp Container.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
ShipPlan.o: ShipPlan.cpp ShipPlan.h Container.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Port.o: Port.cpp Port.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
ShipRoute.o: ShipRoute.cpp ShipRoute.h Port.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Common.o: Common.cpp Common.h WeightBalanceCalculator.h ShipPlan.h ShipRoute.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Parser.o: Parser.cpp Parser.h Port.h Container.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Simulation.o: Simulation.cpp Simulation.h StowageAlgorithm.h 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
StowageAlgorithm.o: StowageAlgorithm.cpp StowageAlgorithm.h Common.h Parser.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
WeightBalanceCalculator.o: WeightBalanceCalculator.cpp WeightBalanceCalculator.h 
clean:
	rm -f $(OBJS) $(EXEC)