#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T, typename Comparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c = Comparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below
 	void trickleUp(int index);
 	void heapify(int index);
 	std::vector<T> items;
 	int mDegree;
 	Comparator comp;
};

// Add implementation of member functions here
template<typename T, typename Comparator>
Heap<T, Comparator>::Heap(int m, Comparator c) :
	mDegree(m), comp(c)
{

}

template<typename T, typename Comparator>
Heap<T, Comparator>::~Heap()
{

}

//pushing back item to end of vector and 
//then calling trickleUp to sort itself into the right position
template<typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& item)
{
	items.push_back(item);
	trickleUp(items.size()-1);
}

template<typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const
{
	if(items.size() == 0)
		return true;
	else
		return false;
}

template<typename T, typename Comparator>
void Heap<T, Comparator>::trickleUp(int index)
{
	int parent = (index-1)/mDegree;
	while(index >= 1 && comp(items[index],items[parent])) 
	{
		T temp = items[parent];
		items[parent] = items[index];
		items[index] = temp;
		trickleUp((index-1)/mDegree);  //recursive implementation
	}
}

template<typename T, typename Comparator>
void Heap<T, Comparator>::heapify(int index)
{
	if(items.size() <= 1) { return; }
	if(index*mDegree + 1 > items.size()-1) { return; }
	else
	{
		int sChild = (index*mDegree) + 1;

		//this condition is for checking the first child then all the other children
		if(sChild*mDegree + 1 < items.size())
		{
			for(int i = sChild; i < sChild + mDegree; i++)
			{
				if(comp(items[i], items[sChild])) { sChild = i; }
			}
		} 
		else
		{
			//for all other conditions
			for(int i = sChild; i < items.size(); i++)
			{
				if(comp(items[i], items[sChild])) { sChild = i; }
			}
		}
		if(!comp(items[index], items[sChild]))
		{
			T temp = items[index];
			items[index] = items[sChild];
			items[sChild] = temp;
			heapify(sChild); //recursive implementation
		}
	}
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return items[0];
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }

  items[0] = items[items.size()-1];
  items.pop_back();
  heapify(0);
}

#endif