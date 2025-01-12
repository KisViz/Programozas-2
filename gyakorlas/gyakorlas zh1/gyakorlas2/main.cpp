#include <iostream>
#include "vector"

using namespace std;

class Allat {
    string nev;
    unsigned jollakva;

public:

    Allat(const string &nev, unsigned int jollakva = 10) : nev(nev), jollakva(jollakva) {}

    Allat(): nev("allat"), jollakva(10) {}

    const string &get_nev() const {
        return nev;
    }

    unsigned int get_jollakva() const {
        return jollakva;
    }

    unsigned operator!() {
        return jollakva;
    }

    Allat& operator--() {
        --jollakva;
        return *this;
    }
};

class Allatkert {
    vector<Allat> allatok;
    unsigned maxdb;

public:

    Allatkert(unsigned hany = 5): maxdb(hany > 10 ? 10 : hany) {}

    Allatkert& operator+=(const Allat& allat) {
        if (allatok.size() < maxdb) {
            allatok.push_back(allat);
        } else {
            cout << "Az allatkert tele van" << endl;
        }
        return *this;
    }

    Allat& operator[](int index) {
        try {
            allatok.at(index);
        } catch (exception) {
            throw out_of_range("Rossz index");
        }

        return allatok[index];
    }

    int operator-() {
        int szaml = 0;
        for (auto& allat : allatok) {
            --allat;
            if (allat.get_jollakva() == 0) {
                szaml++;
            }
        }

        return szaml;
    }
};

int main() {
//    Allatkert allatkert(5);
//    allatkert[1];

    return 0;
};