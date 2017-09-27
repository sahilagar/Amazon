#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore()
{

}
MyDataStore::~MyDataStore()
{
    map<User*, std::queue<Product*> >::iterator mit;    
    for (mit = mappedUsers_.begin(); mit != mappedUsers_.end(); ++mit)
    {
        delete mit->first;
    }

    set<Product*> deleteSet;
    map<std::string, std::set<Product*> >::iterator mit2;
    for (mit2 = mappedProducts_.begin(); mit2 != mappedProducts_.end(); ++mit2)
    {
        set<Product*> tempSet = mit2->second;
        deleteSet = setUnion(deleteSet,tempSet);
    }

    for(set<Product*>::iterator it = deleteSet.begin(); it !=deleteSet.end(); ++ it)
    {
        delete *it;
    }

    for (unsigned int i=0; i < reviews_.size(); i++)
    {
        delete reviews_[i];
    }
}

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p)
{
    //keywords for product passed in
    set<string> keyWords = p->keywords();
    for (set<string>::iterator sit = keyWords.begin(); sit!= keyWords.end(); ++sit)
    {
        set<Product*> tempSet;
        string tempKeyWord = *sit;
        //if keyword not found in map
        if (mappedProducts_.find(*sit) == mappedProducts_.end()) 
        {
            tempSet.insert(p);
            mappedProducts_.insert(make_pair(tempKeyWord, tempSet));
        }
        else //keyword found in map
        {
            (mappedProducts_.find(*sit)->second).insert(p);        
        }
        tempSet.clear();
    }

    products.push_back(p);

}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u)
{
    queue<Product*> cart;
    mappedUsers_.insert(make_pair(u,cart));
    users.push_back(u);
    //cout << users.size() << endl;
    //cout << "Pushed Back User" << endl;

    nameToUser[u->getName()] = u;
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    vector<Product*> matchingProducts;
    set<Product*> baseSet;

    bool oneTimeFlag = false;

    for (unsigned int i=0; i < terms.size(); i++)
    {
        string searchTerm = terms[i];
        //if the term was found in the map, OR search
        if (mappedProducts_.find(searchTerm) != mappedProducts_.end() && type == 1)
        {
            //put all the products in the set into baseSet union
            set<Product*> productSet = mappedProducts_.find(searchTerm)->second;
            baseSet = setUnion(baseSet,productSet);
        }
        //if the term was found in the map, AND search
        else if (mappedProducts_.find(searchTerm) != mappedProducts_.end() && type == 0)
        {
            set<Product*> productSet = mappedProducts_.find(searchTerm)->second;
            //initial case baseSet is empty
            if (!oneTimeFlag)
            {
                baseSet = productSet;
                oneTimeFlag = true;
            }
            else
            {
                baseSet = setIntersection(baseSet,productSet);
            }                   
        }
    }

    //put baseset into vector
    for (set<Product*>::iterator it = baseSet.begin(); it != baseSet.end(); ++it)
    {
        matchingProducts.push_back(*it);
    }   

    return matchingProducts;

}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile)
{
    set<Product*> allProducts;
    //products
    ofile << "<products>" << endl;
    map<std::string, std::set<Product*> >::iterator mit;
    for (mit = mappedProducts_.begin(); mit != mappedProducts_.end(); ++mit)
    {
        allProducts = setUnion(allProducts, mit->second);
    }

    for (set<Product*>::iterator it = allProducts.begin(); it!=allProducts.end();++it)
    {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;
    //users

    ofile << "<users>" << endl;
    map<User*, std::queue<Product*> >::iterator mit2;
    for (mit2 = mappedUsers_.begin(); mit2 != mappedUsers_.end(); ++mit2)
    {
        (mit2->first)->dump(ofile);
    }
    ofile << "</users>" << endl;

    //reviews
    ofile << "<reviews>" << endl;
    for (unsigned int i=0; i != reviews_.size(); i++)
    {
        Review* currReview = reviews_[i];
        ofile << currReview->prodName << endl;
        ofile << currReview->rating << " " << currReview->username << " " << currReview->date;
        ofile << " " << currReview->reviewText << endl;
    }
    ofile << "</reviews>" << endl;

}

//cart functionality

void MyDataStore::addToCart(string name, vector<Product*> hits, int index)
{
    map<User*, std::queue<Product*> >::iterator mit;    
    for (mit = mappedUsers_.begin(); mit != mappedUsers_.end(); ++mit)
    {
        if ((mit->first)->getName() == name)
        {
            Product* p = hits[index];
            (mit->second).push(p);
        }
    }

}

void MyDataStore::viewCart(string name)
{
    map<User*, std::queue<Product*> >::iterator mit;
    for (mit = mappedUsers_.begin(); mit != mappedUsers_.end(); ++mit)
    {
        if ((mit->first)->getName() == name)
        {
            for (unsigned int i=0; i < (mit->second).size(); i++)
            {
                Product* p = (mit->second).front();

                (mit->second).pop();
                (mit->second).push(p);
            }
        }
    }

    /*Item 1
Hidden Figures DVD
Genre: Drama Rating: PG
17.99  1 left.*/

}

void MyDataStore::buyCart(string name)
{
    bool flag = false;

    map<User*, std::queue<Product*> >::iterator mit;
    for (mit = mappedUsers_.begin(); mit != mappedUsers_.end(); ++mit)
    {
        if ((mit->first)->getName() == name) //found user
        {
            flag = true;
            User* user = mit->first;
            unsigned int queueSize = (mit->second).size();
            for (unsigned int i=0; i < queueSize; i++)
            {
                Product* p = (mit->second).front();
                if (user->getBalance() > p->getPrice() && p->getQty() > 0)//user can afford and item in stock
                {
                    user->deductAmount(p->getPrice());
                    p->subtractQty(1);
                    (mit->second).pop();
                }
                else
                {
                    (mit->second).pop();
                    (mit->second).push(p);
                }
            }
        }
    }

    if (!flag){
        cout << "Invalid username" << endl;
    }


}
void MyDataStore::addReview(Review* r)
{
    reviews_.push_back(r);

    //add the rating data member to the product
    for (unsigned int i= 0; i < products.size(); i++)
    {
        if (r->prodName == products[i]->getName())
        {
            products[i]->addRating(r->rating);
        }
    }
    
}
void MyDataStore::removeFromCart(std::string name, unsigned int index)
{
    User* temp = getUserFromName(name);

    map<User*, std::queue<Product*> >::iterator mit;
    mit = mappedUsers_.find(temp);

    

    unsigned int size = mit->second.size();
    for (unsigned int i=0; i < size; i++)
    {
        Product* p = mit->second.front();
        mit->second.pop();
        if (i != index) //will not push delete index
        {
            mit->second.push(p);
        }      
        
    }
    //cout << "Cart Size: " << mit->second.size() << endl;



}