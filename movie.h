#include "product.h"

class Movie : public Product{
public:
    Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
    ~Movie();

    //abstract class. Returns the appropriate keywords to index the product
    std::set<std::string> keywords() const;
    //abstract class. Creates a string that contains the product info
    std::string displayString() const;
    //virtual. outputs the database format of the product info
    void dump(std::ostream& os) const;
private:
    std::string genre_;
    std::string rating_;
};