#include <iostream>
#include <string>
#include <cassert>
#include <cstring>
#include <sstream>
#include "set"
#include "map"

using namespace std;

/////////////////////////
//Ide dolgozz!!

bool osszehasonlit(string elso, string masodik) {
    if (elso.empty() && masodik.empty()) {
        return true;
    }

    if (elso.size() != masodik.size()) {
//        cout << "kivandorlo" << endl;
        return false;
    }

    for (int i = 0; i < elso.size(); ++i) {
        if (tolower(elso[i]) != tolower(masodik[i])) {
            return false;
        }
    }

    return true;
}

class Telepes {
    string nev;
    string szulBolygo;
    string bolygo;
    unsigned ero;

    bool vegan;

public:

    Telepes(const string &nev, const string &szulBolygo, const string &bolygo, unsigned int ero) : nev(nev), szulBolygo(
            szulBolygo), bolygo(bolygo), ero(ero) {}

    Telepes() : nev(""), szulBolygo(""), bolygo(""), ero(1), vegan(false){}

    Telepes(const string &nev, const string &bolygo, const unsigned ero = 1) : nev(nev), bolygo(bolygo), szulBolygo(bolygo), ero(ero) {    }

    const string &getNev() const {
        return nev;
    }

    void setNev(const string &nev) {
        Telepes::nev = nev;
    }

    const string &getSzulBolygo() const {
        return szulBolygo;
    }

    void setSzulBolygo(const string &szulBolygo) {
        Telepes::szulBolygo = szulBolygo;
    }

    const string &getBolygo() const {
        return bolygo;
    }

    void setBolygo(const string &bolygo) {
        Telepes::bolygo = bolygo;
    }

    const unsigned &getEro() const {
        return ero;
    }

    void setEro(const unsigned &ero) {
        Telepes::ero = ero;
    }

    bool isVegan() const {
        return vegan;
    }

    void setVegan(bool vegan) {
        Telepes::vegan = vegan;
    }

    bool kivandorlo() const{
        return !osszehasonlit(bolygo,szulBolygo);
    }

    void dolgozik(string &munkak) const {
        stringstream munka(munkak);
        string szo;
        int szaml = 1;
        string uj;

        for (int i = 0; !munka.eof(); ++i) {
            getline(munka,szo,';');
            if (i >= ero) {
                uj += szo + ";";
            }
        }

        if (!uj.empty()) {
            uj.pop_back();
        }
//        cout << uj << endl;
        munkak = uj;
    }
};

class Kolonia;
bool veganE (Kolonia kolonia);

class Kolonia {
    Telepes telepesek[25];
    string nev;
    string bolygo;
    unsigned letszam;

public:

    Kolonia(const string &nev, const string &bolygo) : nev(nev), bolygo(bolygo), letszam(0) {}

    Kolonia() : nev(""), bolygo(""), letszam(0) {}

    const string &getNev() const {
        return nev;
    }

    const string &getBolygo() const {
        return bolygo;
    }

    unsigned int getLetszam() const {
        return letszam;
    }

    //sajat ganyolas a vegane feladathoz
    Telepes TelepesIndexen(unsigned index) const {
        if (index < letszam) {
            return telepesek[index];
        }

        return Telepes();
    }

    friend bool veganE (Kolonia kolonia);

    void letelepszik(Telepes uj) {
        if (letszam >= 25) {
            cout << "A kolonia megtelt" << endl;
            return;
        }

        if (veganE(*this)) {
            if (!uj.isVegan()) {
                cout << "A kolonia vegan" << endl;
                return;
            }
        }

        uj.setBolygo(bolygo);
        telepesek[letszam] = uj;
        letszam++;
    }

    void nevsor() {
        set<string> nevsor;
        for (int i = 0; i < letszam; ++i) {
            nevsor.insert(telepesek[i].getNev());
        }

        for (const auto& adottNev : nevsor) {
            cout << adottNev << endl;
        }
    }
    
    unsigned legerosebb() const {
        if (letszam == 0) {
            return 0;
        } else {
            unsigned legnagyobb = 0;
            for (int i = 0; i < letszam; ++i) {
                if (telepesek[i].getEro() > legnagyobb) {
                    legnagyobb = telepesek[i].getEro();
                }
            }
            
            return legnagyobb;
        }
    }

    int szamol(string bolygo) const {
        int szaml = 0;
        for (int i = 0; i < letszam; ++i) {
            if (osszehasonlit(bolygo, telepesek[i].getSzulBolygo())) {
                szaml++;
            }
        }

        return szaml;
    }

    map<unsigned, unsigned> eroHisztogram() const {
        map<unsigned, unsigned> hist;
        for (int i = 0; i < letszam; ++i) {
            unsigned ero = telepesek[i].getEro();
            hist[ero]++;
        }

        return hist;
    }
};

bool veganE (Kolonia kolonia) {
    if (kolonia.letszam == 0) {
        return false;
    }

    unsigned veganSzaml = 0;
    for (int i = 0; i < kolonia.getLetszam(); ++i) {
        if (kolonia.TelepesIndexen(i).isVegan()) {
            veganSzaml++;
        }
    }

    return ((float)veganSzaml / kolonia.getLetszam() > 0.5);
}
////////////////////////

//=== Teszteles bekapcsolasa kikommentezessel
//#define TEST_default_konstruktor
//#define TEST_param_konstruktor
//#define TEST_param_konstruktor2
//#define TEST_kivandorlo
//#define TEST_munkavegzes
//=== Teszteles bekapcsolas vege

