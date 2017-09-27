#include <sstream>
#include <iomanip>
#include <string>
#include "product.h"
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty
    ,const std::string genre, const std::string rating) : 
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie()
{

}

//returns the set of keywords
std::set<std::string> Movie::keywords() const
{
    std::set<std::string> keyWords;

    std::set<std::string> tempSet = parseStringToWords(name_);
    keyWords = setUnion(keyWords, tempSet);
    tempSet.clear();
    tempSet = parseStringToWords(genre_); // add words in genre
    keyWords = setUnion(keyWords, tempSet);
    tempSet.clear();

    return keyWords;
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;

}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Movie::displayString() const
{

    stringstream ss;
    ss << name_ << endl;
    ss << "Genre: " << genre_ << " ";
    ss << "Rating: " << rating_ << endl;
    ss << price_<< " ";
    ss << qty_ << " left";

    string display = ss.str();

    return display;
}

/**
 * Outputs the product info in the database format
 */
void Movie::dump(std::ostream& os) const
{
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << genre_ << std::endl;
    os << rating_ << std::endl;

}