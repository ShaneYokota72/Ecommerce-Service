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
std::set<std::string> parseStringToWords(std::string rawWords)
{
    //separate the words when they have a punctuation
    std::set <std::string> result;
    int wordlen = 0;
    int curridx = 0;
    int wordbegin = 0;

    for(unsigned int i=0; i<rawWords.length(); i++){
        if(rawWords[i] == '.' || rawWords[i] == '\'' || rawWords[i] == ',' || rawWords[i] == ':' || rawWords[i] == ' ' || rawWords[i]=='\0'){
            if(wordlen>1){
                std::string temp = rawWords.substr(wordbegin, wordlen);
                result.insert(temp);
                wordlen = 0;
                wordbegin = i+1;
            }else {
                wordlen = 0;
                wordbegin = i+1;
            }
        } else if(i == rawWords.length()-1 && wordlen>1){
            std::string temp = rawWords.substr(wordbegin, wordlen+1);
            result.insert(temp);
            wordlen = 0;
            wordbegin = i+1;
        }else {
            curridx++;
            wordlen++;
        }
    }

    return result;
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