/*
Készíts egy Telepes nevű osztályt, mely a különféle bolygókon letelepedett emberek adatait tárolja.
Négy adattagja van, ezek mindegyikéhez tartozik getter és setter.
- szul_bolygo: születési bolygó
- bolygo: jelenlegi bolygó
- nev: a telepes neve
- ero: munkavégző képesség (unsigned int)
Rendelkezzen egy default konstruktorral, amely a nev, szul_bolygo és bolygo adattagokat üres sztringre inicializálja, az ero-t pedig 1-re.
*/
void test_default_konstruktor(){
#if defined TEST_default_konstruktor && !defined TEST_BIRO
    Telepes t1;
  assert(t1.getNev() == "");
  assert(t1.getSzulBolygo() == "");
  assert(t1.getBolygo() == "");
  assert(t1.getEro() == 1);

  t1.setSzulBolygo("Mars");
  t1.setBolygo("Venus");
  t1.setNev("Jevgenyij Anyegin");
  t1.setEro(10);
  assert(t1.getNev() == "Jevgenyij Anyegin");
  assert(t1.getSzulBolygo() == "Mars");
  assert(t1.getBolygo() == "Venus");
  assert(t1.getEro() == 10);
#endif
}

/*
Legyen egy konstruktora, mely négy paraméterrel rendelkezik és mind a négy adattagot a paramétereknek megfelelően állítja be.
Paraméterek sorrendje: nev, szul_bolygo, bolygo, ero
*/
void test_param_konstruktor(){
#if defined TEST_param_konstruktor && !defined TEST_BIRO
    const Telepes t1("Franz Kafka", "Mars", "Venus", 50);
  assert(t1.getNev() == "Franz Kafka");
  assert(t1.getSzulBolygo() == "Mars");
  assert(t1.getBolygo() == "Venus");
  assert(t1.getEro() == 50);
#endif
}

/*
Legyen egy konstruktora, amely két sztringet és egy unsigned paramétert vár. Az első sztring paraméter alapján a telepes neve legyen inicializálva,
míg a második sztring paraméter a telepes jelenlegi bolygójának a neve.
Ez alapján legyen inicializálva a bolygo és a szul_bolygo adattag is.
Lehessen úgy is használni, hogy meghívásakor nem adunk meg unsigned értéket, csak a két sztringet. Ilyenkor az ero érték legyen 1-re állítva.
*/
void test_param_konstruktor2(){
#if defined TEST_param_konstruktor2 && !defined TEST_BIRO
    const Telepes t1("Kurt Vonnegut", "Venus", 4);
  assert(t1.getNev() == "Kurt Vonnegut");
  assert(t1.getSzulBolygo() == "Venus");
  assert(t1.getBolygo() == "Venus");
  assert(t1.getEro() == 4);

  const Telepes t2("Kurt Vonnegut", "Venus");
  assert(t2.getNev() == "Kurt Vonnegut");
  assert(t2.getSzulBolygo() == "Venus");
  assert(t2.getBolygo() == "Venus");
  assert(t2.getEro() == 1);
#endif
}

/*
Készíts egy kivandorlo() metódust a Telepes osztályba, mely segít eldönteni, hogy a telepes kivandorlónak minősül-e.
A visszatérési értéke akkor legyen igaz, ha a szul\_bolygo és bolygo adattagok értéke nem egyenlő egymással.
Két bolygó neve egyenlőnek számít, ha csak kisbetű/nagybetű eltérés van a nevükben (pl. ``Mars'' és ``mars'' egyenlőek).
A bolygók nevei ascii karakterek (tehát nem tartalmaznak pl. ékezetes betűket). Ha mindkét adattag értéke üres sztring egyenlőnek tekinthetőek.
*/
void test_kivandorlo(){
#if defined TEST_kivandorlo && !defined TEST_BIRO
    const Telepes t1("Franz Kafka", "", "", 50); //Kafka kivandorlo
    assert(!t1.kivandorlo());
#endif
}

/*
Készíts egy dolgozik() metódust, amely naplózza a telepes munkavégézését.
A paraméterként kapott sztring reprezentálja az egymás után következő feladatokat pontosvesszővel elválasztva.
A feladatok alfanumerikus kódokkal vannak reprezentálva, pl.: b1 - kapálás, b22 - ültetés stb.
A telepesek minden feladatot el tudnak végezni, azonban csak annyi darabot,
amennyi az ero értékük, utána kifáradnak. A metódus célja, hogy levágja azokat a munkákat a sztring elejéről, amiket a telepes elvégzett.
*/
void test_munkavegzes(){
#if defined TEST_munkavegzes && !defined TEST_BIRO
    const Telepes t1("Kovacs Geza", "Uranus", "Px-2312", 0);
  string munkak = "b1;b22;c3;x823";
  t1.dolgozik(munkak);
  assert(munkak == "c3;x823");
#endif
}

int main(){

/*    test_default_konstruktor();
    test_param_konstruktor();
    test_param_konstruktor2();
    test_kivandorlo();
    test_munkavegzes();


 
    Kolonia k("VegaLand", "Föld");
    Telepes t1("John", "Föld", "Mars", 5);
    Telepes t2("Doe", "Föld", "Mars", 3);
    Telepes t3("Doe", "Föld", "Mars", 3);


    t1.setVegan(true);
    t2.setVegan(true);
    t3.setVegan(true);
    k.letelepszik(t1);
    k.letelepszik(t2);
    k.letelepszik(t3);

//    cout << veganE(k) << endl;*/

    return 0;
}
