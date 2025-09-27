#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, 
int qty, const std::string ISBN, const std::string author) : Product(category, name, price, qty) {
  ISBN_ = ISBN;
  author_ = author;
}

/**
     * Returns the appropriate keywords that this product should be associated with
     */

/** Books: the words in the author’s name should be searchable keywords as well as the book’s ISBN number **/
std::set<std::string> Book::keywords() const {
  std::set<std::string> allkeywords;

  // no adjustment needed for ISBN info
  allkeywords.insert(ISBN_);

  // split up the author words
  std::set<std::string> authorkw;
  authorkw = parseStringToWords(author_);
  std::set<std::string>::iterator it;
  for(it = authorkw.begin(); it != authorkw.end(); ++it)
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

   

std::string Book::displayString() const {

  std::string total;
  total += name_ + "\n";
  total += "Author: " + author_ + " ISBN: " + ISBN_ + "\n";
  total += std::to_string(price_) + " " + std::to_string(qty_) + " left.";

  return total;
  
}

/**
     * Outputs the product info in the database format
     */

/** follow format:
  product category (book)
  name
  price
  Quantity
  ISBN
  author
  **/
void Book::dump(std::ostream& os) const {
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << ISBN_ << std::endl;
  os << author_ << std::endl;
}