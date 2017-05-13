#include "queueint.h"

QueueInt::QueueInt()
{

}

int QueueInt::size() const
{
	return list.size();
}

bool QueueInt::empty() const
{
	return list.size() == 0;
}

void QueueInt::push(const int& val)
{
	list.push_back(val);
}

void QueueInt::pop()
{
	list.remove(0);
}

int const& QueueInt::front() const
{
	return list.get(0);
}

void QueueInt::concatenate(QueueInt& other)
{
	list += other.list;
}