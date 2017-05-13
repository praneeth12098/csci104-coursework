#include "llistdbl.h"
#include <cstdlib>

LListDbl::LListDbl()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListDbl::~LListDbl()
{
  clear();
}

bool LListDbl::empty() const
{
  return size_ == 0;
}

int LListDbl::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListDbl::insert(int loc, const double& val)
{
  if(loc < 0 || loc > size_)
    return;

  Item* new_node = new Item;
  new_node->val = val;

  if(empty())
  {
    head_ = new_node;
    tail_ = new_node;
    size_++;
  }
  else
  {
    if(loc == 0)
    {
      new_node->prev = NULL;
      new_node->next = head_;
      head_->prev = new_node;
      head_ = new_node;
      size_++;
    }
    else if (loc == size_)
    {
      new_node->next = NULL;
      new_node->prev = tail_;
      tail_->next = new_node;
      tail_ = new_node;
      size_++;
    }
    else
    {
      Item* old_node = getNodeAt(loc);
      Item* prev_node = getNodeAt(loc-1);
      new_node->prev = prev_node;
      prev_node->next = new_node;
      new_node->next = old_node;
      old_node->prev = new_node;
      size_++;
    }
  }
}
/**
 * Complete the following function
 */
void LListDbl::remove(int loc)
{
  if(loc < 0 || loc > size_-1)
    return;

  if(empty())
  {
    return;
  }

  Item* node = getNodeAt(loc);
  Item* prev_node = node->prev;
  Item* next_node = node->next;

  if(size_ == 1)
  {
    //delete head_;
    head_ = NULL;
    tail_ = NULL;
    size_--;
  }
  else
  {  
    if(loc == 0)
    {
      head_ = next_node;
      next_node->prev = head_;
      delete node;
      size_--;
    }
    else if(loc == size_-1)
    {
      prev_node->next = tail_;
      tail_ = prev_node;
      size_--;
      delete node;
    }
    else
    {
      prev_node->next = next_node;
      next_node->prev = prev_node;
      delete node;
      size_--;
    }
  }
}

void LListDbl::set(int loc, const double& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

double& LListDbl::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

double const & LListDbl::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListDbl::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListDbl::Item* LListDbl::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}
