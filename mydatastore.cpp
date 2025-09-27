#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "mydatastore.h"
#include "util.h"

MyDataStore::~MyDataStore() {
  // std::cout << "Entered " << __LINE__ << std::endl;
  // clean up allproducts
  for (unsigned int i = 0; i < allproducts.size(); i++) {
    delete (allproducts[i]);
  }
  // cleanup allusers
  std::map<std::string, User*>::iterator it;
  for (it = nametouser.begin(); it != nametouser.end(); ++it) {
    delete (it->second);
  }
  // for (unsigned int i = 0; i < allusers.size(); i++) {
  //   delete (allusers[i]);
  // }
  // cleanup all carts
  // for (std::map<std::string, std::vector<Product*>>::iterator it = useritems.begin(); i != useritems.end(); ++it) {
  //   delete *it;
  // }
}

/**
* Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p) {
  // std::cout << "Entered " << __LINE__ << std::endl;
  allproducts.push_back(p);

  // making a set of all keywords of current product
  std::set<std::string> currkws = p->keywords();
  std::set<std::string>::iterator it;
  // iterating through all keywords to add to kwtoprods map
  for (it = currkws.begin(); it != currkws.end(); ++it) {
    // std::map<std::string, std::set<Product*>>::iterator it2 = kwtoprods.find(*it);
    // if keyword exists in map, add to products that go with it
    // if (it2 != kwtoprods.end()) {
    //   it2->second.insert(p);
    // } else {
    //   // this means keyword does not exist, need to make a new pair / set that includes this product
    //   std::set<Product*> addprodset;
    //   addprodset.insert(p);
    //   kwtoprods.insert(std::make_pair(*it, addprodset));
    // 
    std::string temp = *it;
    kwtoprods[temp].insert(p);
  }
}

/**
* Adds a user to the data store
*/
void MyDataStore::addUser(User* u) {
  // std::cout << "Entered " << __LINE__ << std::endl;
  // allusers.push_back(u);
  // std::cout << "Adding user?" << std::endl;
  std::string usern = u->getName();
  if (nametouser.find(usern) == nametouser.end()) {
    nametouser.insert(std::make_pair(usern, u));
  }

}

/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  // std::cout << "Entered " << __LINE__ << std::endl;
  // keywords() from before returns appropiate keywords for the product
  // keywords() returns a set of strings - union and intersection passes through searchTerms


  /**
  * go through all products, call keywords and do intersection or union on keywords
  * set as first argument and terms set as second argument
  * 
  */

  /*
  pseudocode
  for product: // iterate over products
    // does this product match our search terms, given the search type?
    termsSet // turn the terms into a set
    keywordSet // get the set of keywords from the product
    intersectionSet // intersection b/w the termsSet and the Keyword set
    if type == 0 && size of the termsSet == intersectionSet:
      /// matches!
    if type == 1 && size of the intersectionSet > 0:
      // matches!

  */
  
  // // turn vector of terms into set to pass through intersection + union functinos
  // std::set<std::string> searchterms;
  // for (unsigned int i = 0; i < terms.size(); i++) {
  //   searchterms.insert(terms[i]);
  // }

  // // go through each product

  // for (unsigned int i = 0; i < allproducts.size(); i++) {
  //   std::set<std::string> kwset = allproducts[i]->keywords();
  //   std::set<std::string> intersectionset = setIntersection(kwset, searchterms);
  //   // if searchterms and intersection set sizes are == then product meets all terms
  //   if (type == 0 && searchterms.size() == intersectionset.size()) {
  //     finalproducts.push_back(allproducts[i]);
  //     // if there is at least one term overlapping btwn terms + keywords, then meets the OR criteria
  //   } else if (type == 1 && intersectionset.size() > 0) {
  //     finalproducts.push_back(allproducts[i]);
  //   }
  // }

  // REVISED VERSION: go through terms given and find it in the keywords -> turn all these instances of keywords into a set?
    std::vector<Product*> randvector;
    if (terms.empty()) {
      return randvector;
    }
    if (type==0 && (kwtoprods.find(terms[0]) == kwtoprods.end())) {
      return randvector;
    }
    // std::set<Product*>::iterator it;
    std::set<Product*> finalproducts;


    // going through terms given & find in kwtoprods
    if (type == 1) {
      for (unsigned int i = 0; i < terms.size(); i++) {
        // find terms in map
        if (kwtoprods.find(terms[i]) != kwtoprods.end()) {
          // for (it = kwtoprods.find(terms[i])->second.begin(); it != kwtoprods.find(terms[i])->second.end(); ++it) {
          //   finalproducts.insert(*it);
          // }
          finalproducts = setUnion(finalproducts, kwtoprods.find(terms[i])->second);
        }
      }
    } else if (type == 0) {
      // need to start w a set of keywords to use intersect on
      finalproducts = kwtoprods.find(terms[0])->second;
      for (unsigned int i = 1; i < terms.size(); i++) {
        // find terms in map & find intersection with past
        finalproducts = setIntersection(kwtoprods.find(terms[i])->second, finalproducts);
      }
    }
    
    for (std::set<Product*>::iterator lastit = finalproducts.begin(); lastit != finalproducts.end(); ++lastit) {
      randvector.push_back(*lastit);
    }

    return randvector;

}

