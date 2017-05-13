#include "puzzle_solver.h"

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph) :
	b_(b), expansions_(0), ph_(ph)

{
	PuzzleMoveBoardComp bComp;
	PuzzleMoveScoreComp sComp;

	openlist = new Heap<PuzzleMove*, PuzzleMoveScoreComp>(2, sComp);
	closedlist = new PuzzleMoveSet(bComp);
}

PuzzleSolver::~PuzzleSolver()
{
	for(unsigned int i = 0; i < allBoardCombos.size(); i++)
		delete allBoardCombos[i];

	for(unsigned int i = 0; i < allPuzzleCombos.size(); i++)
		delete allPuzzleCombos[i];

	delete openlist;
	delete closedlist;
}

std::deque<int> PuzzleSolver::getSolution()
{
	return solution_;
}

int PuzzleSolver::getNumExpansions()
{
	return expansions_;
}

void PuzzleSolver::run()
{
	PuzzleMove* pMove = new PuzzleMove(&b_);
	allPuzzleCombos.push_back(pMove);
	pMove->h = ph_->compute(b_);

	openlist->push(pMove);
	closedlist->insert(pMove);

	while(!openlist->empty())
	{
		PuzzleMove* move = openlist->top();
		Board* board = move->b;
		openlist->pop();

		if(board->solved())
		{
			solve(move); return;
		}
		else
		{
			map<int, Board*> potentialMoves = board->potentialMoves();
			map<int, Board*>::iterator it = potentialMoves.begin();

			for(; it != potentialMoves.end(); ++it)
			{
				allBoardCombos.push_back(it->second);
				PuzzleMove* temp = new PuzzleMove(it->first, it->second, move);
				allPuzzleCombos.push_back(temp);
				temp->h = ph_->compute(*temp->b);
				if(closedlist->find(temp) == closedlist->end())
				//if(closedlist->count(temp) == 0)
				{
					openlist->push(temp);
					expansions_++;
					closedlist->insert(temp);
				}
			}
		}
	}
}

void PuzzleSolver::solve(PuzzleMove* puzzle)
{
	PuzzleMove* temp = puzzle;
	while(temp->prev != NULL && temp->tileMove != -1)
	{
		solution_.push_front(temp->tileMove);
		temp = temp->prev;
	}
}