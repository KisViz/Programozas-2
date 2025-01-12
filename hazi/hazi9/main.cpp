#include <iostream>
#include "vector"

using namespace std;

class Hiba: public exception {
    int hibakod;

public:
    explicit Hiba(int hibakod) : hibakod(hibakod) {}

    int get_hibakod() const {
        return hibakod;
    }
};

class Koordinata {
public:
    virtual void kiir() const = 0;
    virtual operator unsigned() const = 0;
    virtual Koordinata* clone() const = 0;

    virtual ~Koordinata() = default;
};

class Koordinata2D: public Koordinata{
protected:
    unsigned x, y;
public:
    Koordinata2D(unsigned x, unsigned y) : x(x), y(y) {}

    void kiir() const override {
        cout << "X = " << x << ", Y = " << y << endl;
    }

    operator unsigned() const override {
        return 2;
    }

    Koordinata *clone() const override {
        return new Koordinata2D(*this);
    }
};

class Koordinata3D: public Koordinata2D {
    unsigned z;

public:
    Koordinata3D(unsigned x, unsigned y, unsigned z): Koordinata2D(x, y),  z(z) {}

    void kiir() const override {
        cout << "X = " << x << ", Y = " << y << ", Z = " << z << endl;
    }

    operator unsigned() const override {
        return 3;
    }

    Koordinata *clone() const override {
        return new Koordinata3D(*this);
    }
};

class Jatek {
protected:
    string nev;
    unsigned tarhely;
    unsigned firmware;
    bool autosave = false;
    Koordinata *mentes = nullptr;

public:
    Jatek(const string &nev = "", unsigned tarhely = 0, unsigned firmware = 0):
    nev(nev), tarhely(tarhely), firmware(firmware)/*, autosave(false), mentes(nullptr)*/ {}

    Jatek(const Jatek& other): nev(other.nev), tarhely(other.tarhely), firmware(other.firmware), autosave(other.autosave) {
        mentes = other.mentes ? other.mentes->clone() : nullptr;
    }

    Jatek& operator=(const Jatek& other) {
        if (this == &other) {
            return *this;
        }

        delete mentes;
        nev = other.nev;
        tarhely = other.tarhely;
        firmware = other.firmware;
        autosave = other.autosave;
        mentes = other.mentes ? other.mentes->clone() : nullptr;

        return *this;
    }


    virtual ~Jatek() {
        delete mentes;
    }

    unsigned get_tarhely_igeny() const {
        return tarhely;
    }

    unsigned get_firmware_igeny() const {
        return firmware;
    }

    bool operator==(const Jatek& other) const {
        return nev == other.nev && tarhely == other.tarhely && firmware == other.firmware;
    }

    bool operator!() {
        autosave = !autosave;

        if (!autosave) {
            delete mentes;
            mentes = nullptr;
        }

        return autosave;
    }

    void kiir() const {
        if (autosave && mentes) {
            mentes->kiir();
        } else {
            cout << "Nincs mentes" << endl;
        }
    }

    virtual void fut(const vector<Koordinata*>& koordinatak) {
        if (autosave && !koordinatak.empty()) {
            delete mentes;
            mentes = koordinatak.at(koordinatak.size()-1)->clone();
        }

        cout << "nev: " << nev
             << " tarhely_igeny: " << tarhely
             << " firmware_igeny: " << firmware
             << " fut" << std::endl;

        for (const auto& k : koordinatak) {
            k->kiir();
        }
    }

    virtual Jatek* clone() const {
        return new Jatek(*this);
    }
};

class VRJatek: public Jatek {
public:
    VRJatek(const string &nev = "", unsigned tarhely = 0, unsigned firmware = 0):
            Jatek(nev,tarhely,firmware) {}

    void fut(const vector<Koordinata *>& koordinatak) override {
        for(unsigned i = 0; i < koordinatak.size(); ++i) {
            if (koordinatak[i]->operator unsigned int() != 3) {
                throw Hiba(4);
            }
//            kiir();
        }

        Jatek::fut(koordinatak);
    }

    VRJatek* clone() const override {
        return new VRJatek(*this);
    }
};

