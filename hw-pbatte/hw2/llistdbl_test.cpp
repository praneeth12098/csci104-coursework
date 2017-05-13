#include "llistdbl.h"
#include <iostream>

using namespace std;

int main() {
  LListDbl list;


  // Insert an item at the head.
  list.insert(0, 10);
  list.remove(0);

  // Check if the list is still empty.
  if (list.empty()) 
  {
    cout << "SUCCESS: List is empty after one insertion and one deletion." << endl;
  } 
  else 
  {
    cout << "FAIL: List is not empty after one insertion and one deletion." << endl;
  }

  //Insert 5 Items at the head.
  list.insert(0, 30);
  list.insert(0, 20);
  list.insert(0, 15);
  list.insert(0, 10);
  list.insert(0, 5);

  //Check if size remains correct.
  if (list.size() == 5) 
  {
    cout << "SUCCESS: List has size 5 after five insertion." << endl;
  } 
  else 
  {
    cout << "FAIL: List has size " << list.size() << " after five insertions.";
    cout << endl;
  }

  //Insert item in middle.
  list.insert(4, 25);

  //Check if size remains correct
  if(list.get(4) == 25)
  {
    cout << "SUCCESS: Element at inserted index is correct." << endl;
  }
  else
  {
    cout << "FAIL: Element at inserted index is " << list.get(4) << " instead of 25.";
  }

  //Insert item at the end.
  list.insert(6, 35);

  //Checks if item was correctly inserted.
  if(list.get(6) == 35)
  {
    cout << "SUCCESS: Element at inserted at last index is correct." << endl;
  }
  else
  {
    cout << "FAIL: Element at inserted at last index is " << list.get(6) << " instead of 35.";
  }

  //Remove item from beginning and end.
  list.remove(0);
  list.remove(5);

  //Checks if size remains correct.
  if (list.size() == 5) 
  {
    cout << "SUCCESS: List has size 5 after 2 deletions." << endl;
  } 
  else 
  {
    cout << "FAIL: List has size " << list.size() << " after 2 deletions.";
    cout << endl;
  }

  //Removes item from middle.
  list.remove(2);

  //Checks if items shift properly.
  if(list.get(2) == 25)
  {
    cout << "SUCCESS: List shifted correctly after middle deletion." << endl;
  }
  else
  {
    cout << "FAIL: List should contain 25 at index 2 rather than " << list.get(2) << "." << endl;
  }

  //Removes all items from list.
  list.remove(3);
  list.remove(1);
  list.remove(0);
  list.remove(0);

  //Checks to see if list now has size 0.
  if(list.size() == 0)
  {
    cout << "SUCCESS: List is properly containing zero elements after all deletions." << endl;
  }
  else
  {
    cout << "FAIL: List has size " << list.size() << " after deleting all elements." << endl;
  }

  return 0;
}
