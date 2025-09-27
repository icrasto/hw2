#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  /* intersections are AND searches */
  std::set<T> results;
  // maps and keywords() functions i dont think are written yet but these r helpers?

  // go through first set and see if it exists in the other set, if so add to new set
  // it1 is not the value itself but pointer to set value
  typename std::set<T>::iterator it1;
// TOTAL RUNTIME: O(nlogn)

  // runs O(n)
  for (it1 = s1.begin(); it1 != s1.end(); ++it1) {
    // this means that it was found in the other set, add to new set
    // find function runs O(logn) -> CHECK 
    if (s2.find(*it1) != s2.end()) {
      // check runtime i think O(logn)
      results.insert(*it1);
    }
  }
  return results;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  // go through first and second set and add to set, will automatically ignore if already in set

  std::set<T> results;

  typename std::set<T>::iterator it1;
  typename std::set<T>::iterator it2;
  // O(n)
  for (it1 = s1.begin(); it1 != s1.end(); ++it1) {
    // runs O(logn)
    results.insert(*it1);
  }

  for (it2 = s2.begin(); it2 != s2.end(); ++it2) {
    // runs O(logn)
    results.insert(*it2);
  }
  return results;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
