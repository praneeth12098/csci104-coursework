#include <iostream>
#include <utility>
#include "avlbst.h"

using namespace std;

int main(){

  cout << "HOMEWORK EXAMPLE:" << endl;
  AVLTree<int, int> bst;
  bst.insert(make_pair(10,0));
  bst.insert(make_pair(4,0));
  bst.insert(make_pair(20,0));
  bst.insert(make_pair(2,0));
  bst.insert(make_pair(8,0));
  bst.insert(make_pair(14,0));
  bst.insert(make_pair(24,0));
  bst.insert(make_pair(6,0));
  bst.insert(make_pair(12,0));
  bst.insert(make_pair(18,0));
  bst.insert(make_pair(22,0));
  bst.insert(make_pair(16,0));

  bst.print();

  bst.insert(make_pair(15,0));
  bst.print();

  bst.insert(make_pair(17,0));
  bst.print();

  bst.insert(make_pair(11,0));
  bst.print();

  bst.erase(20);
  bst.print();

  bst.erase(16);
  bst.print();

  bst.erase(4);
  bst.print();
  
  cout << "TESTING ITERATOR:" << endl;
  for(AVLTree<int, int>::iterator it = bst.begin(); it != bst.end(); ++it)
  {
    cout << it->first << ", ";
  }
  cout << endl << endl;

  cout << "TESTING INCREASING INSERT:" << endl;
  AVLTree<int, int> bst2;
  for(int i=0; i<5; i++)
  {
    bst2.insert(make_pair(i, 0));
  }
  bst2.print();

  cout << "TESTING DECREASING INSERT:" << endl;
  for(int i=9; i>=5; i--)
  {
    bst2.insert(make_pair(i, 0));
  }
  bst2.print();

  cout << "TESTING INCREASING DELETION:" << endl;
  for(int i=0; i<10; i=i+2)
  {
    bst2.erase(i);
  }
  bst2.print();

  cout << "TESTING WEIRD DELETIONS:" << endl;
  bst2.erase(7);
  bst2.erase(3);
  bst2.erase(5);

  bst2.print();



  return 0;
}