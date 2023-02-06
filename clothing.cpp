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
    string res;
    res = res + "Category: " + category_ + " Name: " +  name_ + " Price: " +  price_ + " Quantity: " +  qty_ + " Size: " + size_ + " Brand: " +  brand_;
    return res;
}

void Clothing::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << 
    "\n" << size_ << "\n" << brand_ << endl;
}