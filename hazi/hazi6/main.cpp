#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <climits>

using namespace std;

class Etel {
protected:
    string nev;
    string leiras;
    unsigned ar;

public:
    Etel() : nev("amint kesz megtudod"), leiras( "ami sikerul"), ar(0) {}

    Etel(const string &nev, const string &leiras, unsigned int ar) : nev(nev), leiras(leiras), ar(ar) {}

    virtual const string get_nev() const {
        return nev;
    }

    const string &get_leiras() const {
        return leiras;
    }

    unsigned int get_ar() const {
        return ar;
    }

    virtual operator unsigned() const {
        return ar;
    }

    virtual unsigned get_type() const {
        return 0;
    }
};

class Menu: public Etel {
protected:
    vector<Etel> etelek;
//    unsigned tarolt = 0;

public:
    Menu() = default;

    Menu(const string &nev, const string &leiras) : Etel(nev, leiras, 0) {}

    Menu(const string &nev, const string &leiras, const Etel elso, const Etel masodik, const Etel harmadik) : Etel(nev, leiras, 0) {
        etelek.push_back(elso);
        etelek.push_back(masodik);
        etelek.push_back(harmadik);
    }

    const string get_nev() const override {
        return "Menu: " + nev;
    }

    operator unsigned() const override {
        unsigned szaml = 0;
        for (auto& etel : etelek) {
            szaml += (unsigned)etel;
        }
        szaml *= 0.9;
        return (unsigned) szaml;
    }

    Etel operator [](unsigned index) const {
        if (index > 2) {
            throw exception();
        } else {
            return etelek[index];
        }
    }

    unsigned get_type() const override {
        return 1;
    }
};

class Vendeglo {
protected:
    vector<reference_wrapper<Etel>> adatok;

public:
    Vendeglo() = default;

    Vendeglo& operator<< (reference_wrapper<Etel> uj) {
        adatok.push_back(uj);
        return *this;
    }

    Etel& operator[] (unsigned index) {
        if (index >= adatok.size()) {
            throw exception();
        } else {
            return adatok[index];
        }
    }

    operator Etel () const {
        if (adatok.empty()) {
            throw exception();
        } else {

            unsigned legkisebb = UINT_MAX;
            Etel legetel;
            for (const auto &elem : adatok) {
                if ( elem.get().get_type() == 0 and elem.get().get_ar() < legkisebb) {
                    cout << elem.get().get_nev() << " " << elem.get().get_type() << " " << elem.get().get_ar() <<endl;
                    legkisebb = elem.get().get_ar();
                    legetel = elem.get();
                }
            }

            if (legkisebb == UINT_MAX) {
                throw exception();
            }

            return legetel;
        }
    }
};

int main() {
    // 1. feladat: Etel osztály tesztelése
//    Etel etel1;  // Default konstruktor
//    Etel etel2("Pizza", "Sonkas-sajtos pizza", 1200);  // Paraméteres konstruktor
//
//    std::cout << "Etel1 neve: " << etel1.get_nev() << ", leirasa: " << etel1.get_leiras() << ", ara: " << (unsigned int)etel1 << "\n";
//    std::cout << "Etel2 neve: " << etel2.get_nev() << ", leirasa: " << etel2.get_leiras() << ", ara: " << (unsigned int)etel2 << "\n";
//
////     2. feladat: Menu osztály tesztelése
//    Etel etel3("Leves", "Zoldsegleves", 600);
//    Etel etel4("Teszta", "Spagetti bolognese", 1500);
//    Menu menu1("Ebedmenu", "3 fogasos ebed", etel2, etel3, etel4);
//
//    std::cout << "Menu neve: " << menu1.get_nev() << "\n";
//    std::cout << "Menu ara: " << (unsigned int)menu1 << "\n";  // 10% kedvezmény
//
//    // 3. feladat: Vendeglo osztály tesztelése
//    Vendeglo vendeglo;
//    vendeglo << etel3 << etel2 << etel4 << menu1;
//
//    try {
//        std::cout << "A vendeglo legolcsobb etele: " << vendeglo.operator Etel().get_nev() << "\n";
//    } catch (const std::exception& e) {
//        std::cout << "Hiba: " << e.what() << "\n";
//    }

    return 0;
}