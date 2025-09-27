#include "util.h"
#include "book.h"
#include "movie.h"
#include "clothing.h"
#include "product.h"
#include "mydatastore.h"
using namespace std;


int main() {

  // testing out book.cpp functions and creations

  Book* Book1 = new Book("book", "Hunger Games", 12.00, 3, "1234567876543", "Suzanne Collins");
  // testing display string
  std::cout << "Displaying Book 1 info: " << Book1->displayString() << std::endl;
  // displaying keywords
  std::set<string> testkeywords = Book1->keywords();
  std::cout << "Book1 keywords: " << std::endl;

  std::set<std::string>::iterator it;
  for(it = testkeywords.begin(); it != testkeywords.end(); ++it)
  {
    std::cout << *it << std::endl;
  }

  Book Book2("book", "CSCI 104 Manual", 100.34, 1, "23847923742198", "I'll be testing. the punct?uation");
  std::set<string> testkeywords2 = Book2.keywords();
  std::cout << "Book2 keywords: " << std::endl;

  std::set<std::string>::iterator it2;
  for(it2 = testkeywords2.begin(); it2 != testkeywords2.end(); ++it2)
  {
    std::cout << *it2 << std::endl;
  }

  // testing out movie.cpp

  Movie* Movie1 = new Movie("movie", "Despicable Me w/ diff.erent punc!uation", 10.15, 20, "comedy", "8");
  std::cout << "Displaying Movie 1 info: " << Movie1->displayString() << std::endl;

  // displaying keywords
  std::set<string> testkeywords3 = Movie1->keywords();
  std::cout << "Movie 1 keywords: " << std::endl;

  std::set<std::string>::iterator it3;
  for(it3 = testkeywords3.begin(); it3 != testkeywords3.end(); ++it3)
  {
    std::cout << *it3 << std::endl;
  }

  // testing out clothing.cpp

  Clothing Clothing1("clothing", "Urban Outfitters x Miu Miu vers. three shirt", 249.99, 3, "4", "UOMM x anthropologie");
  std::cout << "Displaying Clothing 1 info: " << Clothing1.displayString() << std::endl;

  // displaying keywords
  std::set<string> testkeywords4 = Clothing1.keywords();
  std::cout << "Clothing 1 keywords: " << std::endl;

  std::set<std::string>::iterator it4;
  for(it4 = testkeywords4.begin(); it4 != testkeywords4.end(); ++it4)
  {
    std::cout << *it4 << std::endl;
  }

  // testing datastore, users, and some menu functions

  MyDataStore bellastore;
  bellastore.addProduct(Book1);
  // bellastore.addProduct(Book2);
  bellastore.addProduct(Movie1);
  // bellastore.addProduct(Clothing1);
  User* valerie = new User("valerie", 200, 0);
  bellastore.addUser(valerie);

  bellastore.addCartItem("valerie", Book1);
  bellastore.addCartItem("valerie", Movie1);
  // bellastore.addCartItem("valerie", Movie1);
  // bellastore.addCartItem("valerie", Clothing1);
  

  std::cout << "Seeing Valerie's Cart:" << std::endl;
  bellastore.viewCart("valerie");

  return 0;


}