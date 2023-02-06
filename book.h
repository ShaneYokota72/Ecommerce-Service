#include "book.h"

class Book : public Product{
public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author);
    ~Book();

    //abstract class. Returns the appropriate keywords to index the product
    std::set<std::string> keywords() const;
    //abstract class. Creates a string that contains the product info
    std::string displayString() const;
    //virtual. outputs the database format of the product info
    void dump(std::ostream& os) const;
private:
    std::string isbn_;
    std::string author_;
}