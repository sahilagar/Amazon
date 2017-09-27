#include <sstream>
#include <iomanip>
#include <string>
#include "product.h"
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty
    ,const std::string size, const std::string brand) : 
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

Clothing::~Clothing()
{

}

//returns the set of keywords
std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> keyWords;

    std::set<std::string> tempSet = parseStringToWords(name_);
    keyWords = setUnion(keyWords, tempSet);
    tempSet.clear();
    tempSet = parseStringToWords(brand_); // add words in brand
    keyWords = setUnion(keyWords, tempSet);
    tempSet.clear();

    return keyWords;
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{


    return false;

}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Clothing::displayString() const
{ 
    stringstream ss;
    ss << name_ << endl;
    ss << "Brand: " << brand_ << " Size: " << size_ << endl;
    ss << price_<< " ";
    ss << qty_ << " left";
    ss << endl;

    string display = ss.str();

    return display;
}

/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream& os) const
{
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << size_ << std::endl;
    os << brand_ << std::endl;

}