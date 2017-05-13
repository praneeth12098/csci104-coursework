#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

private:
    /// Add whatever helper functions you need below

    void heapify(int index);
    void trickleUp(int index);


    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    // You complete.
    store_.push_back(std::make_pair(priority, item));
    keyToLocation_[item] = store_.size()-1;
    trickleUp(store_.size()-1);

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    // You complete
    int index = keyToLocation_[item];
    keyToLocation_[item] = store_.size()-1;
    store_[index].first = priority;
    heapify(index);

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    // You complete

    return store_[0].second;

}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    // You complete

    store_[0] = store_[store_.size()-1];
    store_.pop_back();
    keyToLocation_.erase(store_[0].second);
    heapify(0);
}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::trickleUp(int index)
{
    int parent = (index-1)/m_;
    while(index >= 1 && c_(store_[index].first,store_[parent].first)) 
    {
        // int temp2 = keyToLocation_[store_[parent].second];
        // keyToLocation_[store_[parent].second] = index;
        // keyToLocation_[store_[index].second] = temp2;

        // std::pair<double, T> temp = store_[parent];
        // store_[parent] = store_[index];
        // store_[index] = temp;
        int p = keyToLocation_[store_[parent].second];
        int c = keyToLocation_[store_[index].second];

        std::pair<double, T> temp = store_[parent];
        keyToLocation_[store_[parent].second] = c;

        store_[parent] = store_[index];
        keyToLocation_[store_[index].second] = p;

        store_[index] = temp;

        trickleUp((index-1)/m_);  //recursive implementation
    }
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::heapify(int index)
{
    if(store_.size() <= 1) { return; }
    if(index*m_ + 1 > store_.size()-1) { return; }
    else
    {
        int sChild = (index*m_) + 1;

        //this condition is for checking the first child then all the other children
        if(sChild*m_ + 1 < store_.size())
        {
            for(int i = sChild; i < sChild + m_; i++)
            {
                if(c_(store_[i].first, store_[sChild].first)) { sChild = i; }
            }
        } 
        else
        {
            //for all other conditions
            for(int i = sChild; i < store_.size(); i++)
            {
                if(c_(store_[i].first, store_[sChild].first)) { sChild = i; }
            }
        }
        if(!c_(store_[index].first, store_[sChild].first))
        {
            int left = keyToLocation_[store_[sChild].second];
            int right = keyToLocation_[store_[index].second];

            std::pair<double, T> temp = store_[sChild];
            store_[sChild] = store_[index];

            keyToLocation_[store_[sChild].second] = right;
            store_[index] = temp;

            keyToLocation_[store_[index].second] = left;
            //index = sChild;

            heapify(sChild); //recursive implementation
        }
    }
}

#endif