#include "mydatastore.h"
#include "util.h"
#include <set>

using namespace std;

MyDataStore::MyDataStore(){ }

MyDataStore::~MyDataStore() {
    for(unsigned int i=0; i<productvector.size(); i++){
        delete [] productvector.at(i);
    }
    for(unsigned int i=0; i<uservector.size(); i++){
        delete [] uservector.at(i);
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
    set<Product*> set1;
    set<Product*> set2;
    // cout << "productvec size" << productvector.size() << endl;
    // cout << "termtvec size" << terms.size() << endl;
    for(unsigned int i=0; i<productvector.size(); i++){
        set<string> productwords = parseStringToWords(convToLower((*productvector.at(i)).getName()));
        set<string> productwordsaddition = (*productvector.at(i)).keywords();
        productwords.insert(productwordsaddition.begin(), productwordsaddition.end());

        /* for(auto str:productwords){
            cout << "Product separated:" << str << endl;
        }
        cout << endl;
        for(auto wor:terms){
            cout << "Terms separated: " << wor << endl;
        }
        cout << endl << endl; */

        set<string>::iterator it = productwords.find(terms.at(0));
        if(it != productwords.end()){
            set1.insert(productvector.at(i));
            // cout << "set1 inserted at " << i << endl;
        }
        set<string>::iterator it2 = productwords.find(terms.at(1));
        if(it2 != productwords.end()){
            set2.insert(productvector.at(i));
            // cout << "set2 inserted at " << i << endl;
        }
    }
    set<Product*> result;
    if(type == 0){
        //intersection
        result = setIntersection(set1, set2);
    } else {
        //union
        result = setUnion(set1, set2);
    }


    /* //compare the 1st and 2nd sets and come out with the result vector
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
                }
            }
            if(match){
                resultset.insert(productvector.at(i));
            }
        }
    } else {
        // union
        for(unsigned int i=0; i<productvector.size(); i++){
            set<string> productword = parseStringToWords((*productvector.at(i)).getName());
            bool match = false;            
            for(unsigned int j=0; j<terms.size(); j++){
                set<string>::iterator it = productword.find(terms.at(i));
                if(it != productword.end()){
                    match = true;
                }
            }
            if(match){
                resultset.insert(productvector.at(i));
            }
        }
    } */

    vector<Product*> ans;
    ans.assign(result.begin(), result.end());
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