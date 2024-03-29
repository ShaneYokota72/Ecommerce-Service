#include "mydatastore.h"
#include "util.h"
#include <set>
#include <map>

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
    map<string, set<Product*>*>::iterator it;
    for(it = keytoproduct.begin(); it!= keytoproduct.end(); ++it){
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p){
    //add the product to the vector
    productvector.push_back(p);

    set<string> productkeywords = parseStringToWords(convToLower(p->getName()));
    set<string> additional = p->keywords();
    productkeywords.insert(additional.begin(), additional.end());

    set<string>::iterator it;
    for(it = productkeywords.begin(); it!=productkeywords.end(); ++it){
        map<string, set<Product*>*>::iterator it2 = keytoproduct.find(*it);
        if(it2 == keytoproduct.end()){
            //this keyword doesnt exist
            set<Product*>* temp = new set<Product*>;
            temp->insert(p);
            keytoproduct.insert(make_pair(*it, temp));
        } else{
            //this keyword is alerady matched with something else
            (it2->second)->insert(p);
        }
    }
}
void MyDataStore::addUser(User* u){
    //add the user to the vector
    uservector.push_back(u);
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    set<Product*> left;
    set<Product*> right;

    //print out the process
    /* map<string, set<Product*>*>::iterator print;
    for(print = keytoproduct.begin(); print!= keytoproduct.end(); ++print){
        cout << print->first << endl;
        set<Product*>::iterator it;
        for(it = (print->second)->begin(); it != (print->second)->end(); ++it){
            cout << '\t' << (*it)->getName() << endl;;
        }
        
    } */

    if(terms.size() == 1){
        map<string, set<Product*>*>::iterator it = keytoproduct.find(terms.at(0));
        left = *(it->second);
    } else {
        for(int i=0; i<terms.size()-1; i++){
            map<string, set<Product*>*>::iterator it = keytoproduct.find(terms.at(i));
            map<string, set<Product*>*>::iterator it2 = keytoproduct.find(terms.at(i+1));

            if(it != keytoproduct.end() && i == 0){
                left = *(it->second);//is a set of <product*>
            }
            if(it2 != keytoproduct.end()){
                right = *(it2->second);//is a set of <product*>
            }
            if(type == 0){
                left = setIntersection(left, right);
                right.clear();
            } else {
                left = setUnion(left, right);
                right.clear();
            }

            //print out the set after union/intersection
            /* //print left
            set<Product*>::iterator check;
            cout << endl << "AFTER LEFT AND RIGHT CONVERSION" << endl;
            for(check = left.begin(); check!= left.end(); ++check){
                cout << (*check)->getName() << endl;
            }
            cout << endl; */
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