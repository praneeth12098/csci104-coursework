#ifndef QUEUEINT_H
#define QUEUEINT_H

#include "llistint.h"


class QueueInt {
public:
    /**
     * Default constructor - empty queue
     */
    QueueInt();

    // ~QueueInt();

    // QueueInt(const QueueInt& other);

    // QueueInt& operator+=(QueueInt& other);
    /**
     * Returns the current number of items in the queue in O(1)
     */
    int size() const;

    /**
     * Returns true if the queue is empty, false otherwise in O(1)
     */
    bool empty() const;

    /**
     * Add to the back of the queue in O(1)
     */
    void push(const int& val);

    /**
     * Removes the value at the front of the queue in O(1)
     */
    void pop();

    /**
     * Returns the value at the front of the queue  in O(1)
     */
    int const & front() const;

    /**
     *  Concatenate the contents of the other queue
     *  to the back of this queue in O(1) leaving
     *  the other queue empty
     */
    void concatenate(QueueInt& other);

private:
    /**
     * Data members -- YOU COMPLETE!!!
     */
    LListInt list;
};

#endif
