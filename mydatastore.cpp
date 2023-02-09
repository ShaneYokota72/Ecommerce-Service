#include "mydatastore.h"
#include "util.h"
#include <set>

using namespace std;

MyDataStore::MyDataStore(){ }

MyDataStore::~MyDataStore() {
    for(unsigned int i=0; i<productvector.size(); i++){
        delete productvector.at(i);
    }
    for(unsigned int i=0; i<uservector.size(); i++){
        delete uservector.at(i);
    }
}

void MyDataStore::addProduct(Product* p){
    productvector.push_back(p);
}
void MyDataStore::addUser(User* u){
    uservector.push_back(u);
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    // get a set for the 1st term
    //get a set for 2nd term
    /* if(terms.size() == 0){
        vector<Product*> empty;
        return empty;
    } */
    // set<Product*> set1;
    // set<Product*> set2;
    // for(unsigned int i=0; i<productvector.size(); i++){
    //     set<string> productwords = parseStringToWords(convToLower((*productvector.at(i)).getName()));
    //     set<string> productwordsaddition = (*productvector.at(i)).keywords();
    //     productwords.insert(productwordsaddition.begin(), productwordsaddition.end());

    //     /* for(auto str:productwords){
    //         cout << "Product separated:" << str << endl;
    //     }
    //     cout << endl;
    //     for(auto wor:terms){
    //         cout << "Terms separated: " << wor << endl;
    //     }
    //     cout << endl << endl; */

    //     if(terms.size()>0){
    //         set<string>::iterator it = productwords.find(terms.at(0));
    //         if(it != productwords.end()){
    //             set1.insert(productvector.at(i));
    //             // cout << "set1 inserted at " << i << endl;
    //         }
    //     }
    //     if(terms.size()>1){
    //         set<string>::iterator it2 = productwords.find(terms.at(1));
    //         if(it2 != productwords.end()){
    //             set2.insert(productvector.at(i));
    //             // cout << "set2 inserted at " << i << endl;
    //         }
    //     }
        
    // }

    /* set<Product*> result;
    if(type == 0){
        //intersection
        result = setIntersection(left ,right);
    } else {
        //union
        result = setUnion(left, right);
    } */
    set<Product*> left;
    set<Product*> right;
    //put the thing in the left and right
    if(terms.size() == 1){
        for(unsigned int i=0; i<productvector.size(); i++){{
            set<string> productwords = parseStringToWords(convToLower((*productvector.at(i)).getName()));
            set<string> productwordsaddition = (*productvector.at(i)).keywords();
            productwords.insert(productwordsaddition.begin(), productwordsaddition.end());

            set<string>::iterator it = productwords.find(terms.at(0));
            if(it != productwords.end()){
                left.insert(productvector.at(i));
            }
        }
    } else {
        for(unsigned int j = 0; j<terms.size()-1; j++){
            for(unsigned int i=0; i<productvector.size(); i++){
                set<string> productwords = parseStringToWords(convToLower((*productvector.at(i)).getName()));
                set<string> productwordsaddition = (*productvector.at(i)).keywords();
                productwords.insert(productwordsaddition.begin(), productwordsaddition.end());
                
                set<string>::iterator it = productwords.find(terms.at(j));
                if(it != productwords.end()){
                    left.insert(productvector.at(i));
                }
                set<string>::iterator it2 = productwords.find(terms.at(j+1));
                if(it2 != productwords.end()){
                    right.insert(productvector.at(i));
                }
            }
            if(type == 0){
                left = setIntersection(left, right);
                right.clear();
            } else {
                left = setUnion(left, right);
                right.clear();
            }
        }
    }

    vector<Product*> ans;
    ans.assign(left.begin(), left.end());
    return ans;
}
void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>\n";
    for(unsigned int i=0; i<productvector.size(); i++){
        (productvector.at(i))->dump(ofile);
    }
    ofile << "</products>\n<users>\n";
    for(unsigned int i=0; i<uservector.size(); i++){
        (uservector.at(i))->dump(ofile);
    }
    ofile << "</users>";
}