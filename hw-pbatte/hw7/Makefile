CXX=g++
CXXFLAGS=-g -std=c++11 -Wall 
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=floorplan.o

all: floorplan

floorplan: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

amazon.o: floorplan.cpp 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c floorplan.cpp

clean:
	rm -f *.o floorplan