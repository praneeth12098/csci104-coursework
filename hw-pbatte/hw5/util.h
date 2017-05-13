#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates  
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> intersect;

	typename std::set<T>::iterator it = s1.begin();
	for(; it != s1.end(); ++it)
	{
		const bool check = s2.find(*it) != s2.end();

		if(check) intersect.insert(*it);
	}

	return intersect;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> uSet;

	typename std::set<T>::iterator it2 = s2.begin();
	for(; it2 != s2.end(); ++it2)
	{
		uSet.insert(*it2);
	}

	typename std::set<T>::iterator it = s1.begin();
	for(; it != s1.end(); ++it)
	{
		const bool check = s2.find(*it) != s2.end();

		if(!check) uSet.insert(*it);
	}

	return uSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) ;

// trim from end
std::string &rtrim(std::string &s) ;

// trim from both ends
std::string &trim(std::string &s) ;
#endif
