#include "movie.h"

using namespace std;

//MOVIE:the movie’s genre should be a searchable keyword
Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating) : Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}
Movie::~Movie(){ };

std::set<std::string> Movie::keywords() const{
    set<string> result;
    result.insert(getName());
    result.insert(genre_);
    return result;
}

std::string Movie::displayString() const{
    /* 
    <name>
    Genre: <genre> Rating: <rating>
    <price> <quantity> left.
     */
    string res;
    res = name_ + '\n' +
    "Genre: " + genre_ + " Rating: " + rating_ + '\n' +
    to_string(price_) + " " + to_string(qty_) + " left.";
    return res;
}

void Movie::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << 
    "\n" << genre_ << "\n" << rating_ << endl;
}

void Movie::sold(){
    qty_--;
}