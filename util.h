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
	typename std::set<T>::iterator it;
	std::set<T> s3;

	//for every value in s1
	for (it = s1.begin(); it != s1.end(); ++it)
	{
		if (s2.find(*it) != s2.end()) //if found in s2, add it
		{
			s3.insert(*it);
		}
	}
	return s3;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

	typename std::set<T>::iterator it;
	for (it = s2.begin(); it != s2.end(); ++it)
	{
		if (s1.find(*it) == s1.end()) //if not found in s1, add it
		{
			s1.insert(*it);
		}
	}
	return s1;
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
