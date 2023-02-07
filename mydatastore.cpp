#include "mydatastore.h"

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
    vector<Product*> result;
    if(type = 0){
        //intersection
        result = setIntersection(productvector, terms);
    } else {
        // union
        result = setUnion(productvector, terms);
    }
    return result;
}
void MyDataStore::dump(std::ostream& ofile){
    for(int i=0; i<productvector.length(); i++){
        (*productvector.at(i)).dump();
    }
    for(int i=0; i<uservector.length(); i++){
        (*uservector.at(i)).dump();
    }
}