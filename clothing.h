#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product{
public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
    ~Clothing();

    //abstract class. Returns the appropriate keywords to index the product
    std::set<std::string> keywords() const;
    //abstract class. Creates a string that contains the product info
    std::string displayString() const;
    //virtual. outputs the database format of the product info
    void dump(std::ostream& os) const;
    void sold();
private:
    std::string size_;
    std::string brand_;
};
#endif