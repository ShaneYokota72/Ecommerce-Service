#include "book.h"
#include "util.h"
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
    //add the keyword for this product
    set<string> result;
    set<string> authorset = parseStringToWords(convToLower(author_));
    result.insert(authorset.begin(), authorset.end());
    result.insert(isbn_);
    return result;
}

std::string Book::displayString() const{
    //display the output in a string
    string res = "";
    res = res + name_ + '\n' +
    "Author: " + author_ + " ISBN: " + isbn_ + '\n' +
    to_string(price_) + " " + to_string(qty_) + " left.";
    return res;
}

void Book::dump(std::ostream& os) const{
    //dump following the format
    Product::dump(os);
    os << isbn_ << endl;
    os << author_ << endl;
}

void Book::sold(){
    qty_--;
}