/**
* Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile) {
  // std::cout << "Entered " << __LINE__ << std::endl;
  // std::cout << "end==begin? " << std::boolalpha << (nametouser.begin()==nametouser.end()) << std::endl;
  // std::cout << "isEmpty? " << std::boolalpha << (nametouser.empty()) << std::endl;
  // use virtual dump function
  ofile << "<products>" << std::endl;
  for (unsigned int i = 0; i < allproducts.size(); i++) {
    allproducts[i]->dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
  // go thorugh user map 
  std::map<std::string, User*>::iterator it;
  // std::cout << "end==begin? " << std::boolalpha << (nametouser.begin()==nametouser.end()) << std::endl;
  // std::cout << "isEmpty? " << std::boolalpha << (nametouser.empty()) << std::endl;
  // std::cout << "size? " << (nametouser2.size()) << std::endl;
  for (it = nametouser.begin(); it != nametouser.end(); ++it) {
    /* <users>
    aturing 100.00 0
    johnvn 50.00 1
    adal 120.00 1
    (there already is a dump function for users - variables not seperated
    directly by lines, just endl for each user )
    </users> */
    User* u = it->second;
    // std::cout << "In the loop: " << it->first << std::endl;
    u->dump(ofile);
  } 
  ofile << "</users>" << std::endl;

}

bool MyDataStore::addCartItem(std::string username, Product* item) {
  // std::cout << "Entered " << __LINE__ << std::endl;
  /* display products start at 1 so need to 
  subtract 1 from users choice
  also now need to associate user w their products -> map 
  ...map string(user)->vector<Product*>(items)? \\ added as data member */
  
  // COMPLETE THIS OUTSIDE THE FUNCTION & BEFORE IS CALLED::::
  // if (terms.size() < 2  || 
  // std::stoi(terms[1]) > hits.size() || std::stoi(terms[1]) < 1) {
  //     cout << "Invalid request" << endl;
  //     // SHOULD I DO ANYTHING ELSE? SEND USER BACK?
  // }


  /* need to check if user is valid */
  // bool found = false;
  if (nametouser.find(username) == nametouser.end()) {
    return false;
  }
  
  
  // check if username is in map already
  // std::map<std::string, std::vector<Product*>>::iterator it = useritems.find(username);
  // if (useritems.find(username) == useritems.end()) // user doesnt exist yet
  // {
  //     std::vector<Product*> newvec;
  //     useritems.insert(std::make_pair(username, newvec));
  // }
  // by now user exists, now add items to vector list
  // std::map<std::string, std::vector<Product*>>::iterator it2 = useritems.find(username);
  useritems[username].push_back(item);
  // it2->second.push_back(item);
  
  return true;
}
bool MyDataStore::viewCart(std::string username) {
  // std::cout << "Entered " << __LINE__ << std::endl;
  std::map<std::string, std::vector<Product*>>::iterator it = useritems.find(username);
  if (it != useritems.end()) // user found
  {
      int i = 0;
      // iterating through the products in the cart of the found user
      std::vector<Product*>::iterator it2;
      for (it2 = it->second.begin(); it2 != it->second.end(); it2++) {
        std::cout << "Item " << (i+1) << std::endl << (*it2)->displayString() << std::endl;
        i++;
      }
      return true;
  }
  return false;
}

bool MyDataStore::buyCart(std::string username) {
  // std::cout << "Entered " << __LINE__ << std::endl;
  std::map<std::string, std::vector<Product*>>::iterator it = useritems.find(username);
  if (it != useritems.end()) // user found
  {
      
      User* curruser;
      // for (unsigned int i = 0; i < allusers.size(); i++) {
      //   if(allusers[i]->getName() == username) {
      //     curruser = allusers[i]; // pointer to same user
      //     break;
      //   }
      // }
      // finding username spot in the name to user map - definitely exists bc user is found in map already?
      if (nametouser.find(username) != nametouser.end()) {
        curruser = nametouser.find(username)->second;
      }
      // list of user items
      std::vector<Product*>& currlist = it->second; // using alias to change og item list
      std::vector<Product*> boughtcurrlist; // making an empty list to add not bought items to
      for (unsigned int i = 0; i < currlist.size(); i++) {
        if(currlist[i]->getQty() >= 1 && curruser->getBalance() >= currlist[i]->getPrice()) {
          currlist[i]->subtractQty(1);
          curruser->deductAmount(currlist[i]->getPrice());
          // currlist.erase(currlist.begin() + i);
        } else {
          boughtcurrlist.push_back(currlist[i]);
        }
      }
      // reassign the curruser's product list to the new list that shows all unbought items (if any)
      it->second = boughtcurrlist;
      return true;
  }
  return false;
}