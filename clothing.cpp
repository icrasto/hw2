#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, 
int qty, const std::string size, const std::string brand) : Product(category, name, price, qty) {
  size_ = size;
  brand_ = brand;
}

/**
     * Returns the appropriate keywords that this product should be associated with
     */

/** Clothing: the words in the brand should be searchable keywords **/
std::set<std::string> Clothing::keywords() const {
  std::set<std::string> allkeywords;


  // split up the brand words
  std::set<std::string> brandkw;
  brandkw = parseStringToWords(brand_);
  std::set<std::string>::iterator it;
  for(it = brandkw.begin(); it != brandkw.end(); ++it)
  {
    allkeywords.insert(*it);
  }

  // split up name words

  std::set<std::string> namekw;
  namekw = parseStringToWords(name_);
  std::set<std::string>::iterator it2;
  for(it2 = namekw.begin(); it2 != namekw.end(); ++it2)
  {
    allkeywords.insert(*it2);
  }

  

  return allkeywords;
}

    /* Returns a string to display the product info for hits of the search DO
     */



std::string Clothing::displayString() const {

  std::string total;
  total += name_ + "\n";
  total += "Size: " + size_ + " Brand: " + brand_ + "\n";
  total += std::to_string(price_) + " " + std::to_string(qty_) + " left.";

  return total;
  
}

/**
     * Outputs the product info in the database format
     */

/** follow format:
  product category (clothing)
  name
  price
  Quantity
  size
  brand
  **/
void Clothing::dump(std::ostream& os) const {
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << size_ << std::endl;
  os << brand_ << std::endl;
}