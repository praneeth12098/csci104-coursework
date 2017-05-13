#include "llistint.h"
#include <iostream>
#include <cstdlib>

using namespace std;

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::LListInt(const LListInt& other)
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;

  if(other.empty())
  {
    return;
  }

  Item* curr = other.head_;

  while(curr != NULL)
  {
    push_back(curr->val);
    curr = curr->next;
  }
}

LListInt& LListInt::operator=(const LListInt& other)
{
  if(this == &other)
    return *this;
  if(other.empty())
    return *this;

  if(!this->empty())
    clear();

  head_ = NULL;
  tail_ = NULL;
  size_ = 0;

  Item* curr = other.head_;

  while(curr != NULL)
  {
    push_back(curr->val);
    curr = curr->next;
  }

  return *this;
}

LListInt& LListInt::operator+=(LListInt& other)
{
  if(this->empty())
  {
    Item* curr = other.head_;
    while(curr != NULL)
    {
      push_back(curr->val);
      curr = curr -> next;
    }
    return *this;
  }
  if(other.empty())
    return *this;

  if(this == &other)
    return *this;

  tail_->next = other.head_;
  other.head_->prev = tail_;
  size_ += other.size_;

  other.head_ = NULL;
  other.tail_ = NULL;
  other.size_ = 0;

  return *this;
}

ostream& operator<<(ostream& out, const LListInt& list)
{
  int pos = 0;
  LListInt::Item* curr = list.head_;

  if(curr == NULL)
  {
    out << "(empty)";
  }

  while(curr != NULL)
  {
    out << curr->val << " ";
    curr = curr->next;
    pos++;
    if(pos % 10 == 0)
    {
      out << "\n";
    }
  }

  return out;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

void LListInt::push_back(const int& val)
{
  Item* list_item = new Item;
  list_item -> val = val;
  list_item -> prev = tail_;
  list_item -> next = NULL;

  if(empty())
  {
    head_ = list_item;
    tail_ = list_item;
  }
  else
  {
    tail_ -> next = list_item;
    tail_ = list_item;
  }
  delete list_item;
  size_++;
}

void LListInt::insert(int loc, const int& val)
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

void LListInt::remove(int loc)
{
  if(loc < 0 || loc > size_-1)
    return;

  if(empty())
  {
    return;
  }


    Item* node = getNodeAt(loc);
    //Item* prev_node = node->prev;
    //Item* next_node = node->next;

    if(size_ == 1)
    {
      head_ = NULL;
      tail_ = NULL;
      size_--;
    }
    else
    {  
      if(loc == 0)
      {
        Item* next_node = node->next;
        head_ = next_node;
        if(next_node != NULL) 
          next_node->prev = NULL;
        delete node;
        size_--;
      }
      else if(loc == size_-1)
      {
        Item* prev_node = node->prev;

        prev_node->next = tail_;
        tail_ = prev_node;
        size_--;
        delete node;
      }
      else
      {
        Item* prev_node = getNodeAt(loc-1);
        Item* next_node = getNodeAt(loc+1);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        delete node;
        size_--;
      }
    }
}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListInt::Item* LListInt::getNodeAt(int loc) const
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
