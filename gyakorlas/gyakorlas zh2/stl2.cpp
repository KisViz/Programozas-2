#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

// Amelyik reszt szeretned tesztelni, az ne legyen komment
#ifndef TEST_BIRO
#define FELADAT_1
#define FELADAT_2
#define FELADAT_3
#define FELADAT_4
#define FELADAT_5
#define FELADAT_6
#endif

// region ------------------------------- 1. FELADAT -------------------------------
#ifdef FELADAT_1
#ifndef BIRO_TESTER_FELJEGYZES
struct Feljegyzes {
    string nev; // bolygo neve
    float tavolsag; // bolygo tavolsaga fenyevben

    bool operator< (const Feljegyzes& other) const {
        return this->nev < other.nev;
    }
};
#endif

int eselyes_idegenek(set<Feljegyzes>& feljegyzesek) {
    // TODO feladat megoldasa

    return count_if(feljegyzesek.begin(), feljegyzesek.end(), []  (const Feljegyzes& feljegyzes) {return feljegyzes.tavolsag < 1000;});
}
#endif
// endregion

// region ------------------------------- 2. FELADAT -------------------------------
#ifdef FELADAT_2
string hadvezer_valasztas(const vector<string>& szavazatok) {
    // TODO feladat megoldasa
    map<string,unsigned> uj;

    for_each(szavazatok.begin(), szavazatok.end(), [&uj] (const auto& elem) {uj[elem]++;});

    unsigned nagy = 0;
    string nev;
    for_each(uj.begin(), uj.end(), [&nagy, &nev] (const auto& elem) {
        if (elem.second > nagy) {
            nagy = elem.second;
            nev = elem.first;
        }
    });
    return nev;
}
#endif
// endregion

// region ------------------------------- 3. FELADAT -------------------------------
#ifdef FELADAT_3
#ifndef BIRO_TESTER_KATONA
struct Katona {
    string nev;
    int allokepesseg;
};
#endif

void meghalnak(vector<Katona>& katonak, int kuszobertek) {
    // TODO feladat megoldasa

    auto vegeit = remove_if(katonak.begin(), katonak.end(), [&kuszobertek] (const Katona &katona) {return katona.allokepesseg < kuszobertek;});
    katonak.erase(vegeit,katonak.end());
}
#endif
// endregion

// region ------------------------------- 4. FELADAT -------------------------------
#ifdef FELADAT_4

bool nulla(pair<string, unsigned> szam) {
    return szam.second == 0;
}

bool gyors_idegenek(const map<string, unsigned>& kontinensek) {
    // TODO feladat megoldasa

    auto it = find_if(kontinensek.begin(), kontinensek.end(), nulla);
    return not(it == kontinensek.end());
}
#endif
// endregion

// region ------------------------------- 5. FELADAT -------------------------------
#ifdef FELADAT_5
vector<string> egyedi_varosok(const vector<string>& varosok) {
    // TODO feladat megoldasa

    set<string> uj;
    for_each(varosok.begin(), varosok.end(), [&uj] (const string& elem) {uj.insert(elem);});

    vector<string> vege;
    for_each(uj.begin(), uj.end(), [&vege] (const string& elem) {vege.push_back(elem);});
    return vege;
}
#endif
// endregion

// region ------------------------------- 6. FELADAT -------------------------------
#ifdef FELADAT_6
struct Zsakmanyolas {
    string nev; // kronozita neve
    string targy; // milyen targyat gyujtott
};

vector<string> legsikeresebbek(Zsakmanyolas* zsakmanyolasok, unsigned darab) {
    // TODO feladat megoldasa

    map<string, unsigned> nevek_szerint;
    for_each(zsakmanyolasok, zsakmanyolasok + darab, [&nevek_szerint] (const auto& elem) {nevek_szerint[elem.nev]++;});

    map<unsigned , string> db_szerint;
    for_each(nevek_szerint.begin(),nevek_szerint.end(), [&db_szerint] (const auto& elem) {db_szerint[elem.second] = elem.first;});

    vector<string> vege;
    for_each(db_szerint.rbegin(), db_szerint.rend(), [&vege] (const auto& nev) {vege.push_back(nev.second);});

    return vege;
}
#endif
// endregion

