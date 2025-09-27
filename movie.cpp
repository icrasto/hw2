#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, 
int qty, const std::string genre, const std::string rating) : Product(category, name, price, qty) {
  genre_ = genre;
  rating_ = rating;
}

/**
     * Returns the appropriate keywords that this product should be associated with
     */

/** Movie: the movie’s genre should be a searchable keyword **/
std::set<std::string> Movie::keywords() const {
  std::set<std::string> allkeywords;
  // split up name words & assign to allkeywords
  allkeywords = parseStringToWords(name_);
  // genre info case sensitive
  allkeywords.insert(convToLower(genre_));
  // std::set<std::string> namekw;
  return allkeywords;

}

    /* Returns a string to display the product info for hits of the search DO
     */


std::string Movie::displayString() const {

  std::string total;
  total += name_ + "\n";
  total += "Genre: " + genre_ + " Rating: " + rating_ + "\n";
  total += std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  
  return total;
  
}

/**
     * Outputs the product info in the database format
     */

/** follow format:
  product category (movie)
  name
  price
  Quantity
  genre
  rating
  **/
void Movie::dump(std::ostream& os) const {
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << genre_ << std::endl;
  os << rating_ << std::endl;
}