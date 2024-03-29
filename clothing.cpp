#include "clothing.h"
#include "util.h"
#include <iomanip>
using namespace std;

//CLOTHES:the words in the brand should be searchable keywords
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, string size, string brand) : Product(category, name, price, qty)
{
    size_ = size;
    brand_ = brand;
}
Clothing::~Clothing(){ };

std::set<std::string> Clothing::keywords() const{
    //add the keyword for this product
    set<string> result;
    set<string> brandset = parseStringToWords(convToLower(brand_));
    result.insert(brandset.begin(), brandset.end());
    return result;
}

std::string Clothing::displayString() const{
    //display the output in a string
    string res = "";
    res = res + name_ + '\n' +
    "Size: " + size_ + " Brand: " + brand_ + '\n' +
    to_string(price_) + " " + to_string(qty_) + " left.";
    return res;
}

void Clothing::dump(std::ostream& os) const{
    //dump following the format
    os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << 
    "\n" << size_ << "\n" << brand_ << endl;
}

void Clothing::sold(){
    qty_--;
}