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
    typename std::set<T>::iterator it;
    typename std::set<T>::iterator it2;

    std::set <typename T> result;

    for(it = s1.begin(); it!= s1.end(); ++it){
        result.insert((*it));
    }
    for(it2 = s2.begin(); it2!= s2.end(); ++it2){
        result.insert((*it2));
    }

    return result;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T>::iterator it;

    std::set <typename T> result;

    for(it = s1.begin(); it!= s1.end(); ++it){
        set<T>::iterator it2 = s2.find(*it);
        if(it2!=s2.end()){
            result.insert((*it));
        }
    }

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
