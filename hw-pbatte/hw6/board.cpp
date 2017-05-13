#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed )
{
  size_ = dim*dim;
  tiles_ = new int[size_];
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::~Board()
{
  delete[] tiles_;
}

Board::Board(const Board& other)
{
  size_ = other.size();
  tiles_ = new int[size_];
  for(int i = 0; i < size_; i++)
  {
    tiles_[i] = (other.tiles_)[i];
  }
}

void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(tiles_[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(tiles_[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  tiles_[j] = tile;
  tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  map<int, Board*> potentialBoards;
  int bTile;

  for(int i = 0; i < size_; i++)
  {
    if(tiles_[i] == 0)
      bTile = i;
  }

  if(bTile >= dim())
  {
    Board* up = new Board(*this);
    int i_up = (*up)[bTile - dim()];
    up->move(i_up);
    potentialBoards.insert(make_pair(i_up, up));
  }
  if(bTile+dim() < size_)
  {
    Board* down = new Board(*this);
    int i_down = (*down)[bTile + dim()];
    down->move(i_down);
    potentialBoards.insert(make_pair(i_down, down));
  }
  if(bTile%dim() != dim()-1)
  {
    Board* right = new Board(*this);
    int i_right = (*right)[bTile + 1];
    right->move(i_right);
    potentialBoards.insert(make_pair(i_right, right));
  }
  if(bTile%dim() != 0)
  {
    Board* left = new Board(*this);
    int i_left = (*left)[bTile-1];
    left->move(i_left);
    potentialBoards.insert(make_pair(i_left, left));
  }

  return potentialBoards; 
}

bool Board::solved() const
{
  bool solved = true;
  for(int i = 0; i < size_; i++)
  {
    if(tiles_[i] != i)
      solved = false;
  }
  return solved;
}

std::ostream& operator<<(std::ostream &os, const Board &b)
{
  for(int i = 0; i <b.size(); i++)
  {
    if(i % b.dim() == 0)
    {
      os << endl;
      b.printRowBanner(os);
      os << "|";
    }
    if(b[i] == 0) os << "  |";
    if(b[i] < 10 && b[i] != 0) os << " " << b[i] << "|";
    else if(b[i] != 0) os << b[i] << "|";
  }
  os<<endl;
  b.printRowBanner(os);

  return os;
}

bool Board::operator<(const Board& rhs) const
{
  for(int i = 0; i < this->size_; i++)
  {
    if(this->tiles_[i] < rhs.tiles_[i])
      return true;
    if(tiles_[i] > rhs.tiles_[i]) 
      return false;
  }
  return false;
}

const int& Board::operator[](int loc) const 
{ 
  return tiles_[loc]; 
}

int Board::size() const 
{ 
  return size_; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}