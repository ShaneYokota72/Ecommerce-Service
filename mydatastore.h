#include "datastor.h"
#include "util.h"



// / implement the core functionality of your program: searching, adding products and users, saving the database, etc. 
//where you should store products and users in some fashion
class MyDataStore: public DataStore {
    
    ~MyDataStore() { }

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) = 0;

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) = 0;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) = 0;

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile) = 0;

}