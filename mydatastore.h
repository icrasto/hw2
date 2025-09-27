#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include <map>

/**
 * 
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */


class MyDataStore : public DataStore {
public:
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
    bool addCartItem(std::string username, Product* item);
    bool viewCart(std::string username);
    bool buyCart(std::string username);

private:
  std::vector<Product*> allproducts;
  // std::vector<User*> allusers;

  std::map<std::string, std::set<Product*>> kwtoprods;
  std::map<std::string, User*> nametouser;
  std::map<std::string, User*> nametouser2;
  std::map<std::string, std::vector<Product*>> useritems; //carts
  // need to change search and checking valid username
  


};

#endif
