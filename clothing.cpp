#include "clothing.h"

using namespace std;

//CLOTHES:the words in the brand should be searchable keywords
Clothing::Clothing(category, name, price, qty, size, brand) : Product(category, name, price, qty)
{
    size_ = size;
    brand_ = brand;
}
Clothing::~Clothing();

std::set<std::string> Clothing::keywords() const{
    set<string> result;
    result.insert(getName());
    result.insert(brand_);
    return result;
}

std::string Clothing::displayString() const{
    /* 
    <name>
    Size: <size> Brand: <brand>
    <price> <quantity> left.
    */
    string res;
    res = res = name_ + '\n' +
    "Size: " + size_ + " Brand: " + brand_ + '\n' +
    price_ + " " + quantity_ + " left.";
    return res;
}

void Clothing::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << 
    "\n" << size_ << "\n" << brand_ << endl;
}