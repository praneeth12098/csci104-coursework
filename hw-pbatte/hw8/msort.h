#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp);

template <class T, class Comparator>
void msort(vector<T>& myArray, int start, int end, Comparator comp);

template <class T, class Comparator>
void merge(vector<T>& myArray, int start, int mid, int end, Comparator comp);


template <class T, class Comparator>
void mergeSort(vector<T>& myArray, Comparator comp)
{
	msort(myArray, 0, myArray.size(), comp);
}

template <class T, class Comparator>
void msort(vector<T>& myArray, int start, int end, Comparator comp)
{
	//checking if list has more than 1 item
	if(start + 1 < end)
	{
		int mid = (start+end)/2;
		msort(myArray, start, mid, comp);
		msort(myArray, mid, end, comp);
		merge(myArray, start, mid, end, comp);
	}
}

template <class T, class Comparator>
void merge(vector<T>& myArray, int start, int mid, int end, Comparator comp)
{
	vector<T> output;
	int ind1 = start; //sub array 1 index
	int ind2 = mid; //sub array 2 index
	int ind; //myarray index;

	//while array is not empty push smaller elements to output array
	while(ind1 < mid && ind2 < end) 
	{
		if(comp(myArray[ind1], myArray[ind2]))
		{
			output.push_back(myArray[ind1]); ind1++;
		}
		else
		{
			output.push_back(myArray[ind2]); ind2++;
		}
	}

	//while one of the sublists has elements push remaining elements to output
	while(ind1 < mid)
	{
		output.push_back(myArray[ind1]); ind1++;
	}
	while(ind2 < end)
	{
		output.push_back(myArray[ind2]); ind2++;
	}

	//copying output vector back
	ind1 = start;
	for (ind = 0; ind < output.size(); ind++)
    {
      myArray[ind1] = output[ind];
      ind1++;
    }
}

struct AlphaStrComp {
    bool operator()(const Product* lhs, const Product* rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs->getName() < rhs->getName(); 
    }
  };

 struct RatingComp {
 	bool operator()(const Product* lhs, const Product* rhs)
 	{
 		return lhs->getRating() > rhs->getRating();
 	}
 };

 struct DateComp {
 	bool operator()(const Review* lhs, const Review* rhs)
 	{
 		string rlhs = lhs->date;
 		string rrhs = rhs->date;

 		return rlhs > rrhs;
 	}
 };

 struct PairComp {
 	bool operator() (const std::pair<std::string, double> lhs, const std::pair<std::string, double> rhs)
 	{
 		return lhs.second > rhs.second;
 	}
 };