#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <set>
#include <vector>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> keyWords; //set to return at the end
    stringstream ss(rawWords); //create the string stream
    std::string word; //for the string stream to insert to

    std::vector<string> storeWords; //store potential keywords

    while(ss >> word) //do for the whole string
    {       
        //remove extra whitespace and make it all lower case
        word = trim(word); 
        word = convToLower(word);
        std::string tempWord = ""; //build the keywords

        for (unsigned int i=0; i < word.size(); i++)
        {
            if (ispunct(word[i])) //char is punctutation
            {
                storeWords.push_back(tempWord);
                tempWord.clear();
            }
            else //character was not a punctutation
            {
                tempWord += word[i];
            }
        } 
        storeWords.push_back(tempWord);                      
    }
    //search through the vector
    for (unsigned int i=0; i < storeWords.size(); i++)
    {
        std::string temp_string = storeWords[i];
        //greater than 2 and not in the set already
        if (temp_string.size() >= 2 && keyWords.find(temp_string) == keyWords.end())
        {
            keyWords.insert(temp_string);
        }
    }
    return keyWords;

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
