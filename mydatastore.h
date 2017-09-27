#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include "datastore.h"
#include "util.h"
#include "review.h"

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    //cart functionality

    void addToCart(std::string name, std::vector<Product*> hits, int index);

    void viewCart(std::string name);

    void buyCart(std::string name);

    void addReview(Review* r);

    std::vector<User*> getUsers() {return users;}

    std::vector<Product*> getProducts() {return products;}

    std::queue<Product*>& getUserCart(User* u) {return mappedUsers_[u];}

    User* getUserFromName(std::string name) {return nameToUser[name];}

    void removeFromCart(std::string name, unsigned int index);

    std::vector<Review*> getReviews() {return reviews_;}




protected:

    std::map<User*, std::queue<Product*> > mappedUsers_;
    std::map<std::string, std::set<Product*> > mappedProducts_;

    std::vector<Review*> reviews_;
    std::map<std::string, std::vector<Review*> > productNameReviews;

    std::vector<User*> users;
    std::vector<Product*> products;

    std::map<std::string, User*> nameToUser;


};
#endif