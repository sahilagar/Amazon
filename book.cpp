#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include "product.h"
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty
    ,const std::string ISBN, const std::string Author) : 
    Product(category, name, price, qty),
    ISBN_(ISBN),
    Author_(Author)
{

}

Book::~Book()
{

}

//returns the set of keywords
std::set<std::string> Book::keywords() const
{
    std::set<std::string> keyWords;

    std::set<std::string> tempSet = parseStringToWords(name_);
    
    keyWords = setUnion(keyWords, tempSet);
    tempSet.clear();
    tempSet = parseStringToWords(Author_);
    keyWords = setUnion(keyWords, tempSet);
    tempSet.clear();
    keyWords.insert(ISBN_);

    return keyWords;
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Book::isMatch(std::vector<std::string>& searchTerms) const
{

    /*std::set<std::string> keyWords = keywords();
    for (unsigned int i=0; i < searchTerms.size(); i++)
    {
        std::string temp_string = searchTerms[i];
        if (keyWords.find(temp_string) != keyWords.end()) //if word was found
        {
            return true;
        }
    }*/

    return false;

}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const
{
    stringstream ss;
    ss << name_ << endl;
    ss << "Author: " << Author_ << " ISBN: " << ISBN_ << endl;
    ss << price_<< " ";
    ss << qty_ << " left" << endl;

    string display = ss.str();

    return display;
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream& os) const
{
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << ISBN_ << std::endl;
    os << Author_ << std::endl;

}