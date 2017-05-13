#ifndef LLISTDBL_H
#define LLISTDBL_H

class LListDbl {
 public:
  struct Item {
    double val;
    Item *prev;
    Item *next;
  };

  /**
   * Default constructor - empty list
   */
  LListDbl();

  /**
   * Destructor
   */
  ~LListDbl();

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
  void insert(int pos, const double& val);

  /**
   * Removes the value at index, pos
   */
  void remove(int pos);

  /**
   * Overwrites the old value at index, pos, with val
   */
  void set(int pos, const double& val);

  /**
   * Returns the value at index, pos
   */
  double& get(int pos);

  /**
   * Returns the value at index, pos
   */
  double const & get(int pos) const;

  /**
   * Deletes all items in the list
   */
  void clear();

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
