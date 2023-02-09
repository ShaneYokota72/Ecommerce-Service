#include "book.h"
#include <iomanip>
using namespace std;

//BOOK:the words in the author’s name should be searchable keywords as well as the book’s ISBN number
Book::Book(const std::string category, const std::string name, double price, int qty, string isbn, string author) : Product(category, name, price, qty)
{
    isbn_ = isbn;
    author_ = author;
}
Book::~Book(){ };

std::set<std::string> Book::keywords() const{
    set<string> result;
    result.insert(getName());
    result.insert(author_);
    result.insert(isbn_);
    return result;
}

std::string Book::displayString() const{
    /* 
    <name>
    Author: <author> ISBN: <isbn>
    <price> <quantity> left. 
    */

    string res = "";
    res = res + name_ + '\n' +
    "Author: " + author_ + " ISBN: " + isbn_ + '\n' +
    to_string(price_) + " " + to_string(qty_) + " left.";
    return res;
}

void Book::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << 
    "\n" << isbn_ << "\n" << author_ << endl;
}

void Book::sold(){
    qty_--;
}