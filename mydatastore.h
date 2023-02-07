#include "datastore.h"
#include "util.h"
#include "product.h"



// / implement the core functionality of your program: searching, adding products and users, saving the database, etc. 
//where you should store products and users in some fashion
class MyDataStore: public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    /**
     *  Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);
   
    
/* private:
 */
//product
    std::vector<Product*> productvector;
//users
    std::vector<User*> uservector;
};