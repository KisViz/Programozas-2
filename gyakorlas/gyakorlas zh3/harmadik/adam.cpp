#include <iostream>
#include <vector>

using namespace std;

class Gyerek {
    int boldogsag = 0;
public:
    int getBoldogsag() const {
        return boldogsag;
    }

    Gyerek& setBoldogsag( int b ) {
        boldogsag = b; return *this;
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

    virtual Ajandek* clone() const {
        return new Ajandek(*this);
    }

    virtual unsigned tipus() const {
        return 0;
    }
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

    unsigned int tipus() const override {
        return 1;
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

    unsigned int tipus() const override {
        return 2;
    }
};

class Mikulas {
public:
    vector<Ajandek*> ajandekok;
    unsigned szaml = 0;

    ~Mikulas() {
        for (auto& elem : ajandekok) {
            delete elem;
        }

        ajandekok.clear();
    }

    Mikulas& operator<< (Ajandek* ajandek) {
        ajandekok.push_back(ajandek->clone());
        return *this;
    }

    Mikulas& operator>> (Gyerek& gyerek) {
        if (szaml == ajandekok.size()) {
            szaml = 0;
        }
//        cout << "tipus: " << ajandekok[szaml % (ajandekok.size())]->tipus() << endl;
        ajandekok[szaml]->ajandekoz(gyerek);
        szaml++;

        return *this;
    }

    Mikulas& operator^ (Ajandek* ajandek) {

        Mikulas tmp = *this;

        for (auto& elem : ajandekok) {
            delete elem;
        }

        ajandekok.clear();

        for (auto& elem : tmp.ajandekok) {
            if (elem->tipus() != ajandek->tipus()) {
                this->ajandekok.push_back(elem->clone());
            }
        }

        return *this;
    }
};

#ifndef TEST_BIRO

/*int main() {

    Vonat mav( "MAV vonat", -10 );
    Vonat tgv( "TGV", 100 );
    Vonat kisvasut( "Kisvasut", 2 );
    Virgacs virgacs;

    Gyerek kisfiu;
    cout << "boldogsag: " << kisfiu.getBoldogsag() << endl << endl;
    // 0

    mav.ajandekoz(kisfiu);
    cout << kisfiu.getBoldogsag() << endl << endl;
    // MAV vonat
    // -10

    virgacs.ajandekoz(kisfiu);
    cout << kisfiu.getBoldogsag() << endl << endl;
    // jaj
    // -20

    tgv.ajandekoz(kisfiu);
    cout << kisfiu.getBoldogsag() << endl << endl;
    // TGV
    // 100

    Mikulas mikulas;
    mikulas << &kisvasut << &virgacs;
    mikulas >> kisfiu;
    cout << kisfiu.getBoldogsag() << endl << endl;
    // Kisvasut
    // 2



    mikulas >> kisfiu;
    cout << kisfiu.getBoldogsag() << endl << endl;
    // jaj
    // 1

    mikulas >> kisfiu;
    cout << kisfiu.getBoldogsag() << endl << endl;
    // Kisvasut
    // 2
*//*
    Mikulas mikulas2 = mikulas;
    mikulas2 >> kisfiu;
    cout << kisfiu.getBoldogsag() << endl << endl;
    // jaj
    // 1
*//*
*//*
    mikulas^&tgv;
    mikulas >> kisfiu;
    cout << kisfiu.getBoldogsag() << endl << endl;
    // jaj
    // 0
    *//*
*//*
    mikulas >> kisfiu;
    cout << kisfiu.getBoldogsag() << endl << endl;
    // jaj
    // 0
*//*
}*/

#endif
