#include <algorithm>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

class Komponens {
protected:
    string nev;

public:
    Komponens(const string& nev) : nev(nev) { }

    virtual operator string() const noexcept {
        return nev;
    }

    enum KomponensTipus { tAlaplap, tProcesszor, tMemoria, tKomponensMAX };
    virtual KomponensTipus getTipus() const noexcept = 0;

    virtual ~Komponens() = default; // ez helyes
};


class Alaplap : public Komponens {
public:
    Alaplap(const string& nev) : Komponens(nev) { }

    operator string() const noexcept override {
//        return Komponens::operator string();
        return nev;
    }

    KomponensTipus getTipus() const noexcept override {
        return tAlaplap;
    }
};


class Processzor : public Komponens {
    unsigned MHz;
public:
    Processzor(const string& nev, unsigned MHz) : Komponens(nev), MHz(MHz) { }

    operator unsigned () const {
        return MHz;
    }

    virtual operator string() const noexcept override {
        return Komponens::operator string() + " (" + to_string(MHz) + "MHz)";
    }

    KomponensTipus getTipus() const noexcept override{
        return tProcesszor;
    }
};


class Memoria : public Komponens {
    unsigned GB;
public:
    Memoria(const string& nev, unsigned gb) : Komponens(nev), GB(gb) { }

    virtual operator string() const noexcept override {
        return Komponens::operator string() + " (" + to_string(GB) + "GB RAM)";
    }

    virtual KomponensTipus getTipus() const noexcept override {
        return tMemoria;
    }

    operator unsigned() const {
        return GB;
    }
};


class Raktar {
    vector<reference_wrapper<Komponens>> komponensek;
public:
    Raktar() = default;

    Raktar& operator<<(Komponens& komponens) {
        komponensek.push_back(reference_wrapper<Komponens>(komponens));
        return *this;
    }

    reference_wrapper<Komponens>& operator[](unsigned i) {
        try {
            return komponensek.at(i);
        } catch (const out_of_range&) {
            throw out_of_range("rossz index " + to_string(i));
        }
    }

    const reference_wrapper<Komponens>& operator[](unsigned i) const {
        if (i <= komponensek.size())
            return komponensek[i];
        throw out_of_range("rossz index " + to_string(i));
    }

    unsigned getProcesszorDarab() const {
        return count_if(komponensek.cbegin(), komponensek.cend(), [](auto k){ return k.get().getTipus() == Komponens::tProcesszor; });
    }

    unsigned getOsszMemoria() const {
        unsigned ossz = 0;
        for_each(komponensek.begin(), komponensek.end(), [&ossz](auto k) {
            if (k.get().getTipus() == Komponens::tMemoria) {
                ossz += (unsigned)(Memoria&)(Komponens&)k;
            }
        });
        return ossz;
    }

    bool vanTeljesGep() const {
        unsigned komp = 0;
        for_each(komponensek.cbegin(), komponensek.cend(), [&komp](auto k) {
            komp|=1<<k.get().getTipus();
        });

        for (unsigned i = 0; i < Komponens::tKomponensMAX; i++) {
            if ((komp & 1<<i) == 0)
                return false;
        }
        return true;
    }

    void selejtez(unsigned minMHz, unsigned minGB) {
        vector<reference_wrapper<Komponens>> uj;
        copy_if(komponensek.begin(), komponensek.end(), back_inserter(uj), [=](auto k) {
            switch (k.get().getTipus()) {
                case Komponens::tMemoria:
                    return minGB <= ((unsigned)(Memoria&)k.get());
                case Komponens::tProcesszor:
                    return minMHz <= ((unsigned)(Processzor&)k.get());
                default:
                    return true;
            }
        });
        komponensek = uj;
    }

    friend ostream& operator<<(ostream& os, const Raktar& r);
};

ostream& operator<<(ostream& os, const Raktar& r) {
    for (unsigned i = 0; i < r.komponensek.size() ; ++i)
        os << (string)(Komponens&)r[i] << endl;
    return os;
}





