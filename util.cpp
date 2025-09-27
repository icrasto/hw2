#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/

        /* Complete the parseStringToWords() in util.cpp according to the 
    specification given above for taking a string of many words and splitting 
    them into individual keywords (split at punctuation, with at least 
    2 character words)
 */

std::set<std::string> parseStringToWords(string rawWords)
{
/* INFO: we define a keyword to be any string of 2 or more characters. 
    If such a word has punctuation it should be split at each punctuation 
    character and the resulting substrings (of 2 or more characters) should be used as 
    keywords. Here are some examples:
        Men's should yield just a keyword of Men
        J. would not yield any keyword since the remaining substring J is only 1 character
        I'll would yield just ll since that substring is 2 or more characters 
        (this is obviously a poor keyword but we’ll follow this rule for simplicity)
 */

    // using functions below to clean up the sides
    rawWords = trim(rawWords);
    rawWords = convToLower(rawWords);

    std::set<std::string> allkeywords;
    std::string subword;
    for (unsigned int i = 0; i < rawWords.length(); i++) {
        if (ispunct(rawWords[i]) == false && isblank(rawWords[i]) == false) {
            subword += rawWords[i];
        } else {
            if (subword.length() >=2) {
                allkeywords.insert(subword);
                subword = "";
            } else {
                // this would mean char is punctuation but subword is less than 2 so need to reset
                subword = "";
            }
        }
    }
    if (subword.length() >= 2) {
        allkeywords.insert(subword);
    }

    return allkeywords;



}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