// region --------------------------- TESZTELO METODUSOK ---------------------------
#ifndef TEST_BIRO
#ifdef FELADAT_1
void test_feladat1() {
    cout << "1. feladat: eselyes_idegenek" << endl;

    // [INFO] A teszteset itt modosithato!
    set<Feljegyzes> halmaz = {
            {"VNDSLK", 4121},
            {"MKLBDL", 532},
            {"KBDMFK", 1001}
    };

    cout << "elvart: " << "1" << endl;
    cout << "kapott: " << eselyes_idegenek(halmaz) << endl;
    cout << endl;
}
#endif

#ifdef FELADAT_2
void test_feladat2() {
    cout << "2. feladat: hadvezer_valasztas" << endl;

    // [INFO] A teszteset itt modosithato!
    vector<string> s2 = {
            "Edit", "Martin", "Peter", "Edit", "Martin", "Edit"
//            "Zephyra", "Nova", "Nova", "Vortex", "Nebulon", "Zephyra", "Zephyra", "Xylix"
    };

    cout << "elvart: " << "Edit" << endl;
    cout << "kapott: " << hadvezer_valasztas(s2) << endl;
    cout << endl;
}
#endif

#ifdef FELADAT_3
void test_feladat3() {
    cout << "3. feladat: hadvezer_valasztas" << endl;

    // [INFO] A teszteset itt modosithato!
    Katona k1 = {"Denes", 2};
    Katona k2 = {"Anna", 11};
    Katona k3 = {"Peter", 22};

    vector<Katona> katonak {k1, k2, k3};
    int kuszobertek = 9;

    meghalnak(katonak, kuszobertek);

    cout << "elvart: " << "Anna Peter" << endl;
    cout << "kapott: ";
    for (const Katona& katona: katonak) {
        cout << katona.nev << " ";
    }

    cout << endl << endl;
}
#endif

#ifdef FELADAT_4
void test_feladat4() {
    cout << "4. feladat: gyors_idegenek" << endl;

    // [INFO] A teszteset itt modosithato!
    map<string, unsigned> kontinensek = {
            {"Europa", 412154},
            {"Afrika", 63435},
            {"Antarktisz", 0},
    };

    cout << "elvart: " << "1" << endl;
    cout << "kapott: " << gyors_idegenek(kontinensek) << endl;

    cout << endl;
}
#endif

#ifdef FELADAT_5
void test_feladat5() {
    cout << "5. feladat: egyedi_varosok" << endl;

    // [INFO] A teszteset itt modosithato!
    const vector<string> varosok = {
            "Szeged", "Szeged", "Budapest", "Szeged", "Mako", "Becs", "Parizs"
    };

    vector<string> kapott = egyedi_varosok(varosok);
    sort(kapott.begin(), kapott.end());

    cout << "elvart: " << "Becs Budapest Mako Parizs Szeged" << endl;
    cout << "kapott: ";
    for (const string& varos: kapott) {
        cout << varos << " ";
    }

    cout << endl << endl;
}
#endif

#ifdef FELADAT_6
void test_feladat6() {
    cout << "6. feladat: legsikeresebbek" << endl;

    // [INFO] A teszteset itt modosithato!
    Zsakmanyolas zsakmazsolasok[] = {
            {"Eszter", "aranyalma"},
            {"Attila", "osi kep"},
            {"Bence", "jezus szobor"},
            {"Eszter", "okori festmeny"},
            {"Attila", "jezus szobor"},
            {"Attila", "1 kg cekla"}
    };

    unsigned meret = 6;


    vector<string> kapott = legsikeresebbek(zsakmazsolasok, meret);

    cout << "elvart: " << "Attila Eszter Bence" << endl;
    cout << "kapott: ";
    for (const string& nev: kapott) {
        cout << nev << " ";
    }

    cout << endl;
}
#endif
#endif
// endregion

// region ---------------------------------- MAIN ----------------------------------
#ifndef TEST_BIRO
/*int main() {
#ifdef FELADAT_1
    test_feladat1();
#endif

#ifdef FELADAT_2
    test_feladat2();
#endif

#ifdef FELADAT_3
    test_feladat3();
#endif

#ifdef FELADAT_4
    test_feladat4();
#endif

#ifdef FELADAT_5
    test_feladat5();
#endif

#ifdef FELADAT_6
    test_feladat6();
#endif

    return 0;
}*/
#endif
// endregion
