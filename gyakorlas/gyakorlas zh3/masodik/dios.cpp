#include <iostream>
#include "vector"
using namespace std;


class Sikidom {
    const string tipus;
public:
    virtual ~Sikidom() = default;

    Sikidom(const string& tipus) : tipus(tipus){}
    virtual unsigned kerulet() const = 0;

    string keruletToString() const {
        return "A " + tipus + " kerulete " + to_string(kerulet()) + " egyseg.";
    }

    virtual Sikidom& novel () = 0;

    virtual Sikidom* clone() = 0;

    virtual const string &getTipus() const {
        return tipus;
    }
};

class Teglalap: public Sikidom {
public:
    unsigned a, b;

    Teglalap(unsigned int a, unsigned int b, const string& tipus = "teglalap") : Sikidom("teglalap"), a(a), b(b) {}

    virtual ~Teglalap() = default;

    unsigned int kerulet() const override {
        return 2 * a * b;
    }

    Teglalap *clone() override {
        return new Teglalap(*this);
    }

    Teglalap& novel() override {
        a++;
        b++;
        return *this;
    }

    const string &getTipus() const override {
        return Sikidom::getTipus();
    }
};

class Negyzet: public Teglalap {
public:
    Negyzet(unsigned a, const string& tipus = "negyzet") : Teglalap(a,a, tipus) {}

    virtual ~Negyzet() = default;

    unsigned int kerulet() const override {
        return 4 * a;
    }

    Negyzet *clone() override {
        return new Negyzet(*this);
    }

    Negyzet &novel() override {
        a++;
        return *this;
    }

    const string &getTipus() const override {
        return Teglalap::getTipus();
    }
};

class Haromszog: public Sikidom {
public:
    unsigned a, b, c;

    Haromszog(unsigned int a, unsigned int b, unsigned int c, const string &tipus = "harmoszog") : Sikidom(tipus), a(a), b(b), c(c) {}

    virtual ~Haromszog() = default;

    unsigned int kerulet() const override {
        return a + b + c;
    }

    Sikidom *clone() override {
        return new Haromszog(*this);
    }

    Haromszog &novel() override {
        a++;
        b++;
        c++;
        return *this;
    }

    const string &getTipus() const override {
        return Sikidom::getTipus();
    }
};

class Rajz {
public:
    vector<Sikidom*> sikidomok;

    ~Rajz() {
        for (auto& elem : sikidomok) {
            delete elem;
        }

        sikidomok.clear();
    }

    Rajz() = default;

    Rajz(const Rajz& other) {
        for (auto& elem : other.sikidomok) {
            this->sikidomok.push_back(elem->clone());
        }
    }

    Rajz& operator= (const Rajz& other) {
        if (this == &other) {
            return *this;
        }

        for (auto& elem : sikidomok) {
            delete elem;
        }

        sikidomok.clear();

        for (auto& elem: other.sikidomok) {
            if (elem->getTipus() == "teglalap") {
                this->sikidomok.push_back(elem->clone());
            }
        }

        return *this;
    }

    Rajz& operator<< (Sikidom* uj) {
        sikidomok.push_back(uj->clone());

        return *this;
    }

    friend ostream &operator<<(ostream &os, const Rajz &rajz) {
        for (auto& elem : rajz.sikidomok) {
            os << elem->kerulet() << endl;
        }
        return os;
    }

    Rajz operator++ (int) {
        Rajz* tmp = this;
        for (auto& elem : sikidomok) {
            cout << elem->getTipus() << endl;
            elem->novel();
        }

        return *tmp;
    }
};

/*
int main() {
     //Beugro feladat
    Teglalap t(3,4);
    Negyzet n(5);
    Haromszog h(3,4,5);

//    cout << t.keruletToString() << endl;

    //Rajz osztalytol
    Rajz rajz;

    //hozzaadas
    rajz << &t << &h;

    //kiiratas
    cout << "-------------" << endl;
    cout << "rajz" << endl << rajz;
    cout << "-------------" << endl << endl;

    cout << "-------------" << endl;
    //++ operator
    cout << "++ operator" << endl;
    rajz++;
//    cout << "kiir" << endl;
//    cout << h.kerulet() << endl;
    cout << "kiir" << endl;
    cout << rajz;
    cout << "-------------" << endl << endl;

    //Copy konstruktor
    cout << "Copy" <<endl;
    Rajz rajz2 = rajz;
    cout << rajz2;

    //Ertekado operator
    cout << "ertek" << endl;
    rajz=rajz2;
    cout << rajz << endl;

    return 0;
}
*/
