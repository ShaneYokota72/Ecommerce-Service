#include "movie.h"
#include "util.h"
#include <iomanip>
using namespace std;

//MOVIE:the movie’s genre should be a searchable keyword
Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating) : Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}
Movie::~Movie(){ };

std::set<std::string> Movie::keywords() const{
    //add the keyword for this product
    set<string> result;
    set<string> genreset = parseStringToWords(convToLower(genre_));
    result.insert(genreset.begin(), genreset.end());
    return result;
}

std::string Movie::displayString() const{
    //display the output in a string
    string res = "";
    res = res + name_ + '\n' +
    "Genre: " + genre_ + " Rating: " + rating_ + '\n' +
    to_string(price_) + " " + to_string(qty_) + " left.";
    return res;
}

void Movie::dump(std::ostream& os) const{
    //dump following the format
    os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << 
    "\n" << genre_ << "\n" << rating_ << endl;
}

void Movie::sold(){
    qty_--;
}