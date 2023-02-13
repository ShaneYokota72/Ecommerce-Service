#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "datastore.h"
#include <queue>
#include <map>
#include <deque>
#include "user.h"
#include "product.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    // DataStore ds;
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    map<string, deque<Product*>*> usercarts;
    
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            } else if (cmd == "ADD"){/* Add support for other commands here */
                //username search_hit_number
                string username = "";
                string search_hit_number = "";

                ss >> username >> search_hit_number;
                if(ss.fail()){
                    cout << "Invalid request" << endl;
                }
                if(stoi(search_hit_number)-1 >= hits.size() || stoi(search_hit_number)-1 < 0){
                    cout << "Invalid request" << endl;
                }
                //find user
                /* vector<User*>::iterator it = (ds.uservector).find(username); */
                bool userexist = false;
                for(unsigned int i=0; i<(ds.uservector).size(); i++){
                    if(((ds.uservector).at(i))->getName() == username){
                        userexist = true;
                        break;
                    }
                }
                if(userexist){
                    //there's a user
                    map<string, deque<Product*>*>::iterator it2 = usercarts.find(username);
                    if(it2 != usercarts.end()){
                        //this user already has a cart
                        (it2->second)->push_back(hits.at(stoi(search_hit_number)-1));
                    } else {
                        //this user does not have a cart
                        deque<Product*>* user_cart = new deque<Product*>();
                        
                        user_cart->push_back(hits.at(stoi(search_hit_number)-1));
                        usercarts.insert(make_pair(username, user_cart));
                    }
                } else {
                    cout << "Invalid request" << endl;
                }

            } else if (cmd == "VIEWCART"){
                //username 
                string username = "";
                ss >> username;
                if(ss.fail()){cout << "Invalid request" << endl;}

                //find if the user exists
                bool userexist = false;
                for(unsigned int i=0; i<(ds.uservector).size(); i++){
                    if(((ds.uservector).at(i))->getName() == username){
                        userexist = true;
                        break;
                    }
                }
                if(userexist){
                    //view cart
                    map<string, deque<Product*>*>::iterator it2 = usercarts.find(username);
                    if(it2 != usercarts.end()){
                        //*(it2->second); //the deque itself
                        //          vector<Product*> convert;
                        //this user already has a cart
                        for(unsigned int i=0; i<(it2->second)->size(); i++){
                            //            convert.push_back((it2->second)->at(i));
                            cout << "Item " << i+1 << endl;
                            cout << ((it2->second)->at(i))->displayString() << endl;
                        }
                        //         displayProducts(convert);
                    } else {
                        //this person does not have a cart
                        cout << "empty cart" << endl;
                    }
                } else {
                    //this user does not exist
                    cout << "End of file encountered while searching for invalid username message" << endl;
                }
            } else if (cmd == "BUYCART"){
                //username 
                string username = "";
                ss >> username;
                if(ss.fail()){cout << "Invalid request" << endl;}
                
                //find user. If there's user, save the pointer that user
                bool userexist = false;
                User* userptr;
                for(unsigned int i=0; i<(ds.uservector).size(); i++){
                    if(((ds.uservector).at(i))->getName() == username){
                        userexist = true;
                        userptr = (ds.uservector).at(i);
                        break;
                    }
                }
                if(userexist){
                    //Buy cart
                    map<string, deque<Product*>*>::iterator it2 = usercarts.find(username);
                    if(it2 != usercarts.end()){
                        //cart exists
                        // buy all the item as long as the funds are enough
                        while(((*userptr).getBalance() >= (it2->second)->at(0)->getPrice()) && ((it2->second)->at(0)->getQty()>=1)){
                            userptr->deductAmount((it2->second)->at(0)->getPrice());
                            (it2->second)->at(0)->sold();
                            (it2->second)->pop_front();
                            if((it2->second)->size() == 0){
                                break;
                            }
                        }
                    }
                } else {
                    // error msg(user does not exist)
                    cout << "End of file encountered while searching for invalid username message" << endl;
                }
            } else {
                cout << "Unknown command" << endl;
            }
        }

    }

    // deleting the dynamically allocated deques
    map<string, deque<Product*>*>::iterator it;
    for(it = usercarts.begin(); it != usercarts.end(); ++it){
        delete (it->second);
    }

    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
