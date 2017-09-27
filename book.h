#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "product.h"

class Book : public Product {
public:
    Book(const std::string category, const std::string name, double price, int qty,
        const std::string ISBN, const std::string Author);
    ~Book();

    //returns the set of keywords
    std::set<std::string> keywords() const;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;


protected:
    std::string ISBN_;
    std::string Author_;

};
#endif