/*int main() {

    { // 1
        cout << "teszt Alaplap" << endl;
        Alaplap asusX("Asus X");
        cout << (string)asusX << " " << asusX.getTipus() << endl;
        cout << ([](const Komponens& k) { return k.getTipus(); })(asusX) << endl;
    }


    { // 2
        cout << endl << endl << "teszt Processzor" << endl;
        Processzor intelAlpha("Intel Alpha", 5600);
        cout << (string)intelAlpha << " " << intelAlpha.getTipus() << " " << (unsigned)intelAlpha << endl;
        cout << ([](const Komponens& k) { return k.getTipus(); })(intelAlpha) << endl;
    }


    { // 3
        cout << endl << endl << "teszt Memoria" << endl;
        Memoria mem4GB("RAM", 4);
        cout << (string)mem4GB << " " << mem4GB.getTipus() << " " << (unsigned)mem4GB << endl;
        cout << ([](const Komponens& k) { return k.getTipus(); })(mem4GB) << endl;
    }


    { // 4
        cout << endl << endl << "teszt Processzor, operator <<, operator[], operator string - I." << endl;
        Processzor intelAlpha("Intel Alpha", 5600);
        Memoria mem4GB("RAM", 4);
        Alaplap asusX("Asus X");
        Raktar raktar;
        raktar << intelAlpha << mem4GB << asusX;

        try {
            cout << (string)raktar[0].get() << endl;
            cout << (string)raktar[1].get() << endl;
            cout << (string)raktar[2].get() << endl;
        } catch (const out_of_range& e) {
            cout << e.what() << endl;
        } catch (...) {
            cout << "HIBA" << endl;
        }

        try {
            cout << (string)raktar[-1].get() << endl;
        } catch (const out_of_range& e) {
            cout << "OK" << endl;
        } catch (...) {
            cout << "HIBA" << endl;
        }

        try {
            cout << (string)raktar[3000].get() << endl;
        } catch (const out_of_range& e) {
            cout << "OK" << endl;
        } catch (...) {
            cout << "HIBA" << endl;
        }
    }


    { // 5
        cout << endl << endl << "teszt Processzor, operator <<, operator[], operator string - II." << endl;
        Processzor intelAlpha("Intel Alpha", 5600);
        Memoria mem4GB("RAM", 4);
        Alaplap asusX("Asus X");
        Raktar raktar;
        raktar << intelAlpha << mem4GB << asusX;
        try {
            ([](const Raktar& r){ cout << (string)r[1].get() << endl; })(raktar);
            cout << (string)(raktar[0] = mem4GB).get() << endl;
        } catch (const out_of_range& e) {
            cout << e.what() << endl;
        } catch (...) {
            cout << "HIBA" << endl;
        }
    }


    { // 6
        cout << endl << endl << "teszt Processzor, operator <<, getProcesszorDarab" << endl;
        Processzor intelAlpha("Intel Alpha", 5600);
        Processzor intelBeta("Intel Beta", 8700);
        Memoria mem4GB("RAM", 4);
        Memoria mem8GB("RAM", 8);
        Alaplap asusX("Asus X");
        Alaplap asusY("Asus Y");
        Raktar raktar;

        raktar << intelAlpha << mem4GB << asusX;
        cout << raktar.getProcesszorDarab() << endl;

        raktar << intelBeta << mem8GB << asusY;

        unsigned (Raktar::*rgpd)() const = &Raktar::getProcesszorDarab;
        cout << (raktar.*rgpd)() << endl;
    }


    { // 7
        cout << endl << endl << "teszt Processzor, operator <<, getOsszMemoria" << endl;
        Processzor intelAlpha("Intel Alpha", 5600);
        Processzor intelBeta("Intel Beta", 8700);
        Memoria mem4GB("RAM", 4);
        Memoria mem8GB("RAM", 8);
        Alaplap asusX("Asus X");
        Alaplap asusY("Asus Y");
        Raktar raktar;

        raktar << intelAlpha << mem4GB << asusX;
        cout << raktar.getOsszMemoria() << endl;

        raktar << intelBeta << mem8GB << asusY;

        unsigned (Raktar::*rgom)() const = &Raktar::getOsszMemoria;
        cout << (raktar.*rgom)() << endl;
    }


    { // 8
        cout << endl << endl << "teszt Processzor, operator <<, operator[], operator string, vanTeljesGep" << endl;
        Processzor intelAlpha("Intel Alpha", 5600);
        Processzor intelBeta("Intel Beta", 8700);
        Memoria mem4GB("RAM", 4);
        Memoria mem8GB("RAM", 8);
        Alaplap asusX("Asus X");
        Raktar raktar;
        raktar << intelAlpha << intelBeta << mem4GB;
        cout << raktar.vanTeljesGep() << endl;
        raktar << intelAlpha << intelBeta;
        cout << raktar.vanTeljesGep() << endl;
        raktar << asusX;
        cout << raktar.vanTeljesGep() << endl;
        raktar[2] = raktar[0];
        cout << raktar.vanTeljesGep() << endl;
        cout << raktar << endl;
    }


    { // 9
        cout << endl << endl << "teszt Processzor, operator <<, operator string, selejtez" << endl;
        Processzor intelAlpha("Intel Alpha", 5600);
        Processzor intelBeta("Intel Beta", 8700);
        Memoria mem4GB("RAM", 4);
        Memoria mem8GB("RAM", 8);
        Alaplap asusX("Asus X");
        Alaplap asusY("Asus Y");
        Raktar raktar;
        raktar << intelAlpha << intelBeta << mem4GB << mem8GB << asusX << asusY;
        cout << raktar << endl << endl;
        raktar.selejtez(6, 8000);
        cout << raktar << endl << endl;
    }

    return 0;
}*/
