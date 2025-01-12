#include <string>
#include <iostream>
#include <vector>
using namespace std;


class Verseny {
protected:
    string nev;
public:
    Verseny(const string& n) : nev(n) { }

    virtual ~Verseny() = default;

    virtual string leiras() const {
        return nev;
    }

    virtual Verseny* clone() {
        return new Verseny(*this);
    }

    virtual unsigned tipus() const {
        return 0;
    }

    virtual unsigned tav() const {
        return 0;
    }
};

class FutoVerseny : public Verseny {
    unsigned tavolsag;

public:
    FutoVerseny(const string& nev, unsigned tav) : Verseny(nev), tavolsag(tav) { }

    unsigned getTavolsag() const noexcept {
        return tavolsag;
    }

    string leiras() const override {
        return nev + " - " + to_string(tavolsag);
    }

    ~FutoVerseny() override = default;

    FutoVerseny *clone() override {
        return new FutoVerseny(*this);
    }

    unsigned int tipus() const override {
        return 1;
    }

    unsigned int tav() const override {
        return tavolsag;
    }
};

class HegymaszoVerseny : public Verseny {
    string hegy;

public:
    HegymaszoVerseny(const string& nev, const string& hegy) : Verseny(nev), hegy(hegy) { }

    string leiras() const override {
        return nev + " - " + hegy;
    }

    ~HegymaszoVerseny() override = default;

    HegymaszoVerseny *clone() override {
        return new HegymaszoVerseny(*this);
    }

    unsigned int tipus() const override {
        return 2;
    }

    unsigned int tav() const override {
        return 0;
    }
};

class Versenyek {
public:
    vector<Verseny*> versenyek;

    Versenyek() = default;

    virtual ~Versenyek() {
        for (auto& elem : versenyek) {
            delete elem;
        }

        versenyek.clear();
    }

    Versenyek(const Versenyek& other) {
        for (auto& elem : other.versenyek) {
            this->versenyek.push_back(elem->clone());
        }
    }

    Versenyek& operator= (const Versenyek& other) {
        if (&other == this) {
            return *this;
        }

        for (auto& elem : versenyek) {
            delete elem;
        }

        versenyek.clear();

        for (auto& elem : other.versenyek) {
            this->versenyek.push_back(elem->clone());
        }

        return *this;
    }

    virtual Versenyek& operator<< (Verseny* uj) {
        this->versenyek.push_back(uj->clone());
        return *this;
    }

    void kiir() const {
        for (auto& elem : versenyek) {
            cout << elem->leiras() << endl;
        }
    }
};

class UltraFutoVersenyek: public Versenyek {

public:
    UltraFutoVersenyek() = default;

    UltraFutoVersenyek &operator<<(Verseny *uj) override {
        if (uj->tipus() == 1 && uj->tav() >= 42) {
            this->versenyek.push_back(uj->clone());
        }
        return *this;
    }

    UltraFutoVersenyek &operator<<(Versenyek& versenyek) {
        for (auto& uj : versenyek.versenyek) {
            if (uj->tipus() == 1 && uj->tav() >= 42) {
                this->versenyek.push_back(uj->clone());
            }
        }

        return *this;
    }
};

#ifndef TEST_BIRO

/*int main() {
    Verseny* ub = new FutoVerseny("Ultra Balaton", 211);
    cout << ub->leiras() << endl;
    // Ultra Balaton - 211

    FutoVerseny* szegedm = new FutoVerseny("Szeged Maraton", 42);
    HegymaszoVerseny* kekes = new HegymaszoVerseny("Kekes Maszas", "Kekes");

    Versenyek v;
    v << ub << szegedm << kekes;
    v.kiir();
    // Ultra Balaton - 211
    // Szeged Maraton - 42
    // Kekes Maszas - Kekes

    {
      Versenyek v2(v);
      v2.kiir();
      // Ultra Balaton - 211
      // Szeged Maraton - 42
      // Kekes Maszas - Kekes
    }

    UltraFutoVersenyek ufv;
    ufv << new FutoVerseny("Szegedi Esti Kocogas", 10)
        << new FutoVerseny("Szeged-Budapest", 192)
        << new HegymaszoVerseny("Magas Tatra", "Tatra");
    // ketto objektum nem lesz felszabaditva, de ez most nem gond ...
    ufv.kiir();
    // Szeged-Budapest - 192

    ufv << v;
    ufv.kiir();
    // Ultra Balaton - 211
    // Szeged Maraton - 42
}*/

#endif
