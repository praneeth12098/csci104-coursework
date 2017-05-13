#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(std::string rawWords)
{

    std::set<std::string> keywords;
    std::string temp1;
    std::string temp;
    std::stringstream ss(rawWords);

    while(ss >> temp1)
    {
        //making everything lowercase first
        temp = convToLower(temp1);

        std::string t1, t2;
        bool check = false;
        for(unsigned int i = 0; i < temp.size(); i++) 
        {
            if(ispunct(temp[i]))
            {
                t1 = temp.substr(0, i);
                t2 = temp.substr(i+1, temp.size());
                check = true;
            }
        }
        if(check)
        {
            if(t1.size() >= 2) keywords.insert(t1);

            if(t2.size() >= 2) keywords.insert(t2);
        }
        else
            keywords.insert(temp);
    }
    return keywords;
}


/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
