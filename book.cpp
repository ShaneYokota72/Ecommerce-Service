#include "book.h"

using namespace std;

//BOOK:the words in the author’s name should be searchable keywords as well as the book’s ISBN number
Book::Book(category, name, price, qty, isbn, author) : Product(category, name, price, qty)
{
    isbn_ = isbn;
    author_ = author;
}
Book::~Book();

std::set<std::string> Book::keywords() const{
    set<string> result;
    result.insert(getName());
    result.insert(author_);
    return result;
}

std::string Book::displayString() const{
    string res;
    res = res + "Category: " + category_ + " Name: " +  name_ + " Price: " +  price_ + " Quantity: " +  qty_ + " ISBN: " + isbn_ + " Author: " +  author_;
    return res;
}

void Book::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << 
    "\n" << isbn_ << "\n" << author_ << endl;
}