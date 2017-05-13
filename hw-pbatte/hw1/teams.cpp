#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, 
		   const string* team2,
		   int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}

// You may add additional functions here
void gen_combos(string* arr, int len, int index, string* temp1, string* temp2, int counter1);
void gen_other_team(string* arr, int len, string* temp1, string* temp2, int c2);

void gen_combos(string* arr, int len, int index, string* temp1, string* temp2, int counter1)
{
  if(index == 2)
  {
    gen_other_team(arr, len, temp1, temp2, 0); //after temp2 is created with unique elements from this method, the combination is then printed
    printSolution(temp1, temp2, 2);
    return;
  }
  if (counter1 >= len) //makes sure there is no seg fault from accessing elements out of size
  {
    return;
  } //second if statement because if it wasn't then the isomorphic solution would not be printed since it would satisfy this condition before the first

  temp1[index] = arr[counter1]; //sets the first value of temp1 to the first value of the array of names
                                //then iterates through temp1 til it is filled adding consecutive elements from array
  gen_combos(arr, len, index+1, temp1, temp2, counter1+1);
  //recursively calls itself starting from next index in both array and temp1
  //this is called to help the other isomorphic team
  gen_combos(arr, len, index, temp1, temp2, counter1+1);
  //recursively calls itself starting from same index, but next index in temp1
  //this is called to help make unique combinations because it keeps rearranging temp1 through replacement by only changing one index
}

//generate the other possibility since it is isomorphicss
void gen_other_team(string* arr, int len, string* temp1, string* temp2, int c2)
{
  //i is counter for arr, c1 is counter for temp1, and c2 is counter for temp2
  for(int i = 0; i < len; ) //loops through arr and compares them with elemnts in temp1 to find the ones not in temp1 in order to add to temp2
  {
    for(int c1 = 0; c1 < 2; )
    {
      if(arr[i].compare(temp1[c1]) == 0) //checks same elements in arr and temp1 for similarity
      {
        i++; c1++;
      }
      else if(arr[i].compare(temp1[c1]) != 0) //checks same elements in arr and temp1 and if they aren't the same, then it adds the element to temp2
      {
        temp2[c2] = arr[i];
        c2++; i++;

        if(c2 == 2) return;//once temp2 is filled it exits out of the method
      }
    }
  }
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a file of names" << endl;
    return 1;
  }
  // Complete the rest of main
  ifstream myfile(argv[1]);
  if(myfile.fail()){
    cerr << "Error" << endl;
    return 1;
  }

  int num_names;
  myfile >> num_names;
  string* arr = new string[num_names];
  string* t1 = new string[num_names/2];
  string* t2 = new string[num_names/2];
  for(int i = 0; i < num_names; i++)
  {
    myfile >> arr[i];
  }

  gen_combos(arr, num_names, 0, t1, t2, 0);

  delete [] arr;
  delete [] t1;
  delete [] t2;

  return 0;
}