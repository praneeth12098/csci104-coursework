#include "puzzle_move.h"

PuzzleMove::PuzzleMove(Board* board)
{
	tileMove = -1;
	b = board;
	g = 0;
	h = 0;
	prev = NULL;
}

PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
{
	tileMove = tile;
	b = board;
	prev = parent;
	g = (prev->g) + 1;
	h = 0;
}

PuzzleMove::~PuzzleMove()
{
	
}