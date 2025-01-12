#include <iostream>
#include <string>
#include "set"
#include "map"
#include <algorithm>

using namespace std;

class Konyvtar;

class FRElem {
protected:
    string nev;
    Konyvtar *szulo;

    FRElem(const string& nev, Konyvtar* szulo) :
            nev(nev), szulo(szulo) { }

public:
    virtual ~FRElem() = default;

    const string& getNev() const {
        return nev;
    }

    const Konyvtar* getSzulo() const noexcept {
        return szulo;
    }

    string getTeljesUtvonal() const;

    virtual FRElem* clone() const {
        return new FRElem(*this);
    }
};

class Fajl: public FRElem {
protected:
    string tartalaom;
public:
    Fajl(const string &nev, Konyvtar *szulo) : FRElem(nev, szulo), tartalaom("") {}

    const string &getTartalaom() const {
        return tartalaom;
    }

    void setTartalaom(const string &tartalaom) {
        Fajl::tartalaom = tartalaom;
    }

    void rm() {
        ///todo
    }

    Fajl *clone() const override {
        return new Fajl(*this);
    }
};

class Rendez {
public:
    bool operator() (const FRElem* elso, const FRElem* masodik) const {
        return elso->getNev() < masodik->getNev();
    }
};

class Konyvtar: public FRElem {
protected:
    set<FRElem*, Rendez> elemek;

public:

    Konyvtar(const string& nev, Konyvtar* szulo = nullptr): FRElem(nev, szulo) {}

     static Konyvtar& getGyoker() {

        for (auto& elem : elemek) {
            if (elem)
        }
         if (!gyoker) {
             gyoker = new Konyvtar("/");
         }

         return *gyoker;
    }

    static Konyvtar* getGyokerPtr() {
        if (!gyoker) {
            gyoker = new Konyvtar("/");
        }

        return gyoker;
    }

    Konyvtar& operator/ (const string& nev) {
        auto it = find_if(elemek.cbegin(), elemek.cend(), [&](const FRElem* elem) {
            return elem->getNev() == nev;
        });

        if (it != elemek.end()) {
            throw exception();
        }

        elemek.insert(this->clone());
        return *this;
    }

    Konyvtar *clone() const override {
        return new Konyvtar(*this);
    }
};

#ifndef TEST_BIRO

int main() {
#if 0
    Konyvtar& gyoker = Konyvtar::getGyoker();
  Konyvtar& k2 = gyoker / "elso" / "masodik";
  Konyvtar& k4 = k2 / "harmadik" / "negyedik";
  gyoker / "elso 2";
  gyoker / "elso 3";

  k2 % "readme.txt";
  k4 % "feladat.cpp";
  k4 / "otodik";

  cout << "Teljes utvonal" << endl;
  cout << k2.getTeljesUtvonal() << endl;
  cout << gyoker.getTeljesUtvonal() << endl;
  //  Teljes utvonal
  //  /elso/masodik/
  //  /

  cout << endl << "ls I." << endl;
  k2.ls();
  //  ls I.
  //  masodik
  //    harmadik
  //      negyedik
  //        feladat.cpp (fajl)
  //        otodik
  //    readme.txt (fajl)

  cout << endl << "ls II." << endl;
  gyoker.ls();
  //  ls II.
  //  /
  //    elso
  //      masodik
  //        harmadik
  //          negyedik
  //            feladat.cpp (fajl)
  //            otodik
  //        readme.txt (fajl)
  //    elso 2
  //    elso 3

  cout << endl << "operator >>" << endl;
  Konyvtar& masodik = gyoker >> "elso" >> "masodik";
  cout << masodik.getNev() << endl;
  //  operator >>
  //  masodik

  cout << endl << "cp" << endl;
  gyoker.cp(k2);
  gyoker.ls();
  //  cp
  //  /
  //    elso
  //      masodik
  //        harmadik
  //          negyedik
  //            feladat.cpp (fajl)
  //            otodik
  //        readme.txt (fajl)
  //    elso 2
  //    elso 3
  //    masodik
  //      harmadik
  //        negyedik
  //          feladat.cpp (fajl)
  //          otodik
  //      readme.txt (fajl)

  cout << endl << "rm I." << endl;
  (gyoker >> "masodik").rm();
  gyoker.ls();
  //  rm I.
  //  /
  //    elso
  //      masodik
  //        harmadik
  //          negyedik
  //            feladat.cpp (fajl)
  //            otodik
  //        readme.txt (fajl)
  //    elso 2
  //    elso 3

  cout << endl << "rm II." << endl;
  gyoker.rm();
  gyoker.ls();
  //  rm II.
  //  /
#endif
}
#endif
