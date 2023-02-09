#include "mydatastore.h"
#include "util.h"
#include <set>

using namespace std;

MyDataStore::MyDataStore(){ }

MyDataStore::~MyDataStore() {
    //deleting the dynamically allocated datas
    for(unsigned int i=0; i<productvector.size(); i++){
        delete productvector.at(i);
    }
    for(unsigned int i=0; i<uservector.size(); i++){
        delete uservector.at(i);
    }
}

void MyDataStore::addProduct(Product* p){
    //add the product to the vector
    productvector.push_back(p);
}
void MyDataStore::addUser(User* u){
    //add the user to the vector
    uservector.push_back(u);
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    set<Product*> left;
    set<Product*> right;
    //put the thing in the left and right

    //edgecase, when theres only one serach term
    if(terms.size() == 1){
        for(unsigned int i=0; i<productvector.size(); i++){
            set<string> productwords = parseStringToWords(convToLower((*productvector.at(i)).getName()));
            set<string> productwordsaddition = (*productvector.at(i)).keywords();
            productwords.insert(productwordsaddition.begin(), productwordsaddition.end());

            set<string>::iterator it = productwords.find(terms.at(0));
            if(it != productwords.end()){
                left.insert(productvector.at(i));
            }
        }
    } else {//when the search term are 2 or above
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

    //translate set to vector
    vector<Product*> ans;
    ans.assign(left.begin(), left.end());
    return ans;
}
void MyDataStore::dump(std::ostream& ofile){
    //dump following the format
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