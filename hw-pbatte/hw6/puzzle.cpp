#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

  int dim = atoi(argv[1]);
  int iMoves = atoi(argv[2]);
  int seed = atoi(argv[3]);
  int heur = atoi(argv[4]);

  PuzzleHeuristic* ph;

  if(heur == 0) { ph = new PuzzleBFSHeuristic(); }
  else if(heur == 1) { ph = new PuzzleOutOfPlaceHeuristic(); }
  else if(heur == 2) { ph = new PuzzleManhattanHeuristic(); }

  Board board(dim, iMoves, seed);

  while(board.solved() != true)
  {
  	int move;
  	cout << board << endl;
  	cout << "Enter tileNumber or -1 for cheat or 0 to quit: ";
  	cin >> move;
  	if (move == -1)
  	{
  		PuzzleSolver ps(board, ph);
  		ps.run();
  		deque<int> solutions = ps.getSolution();
  		cout << "Try this sequence: " << endl;

  		for(unsigned int i = 0; i < solutions.size(); i++)
  			cout << solutions[i] << " ";

  		cout << endl;
  		cout << "(Expansions = " << ps.getNumExpansions() << " )" << endl << endl;
  	}
  	else
  	{
  		if(move == 0)
  		{
  			return 0;
  		}
  		board.move(move);
  	}
  }

  cout << board;
  delete ph;

  return 0;
}
