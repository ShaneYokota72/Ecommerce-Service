#include "mydatastore.h"
#include "util.h"
#include <set>

using namespace std;

MyDataStore::MyDataStore(){ }

MyDataStore::~MyDataStore() { }

void MyDataStore::addProduct(Product* p){
    productvector.push_back(p);
}
void MyDataStore::addUser(User* u){
    uservector.push_back(u);
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    /* vector<Product*> result; */
    set<Product*> resultset;
    if(type == 0){
        //intersection
        for(unsigned int i=0; i<productvector.size(); i++){
            set<string> productword = parseStringToWords((*productvector.at(i)).getName());
            bool match = true;            
            for(unsigned int j=0; j<terms.size(); j++){
                set<string>::iterator it = productword.find(terms.at(i));
                if(it == productword.end()){
                    match = false;
                }/* 
                set<string> match = setIntersection<string>(parseStringToWords((*productvector.at(i)).getName()), parseStringToWords(terms.at(i)));
                if(match.size()>0){
                    resultset.insert(productvector.at(i));
                } */
            }
            if(match){
                resultset.insert(productvector.at(i));
            }
        }
        /* resultset = setIntersection<Product*>(productvector, terms);
        vector<Product*> result(resultset.size());
        std::copy(resultset.begin(), resultset.end(), result.begin()); */
    } else {
        // union
        for(unsigned int i=0; i<productvector.size(); i++){
            set<string> productword = parseStringToWords((*productvector.at(i)).getName());
            bool match = false;            
            for(unsigned int j=0; j<terms.size(); j++){
                set<string>::iterator it = productword.find(terms.at(i));
                if(it != productword.end()){
                    match = true;
                }/* 
                set<string> match = setIntersection<string>(parseStringToWords((*productvector.at(i)).getName()), parseStringToWords(terms.at(i)));
                if(match.size()>0){
                    resultset.insert(productvector.at(i));
                } */
            }
            if(match){
                resultset.insert(productvector.at(i));
            }
        }
    }
    vector<Product*> ans(resultset.begin(), resultset.end());
    return ans;
}
void MyDataStore::dump(std::ostream& ofile){
    for(unsigned int i=0; i<productvector.size(); i++){
        (productvector.at(i))->dump(ofile);
    }
    for(unsigned int i=0; i<uservector.size(); i++){
        (uservector.at(i))->dump(ofile);
    }
}