COMP = g++-8.3.0
OBJS = main.o Container.o ShipPlan.o Port.o ShipRoute.o Parser.o Simulation.o Algorithm.o WeightBalanceCalculator.o

EXEC = ex1
CPP_COMP_FLAG = -std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
main.o: main.cpp Simulation.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Container.o: Container.cpp Container.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
ShipPlan.o: ShipPlan.cpp ShipPlan.h Container.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Port.o: Port.cpp Port.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
ShipRoute.o: ShipRoute.cpp ShipRoute.h Port.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Parser.o: Parser.cpp Parser.h ShipRoute.h ShipPlan.h WeightBalanceCalculator.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Simulation.o: Simulation.cpp Simulation.h Algorithm.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Algorithm.o: Algorithm.cpp Algorithm.h Parser.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
WeightBalanceCalculator.o: WeightBalanceCalculator.cpp WeightBalanceCalculator.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)