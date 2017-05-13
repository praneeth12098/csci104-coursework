#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "avlbst.h"
#include <map>

using namespace std;

struct Rectangle
{
    int ID;
    int length;
    int height;

    Rectangle() {}

    Rectangle(int id, int l, int h) :
        ID(id), length(l), height(h)
    {

    }

    void rotate()
    {
        int temp = height;
        height = length;
        length = temp;
    }
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
typedef std::map<int, Rectangle> InputMapType;
typedef std::map<int, std::pair<int, int> > OutputMapType;

// Allowed global variables: the dimensions of the grid
int n; // X-dim size
int m; // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
// std::ostream& operator<<(std::ostream& os, const Rectangle& r)
// {
//   os << r.ID;
// }

// // A dummy operator << for pairs so the BST and AVL BST will
// // compile with their printRoot() implementations
// template <typename T, typename U>
// std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
// {
//   os << p.first << "," << p.second;
// }



void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output)
{
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it)
    {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

void flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) grid[x][y] = !grid[x][y];
    }
}

void insertTile(Rectangle rectangle, vector<vector<bool> >& grid, int row, int col, OutputMapType output)
{
    for(int i = row; i < row + rectangle.height; ++i)
    {
        for(int j = col; j < row + rectangle.length; ++j)
        {
            grid[i][j] = true;
        }
    }
    cout << col << " " << row << endl;
    output.find(rectangle.ID)->second = make_pair(col, row);
}

void removeTile(vector<vector<bool> >& grid, int row, int col, int length, int height)
{
    for(int i = row; i < row + height; ++i)
    {
        for(int j = col; j < row + length; ++j)
        {
            grid[i][j] = false;
        }
    }
}

bool isValid(Rectangle rectangle, vector<vector<bool> >& grid, int row, int col)
{
    int l = row + rectangle.length;
    int h = col + rectangle.height;

    int glength = grid.size(); 
    int gheight = grid[1].size();

    if(h > gheight || l > glength) return false;
    else if (grid[row][col] == true) return false;
    else
    {
        for(int i = row; i < l; i++)
        {
            for(int j = col; j < h; j++)
            {
                if(grid[i][j] == false) grid[i][j] = true;
                else if(grid[i][j] == true)
                {
                    removeTile(grid, i, j, rectangle.length, rectangle.height);
                    return false;
                }
            }
        }
    }
    return true;
}

// TODO: Write your backtracking search function here

bool solve(InputMapType::iterator it, InputMapType &input, OutputMapType &output, vector<vector<bool> > grid,
    const int &length, const int &height)
{
    if(it == input.end()) return true;

    for(int i = 0; i < height - it->second.height + 1; ++i)
    {
        for(int j = 0; j < length - it->second.length + 1; ++j)
        {
            if(isValid(it->second, grid, i, j))
            {
                insertTile(it->second, grid, i, j, output);
                //output.find(it->second.ID)->second = make_pair(i, j);
                InputMapType::iterator it2 = it;
                if(solve(++it, input, output, grid, length, height)) return true;
                else removeTile(grid, i, j, it->second.length, it->second.height);
            }
        }
    }

    //checking to rotate if its not equal length and height
    if(it->second.length != it->second.height)
    {
        it->second.rotate();

        for(int i = 0; i < height - it->second.height + 1; ++i)
        {
            for(int j = 0; j < length - it->second.length + 1; ++j)
            {
                if(isValid(it->second, grid, i, j))
                {
                    insertTile(it->second, grid, i, j, output);
                    //output.find(it->second.ID)->second = make_pair(i, j);
                    InputMapType::iterator it2 = it;
                    if(solve(++it, input, output, grid, length, height)) return true;
                    else removeTile(grid, i, j, it->second.length, it->second.height);
                }
            }
        }
    }
    return false;

}


int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n;
    ss >> m;
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++) {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool> > grid;
    
    for (int i = 0; i < n; i++)
    {
      grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;

    // TODO:  Call your backtracking search function here

    if(solve(input.begin(), input, output, grid, n, m))
    {
        for(OutputMapType::iterator oit = output.begin(); oit != output.end(); ++oit)
        {
            ofile << oit->first << " " << oit->second.first << " " <<
            oit->second.second << " " << input.find(oit->first)->second.length << " "
            << input.find(oit->first)->second.height << endl;
        }
        solution_exists = true;
    }


    if (!solution_exists) {
      ofile << "No solution found.";
    }
    else {
      printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}
