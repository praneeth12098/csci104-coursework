CXX=g++
CXXFLAGS=-g -Wall 

all: board.o puzzle puzzle_heur.o puzzle_move.o puzzle_solver.o

board.o: board.cpp board.h
	$(CXX) $(CXXFLAGS) -c board.cpp -o board.o

puzzle_heur.o: puzzle_heur.cpp puzzle_heur.h
	$(CXX) $(CXXFLAGS) -c puzzle_heur.cpp -o puzzle_heur.o

puzzle_move.o: puzzle_move.cpp puzzle_move.h
	$(CXX) $(CXXFLAGS) -c puzzle_move.cpp -o puzzle_move.o

puzzle_solver.o: puzzle_solver.cpp puzzle_solver.h
	$(CXX) $(CXXFLAGS) -c puzzle_solver.cpp -o puzzle_solver.o

puzzle: puzzle.cpp board.o puzzle_move.o puzzle_heur.o puzzle_solver.o
	$(CXX) $(CXXFLAGS) puzzle.cpp board.o puzzle_move.o puzzle_heur.o puzzle_solver.o -o puzzle

clean: 
	rm -f *.o puzzle