#include <iostream>
#include <vector>
#include "set"

using namespace std;

class Gyerek {
    int boldogsag = 0;
    string nev = "gyerek";
public:
    Gyerek() = default;

    ~Gyerek() = default;

    Gyerek(const string& n) : nev(n) { }

    int getBoldogsag() const {
        return boldogsag;
    }

    Gyerek& setBoldogsag( int b ) {
        boldogsag = b;
        return *this;
    }

    const string& getNev() const {
        return nev;
    }
};


class Ajandek {
protected:
    string uzenet;
public:
    Ajandek(const string& u) : uzenet(u) { }

    virtual ~Ajandek() = default;

    virtual void ajandekoz(Gyerek& gy) const {
        cout << uzenet << endl;
    }

    virtual Ajandek* clone() const = 0;
};

class Vonat : public Ajandek {
    int boldogsag;
public:
    Vonat(const string& u, unsigned b) : Ajandek(u), boldogsag(b) { }

    void ajandekoz(Gyerek &gy) const override {
        cout << uzenet << endl;
        gy.setBoldogsag(boldogsag);
    }

    Vonat *clone() const override {
        return new Vonat(*this);
    }
};

class Virgacs : public Ajandek {
public:
    Virgacs() : Ajandek("jaj") { }

    void ajandekoz(Gyerek &gy) const override {
        cout << uzenet << endl;

        if (gy.getBoldogsag() > 0) {
            gy.setBoldogsag(gy.getBoldogsag() / 2);
        } else {
            gy.setBoldogsag(gy.getBoldogsag() * 2);
        }
    }

    Virgacs *clone() const override {
        return new Virgacs(*this);
    }
};

class Mikulas {
public:
    set<string> nevek;
    vector<Ajandek*> ajandekok;

    Mikulas() = default;

    Mikulas(const Mikulas& mikulas) {
        for (auto& elem : mikulas.nevek) {
            this->nevek.insert(elem);
        }

        for (auto& elem : mikulas.ajandekok) {
            this->ajandekok.push_back(elem->clone());
        }

    }

    Mikulas& operator= (const Mikulas& mikulas) {
        if (&mikulas == this) {
            return *this;
        }

        for (auto& elem : ajandekok) {
            delete elem;
        }

        ajandekok.clear();
        this->nevek.clear();

        for (auto& elem : mikulas.nevek) {
            this->nevek.insert(elem);
        }

        for (auto& elem : mikulas.ajandekok) {
            this->ajandekok.push_back(elem->clone());
        }

        return *this;
    }

    ~Mikulas() {
        for (auto& elem : ajandekok) {
            delete elem;
        }

        ajandekok.clear();
    }

    Mikulas& operator<< (Ajandek& ajandek) {

        ajandekok.push_back(ajandek.clone());

        return *this;
    }

    Mikulas& operator>> (Gyerek &gyerek) {
        if (nevek.empty() || nevek.find(gyerek.getNev()) != nevek.end()) {
            return *this;
        }

        ajandekok[ajandekok.size() - 1]->ajandekoz(gyerek);
        nevek.insert(gyerek.getNev());
        ajandekok.pop_back();

        return *this;
    }

    Mikulas& operator<< (Mikulas& mikulas) {

        for (auto & elem : mikulas.ajandekok) {
            this->ajandekok.push_back(elem->clone());
        }

        for (auto& elem : mikulas.nevek) {
            try {
                this->nevek.insert(elem);
            } catch (exception& exception) {
                continue;
            }
        }

        return *this;
    }
};

#ifndef TEST_BIRO

int main() {
    Vonat mav( "MAV vonat", -10 );
    Vonat tgv( "TGV", 100 );
    Vonat kisvasut( "Kisvasut", 2 );
    Virgacs virgacs;

    Gyerek kisfiu;
    cout << kisfiu.getBoldogsag() << endl << endl;
    // 0

    mav.ajandekoz(kisfiu);
    cout << kisfiu.getBoldogsag() << endl << endl;
    // MAV vonat
    // -10
    // 100

    Mikulas miki;
    miki >> kisfiu;
    miki << mav << tgv << kisvasut;
    miki >> kisfiu;
    cout << kisfiu.getBoldogsag() << endl << endl;
    // Kisvasut
    // 2

    Mikulas m2;
    m2 << miki;
    m2 >> kisfiu;

    Gyerek gy2("..");
    m2 >> gy2;
    // TGV
}

#endif