class Jatekplatform {
protected:
    unsigned max_tarhely;
    unsigned firmware;
    vector<Jatek*> jatekok;

public:
    Jatekplatform(unsigned maxTarhely, unsigned firmware) : max_tarhely(maxTarhely), firmware(firmware) {}

    virtual ~Jatekplatform() {
        for (auto& elem : jatekok) {
            delete elem;
        }

        jatekok.clear();
    }

    Jatekplatform(const Jatekplatform& other): max_tarhely(other.max_tarhely), firmware(other.firmware) {
        for (auto& elem : other.jatekok) {
            jatekok.push_back(elem->clone());
        }
    }

    Jatekplatform& operator= (const Jatekplatform& other) {
        if (&other == this) {
            return *this;
        }

        max_tarhely = other.max_tarhely;
        firmware = other.firmware;

        for (auto& elem : jatekok) {
            delete elem;
        }

        jatekok.clear();

        for (auto& elem : other.jatekok) {
            jatekok.push_back(elem->clone());
        }

        return *this;
    }

    unsigned get_firmware() const {
        return firmware;
    }

    unsigned size() const {
        return jatekok.size();
    }

    Jatekplatform& operator++ () { //pre
        ++firmware;
        return *this;
    }

    Jatekplatform operator++ (int) { //post
        Jatekplatform tmp = *this;
        operator++();
        return tmp;
    }

    virtual Jatekplatform& operator+=(const Jatek& jatek) {
        for (const auto& elem : jatekok) { //fel van e teve
            if (*elem == jatek) {
                throw Hiba(1);
            }
        }

        unsigned szaml = 0;
        for (const auto& elem : jatekok) {
            szaml += elem->get_tarhely_igeny();
        }

        if (szaml + jatek.get_tarhely_igeny() > max_tarhely) { //tarhely
            throw Hiba(2);
        }

        if (firmware < jatek.get_firmware_igeny()) { //szoros var
            throw Hiba(3);
        }

        jatekok.push_back(jatek.clone());

        return *this;
    }

    Jatek* operator[] (unsigned index) {
        if (index >= jatekok.size()) {
            throw Hiba(5);
        }

        return jatekok[index];
    }
};

class Playstation: public Jatekplatform{
    bool pro;

public:
    Playstation(unsigned maxTarhely, unsigned firmware, bool pro) : Jatekplatform(maxTarhely, firmware), pro(pro) {}

    Playstation(const Playstation& oother): Jatekplatform(oother), pro(oother.pro) {}

    bool get_pro() const {
        return pro;
    }

    Playstation& operator+=(const Jatek &jatek) override {

        if (!pro) {
            Jatekplatform::operator+=(jatek);
            return *this;
        } else {
            for (unsigned i = 0; i < jatekok.size(); ++i) {
                if (*jatekok[i] == jatek) {
                    throw Hiba(1);
                }
            }

            unsigned szaml = 0;
            for (unsigned i = 0; i < jatekok.size(); ++i) {
                szaml += jatekok[i]->get_tarhely_igeny();
            }

            if (szaml + jatek.get_tarhely_igeny() > max_tarhely) {
                throw Hiba(2);
            }

            if (firmware < jatek.get_firmware_igeny()) {
                firmware = jatek.get_firmware_igeny();
            }

            jatekok.push_back(jatek.clone());
            return *this;
        }


        /*try {
            Jatekplatform::operator+=(jatek);
        } catch (Hiba &hiba) {
            if (hiba.get_hibakod() == 3 && pro) {
                firmware = jatek.get_firmware_igeny();
                Jatekplatform::operator+=(jatek);
            }
        }

        return *this;*/
    }
};

int main() {
/*    Jatekplatform platform(100, 10);
    Jatek jatek1("Game1", 20, 5);
    VRJatek vrjatek("VRGame", 30, 7);

    try {
        platform += jatek1;
        platform += vrjatek;
        cout << "Játékok száma: " << platform.size() << endl;
    } catch (const Hiba& h) {
        cout << "Hiba kód: " << h.get_hibakod() << endl;
    }*/


    return 0;
}