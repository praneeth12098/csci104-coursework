#ifndef LLISTINT_H
#define LLISTINT_H
#include <iostream>

using namespace std;

class LListInt {
 public:
  struct Item {
    int val;
    Item *prev;
    Item *next;
  };

  /**
   * Default constructor - empty list
   */
  LListInt();

  /**
   * Copy constructor [must run in O(n) where n=size of other]
   *   Be careful you don't give us an O(n^2) implementation
   */
  LListInt(const LListInt& other);

  /**
   * Assignment Operator (must run in O(n + m) where
   *   n is the size of this list & m is the size of other
   *   Be careful you don't give us an O(n^2) or O(m^2) implementation
   */
  LListInt& operator=(const LListInt& other);

  LListInt& operator+=(LListInt& other);

  friend ostream& operator<<(ostream& out, const LListInt& list);
  /**
   * Destructor
   */
  ~LListInt();

  /**
   * Returns the current number of items in the list 
   */
  int size() const;

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool empty() const;

  /**
   * Inserts val so it appears at index, pos
   */
  void insert(int pos, const int& val);

  /**
   * Removes the value at index, pos
   */
  void remove(int pos);

  /**
   * Overwrites the old value at index, pos, with val
   */
  void set(int pos, const int& val);

  /**
   * Returns the value at index, pos
   */
  int& get(int pos);

  /**
   * Returns the value at index, pos
   */
  int const & get(int pos) const;

  /**
   * Deletes all items in the list
   */
  void clear();

  /**
   * Adds an item to the back of the list in O(1) time
   */
  void push_back(const int& val);

 private:
  /** 
   * Returns a pointer to the item at index, pos
   *  and NULL otherwise
   */
  Item* getNodeAt(int pos) const;

  /**
   * Data members
   */
  Item* head_;
  Item* tail_;
  int size_;
};

#endif
