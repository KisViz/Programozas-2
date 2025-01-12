#include <iostream>
#include "vector"
#include "map"

using namespace std;

class Uszo {
public:
    string nev;
    explicit Uszo(const string &nev) : nev(nev) {}

    operator string() {
        return nev;
    }
};

class Medence {
public:
    unsigned ido;
    unsigned elerendo;
    map<string, unsigned> uszok;
    map<string, unsigned > beert;


    Medence(unsigned elerendo): elerendo(elerendo), ido(0) {}

    void status() const {
        cout << to_string(ido) + "/" + to_string(elerendo) << endl;

        for (auto& elem : uszok) {
            cout << elem.first + ":" + to_string(elem.second) << endl;
        }
    }

    Medence& operator++() {
        ++ido;
        return *this;
    }

    Medence operator++(int) {
        Medence tmp = *this;
        operator++();
        return tmp;
    }

    Medence& operator+=(string nev) {
        beert[nev] = ido;
        return *this;
    }

    unsigned& operator[](string nev) {
        if (beert.find(nev) == beert.end()) {
            beert[nev] = 666;
        }
        return beert[nev];
    }

    int szintido() const {
        int szaml = 0;
        for(auto& ekem : uszok) {
            if (ekem.second > elerendo) {
                szaml++;
            }
        }

        return szaml;
    }

    operator Uszo() const {
        
    }
};

/*int main() {
    return 0;
}*/
