#include "puzzle_heur.h"
#include <cmath>

using namespace std;

int PuzzleBFSHeuristic::compute(const Board& b)
{
	return 0;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	int count_oop = 0;
	for(int i = 0; i < b.size(); i++)
	{
		if(b[i] != 0 && b[i] != i) count_oop++;
	}
	return count_oop;
}

int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int total_distance = 0;
	int dx = 0; 
	int dy = 0;
	int dxdy = 0;
	int goal[b.size()];
	int board[b.size()];

	for(int i = 0; i < b.size(); i++)
	{
		goal[i] = i; board[i] = b[i];
	}

	for(int i = 0; i < b.size(); i++)
	{
		for(int j = 0; j < b.size(); j++)
		{
			if((goal[i] == board[j]) && (i != j))
			{
				dx = abs(i/b.dim() - j/b.dim());
				dy = abs(i%b.dim() - j%b.dim());
				dxdy = dx + dy;
				total_distance += dxdy;
			}
		}
	}
	return total_distance;
}