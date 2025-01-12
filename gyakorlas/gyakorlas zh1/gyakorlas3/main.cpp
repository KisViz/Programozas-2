#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <map>
#include "set"

using namespace std;



class Hiba : public exception{
    string msg;
public:
    Hiba(unsigned szam) {
        if (szam > 50) {
            msg = "Sulyos hiba tortent";
        } else if (szam > 25) {
            msg = "Komoly hiba tortent";
        } else {
            msg = "Kis hiba tortent";
        }
    }

    const char * what() const noexcept override {
        return msg.c_str();
    }
};

// 1. Feladat
bool osztalytKeres(const map<string, unsigned>& osztalyok, const string& keresettOsztaly) {

    for (auto& elem : osztalyok) {
        if (elem.second > 20) {
            throw Hiba(elem.second);
        }
    }

    for (auto & elem : osztalyok) {
        if (elem.first == keresettOsztaly && elem.second > 10) {
            return true;
        }
    }
    // megoldas
    return false; // ezt a sort modosithatod
}


// 2. Feladat
unsigned atlagalatt(const vector<int>& vektor){

    int szaml = 0;
    for (auto& elem : vektor) {
        szaml += elem;
    }

    double atlag = szaml/vektor.size();

    szaml = 0;
    for (auto& elem : vektor) {
        if (elem <= atlag) {
            szaml++;
        }
    }
    // megoldas
    return szaml; // ezt a sort modosithatod
}


struct Renszarvas {
    unsigned sebesseg;
    Renszarvas(unsigned sebesseg = 0): sebesseg(sebesseg) {}
    // 3.feladat

    bool operator<(const Renszarvas& renszarvas) const {
        return this->sebesseg < renszarvas.sebesseg;
    }
};


// 4. Feladat
vector<Renszarvas> egyedieketRendez(const vector<Renszarvas>& tomb){
    // megoldas
    set<unsigned> szamok;

    for (auto& elem : tomb) {
        szamok.insert(elem.sebesseg);
    }

    vector<Renszarvas> szarvasok;
    for (auto it = szamok.rbegin(); it != szamok.rend(); ++it) {
        szarvasok.push_back(*it);
    }

    return szarvasok;
}


int main(){

    map<string, unsigned> osztalyok = { {"9a", 8}, {"9b", 19}, {"7a", 11}};
    assert(osztalytKeres(osztalyok, "7a"));

    unsigned db = atlagalatt({2,3,4,5,1,4,5,1,2,3,4,5,1}); //atlag: 3.08
    assert(db == 7);

    Renszarvas sz1(5), sz2(10);
    //assert(sz1 < sz2);

    vector<Renszarvas> szrok = {2, 5, 5, 0, 2, 3}; //implicit konverzio renszarvasra
    vector<Renszarvas> rendezett = egyedieketRendez(szrok);
    vector<Renszarvas> elvart = {5, 3, 2, 0}; //implicit konverzio renszarvasra
    for(unsigned i =0;i<elvart.size();++i){
//        cout << rendezett[i].sebesseg << endl;
        assert(elvart[i].sebesseg == rendezett[i].sebesseg);
    }
    cout << endl;
    return 0;
}