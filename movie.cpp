#include "movie.h"

using namespace std;

//MOVIE:the movie’s genre should be a searchable keyword
Movie::Movie(category, name, price, qty, genre, rating) : Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}
Movie::~Movie();

std::set<std::string> Movie::keywords() const{
    set<string> result;
    result.insert(getName());
    result.insert(genre_);
    return result;
}

std::string Movie::displayString() const{
    string res;
    res = res + "Category: " + category_ + " Name: " +  name_ + " Price: " +  price_ + " Quantity: " +  qty_ + " Genre: " + genre_ + " rating: " +  rating_;
    return res;
}

void Movie::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << 
    "\n" << genre_ << "\n" << rating_ << endl;
}