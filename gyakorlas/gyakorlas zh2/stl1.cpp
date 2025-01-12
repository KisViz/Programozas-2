#include<algorithm>
#include<iostream>
#include<map>
#include<set>
#include<string>
#include<vector>

using namespace std;

#ifndef TEST_BIRO
#define TEST_KEDVENC_SZAMOK
#define TEST_UVEGGOLYOK
#define TEST_UTICELOK
#define TEST_NAGY_KEZDOBETU
#define TEST_PENZVALTAS
#endif // TEST_BIRO


#ifdef TEST_KEDVENC_SZAMOK

// IDE DOLGOZZ!!!
/*int kedvenc_szamok(const vector<int> eredeti, vector<int>& uj) {
    int szaml = 0;
    for (auto &elem : eredeti) {
        if (elem == 13) {
            uj.push_back(elem);
            szaml++;
        } else if (elem > 99 and to_string(elem).substr(to_string(elem).length()-2, to_string(elem).length()-1) == "13") {
//           cout << elem << endl;
            uj.push_back(elem);
            szaml++;
        }
    }

    return szaml;
}*/

int kedvenc_szamok(const vector<int>& eredeti, vector<int>& uj) {
    int szaml = 0;
    for (auto elem : eredeti) {
        if (elem % 100 == 13  or elem % 100 == -13) {
            uj.push_back(elem);
            szaml++;
        }
    }
    return szaml;
}

auto kedvenc_szamok_lambda1 = [] ( const vector<int> eredeti, vector<int>& uj) {
    return count_if(eredeti.begin(), eredeti.end(), [/*scope valtozok*/&](/*parameterek*/int elem) {
        /*fgv maga*/

        if (elem % 100 == 13  or elem % 100 == -13) {
            uj.push_back(elem);
            return true;
        } else {
            return false;
        }
    });
};

auto kedvenc_szamok_lambda2= []( const vector<int> eredeti, vector<int>& uj) {
    int szaml = 0;

    for_each(eredeti.begin(), eredeti.end(), [&](int elem){
        if (elem % 100 == 13 or elem % 100 == -13) {
            uj.push_back(elem);
            szaml++;
        }
    });

    return szaml;
};

#ifndef TEST_BIRO
void test_kedvenc_szamok() {
//    string szo = "ls";
//    cout << szo.substr(szo.length()-2, szo.length()-1) << endl;
//cout << to_string(1402%100) << endl;
  vector<int> sz { 18, 13, 813, 1313, 9, 44, 42, 113, 131, -13, -1313 };
  vector<int> k;
  cout << kedvenc_szamok(sz, k) << "db kedvenc szam van" << endl;
  for (int i : k)
    cout << i << endl;

  k = {};
  cout << endl;
  cout << kedvenc_szamok_lambda1(sz, k) << "db kedvenc szam van" << endl;
  for (int i : k)
      cout << i << endl;

  k = {};
  cout << endl;
  cout << kedvenc_szamok_lambda2(sz, k) << "db kedvenc szam van" << endl;
  for (int i : k)
      cout << i << endl;

  // kimenet
  // 4
  // 13
  // 813
  // 1313
  // 113
}
#endif // TEST_BIRO
#endif // TEST_KEDVENC_SZAMOK


#ifdef TEST_UVEGGOLYOK

// IDE DOLGOZZ!!!

map<string, unsigned> uveggolyok_osszeszamolasa(const vector<string>& golyok) {
    map<string, unsigned> darab;

    for (const auto& elem : golyok) {
        darab[elem]++;
    }

    return darab;
}

//hulyeség, rosszul csinaltam, ez nem lambda
/*map<string, unsigned> uveggolyok_osszeszamolasa_lambda1(const vector<string>& golyok) {
    map<string, unsigned> darab;

    for_each(golyok.begin(), golyok.end(), [&](string elem){
        darab[elem]++;
    });

    return darab;
}*/

auto uveggolyok_osszeszamolasa_lambda2 = [](const vector<string>& golyok) {
    map<string, unsigned> darab;

    for_each(golyok.begin(), golyok.end(), [&](string elem){
        darab[elem]++;
    });

    return darab;
};


#ifndef TEST_BIRO
void test_uveggolyok_osszeszamolasa() {
  string s[] = { "piros", "kek", "zold", "sarga", "fekete", "feher" };

  cout << "az uveggolyok rendezve es osszeszamolva:" << endl;

  vector<string> be = { s[0], s[2], s[2], s[1], s[3], s[4], s[2], s[0], s[5], s[4], s[5], s[5] };
  for (auto elem : uveggolyok_osszeszamolasa(be)) {
      cout << elem.first << " : " << elem.second << endl;
  }

//  cout << endl;
//  for (auto elem : uveggolyok_osszeszamolasa_lambda1(be)) {
//      cout << elem.first << " : " << elem.second << endl;
//  }

  cout << endl;
  for (auto elem : uveggolyok_osszeszamolasa_lambda2(be)) {
      cout << elem.first << " : " << elem.second << endl;
  }
//  for (auto &[szin, db] : uveggolyok_osszeszamolasa( { s[0], s[2], s[2], s[1], s[3], s[4], s[2], s[0], s[5], s[4], s[5], s[5] } ) )
//    cout << szin << " : " << db << endl;
}
#endif // TEST_BIRO
#endif // TEST_UVEGGOLYOK


#ifdef TEST_UTICELOK

void utazas(const map<string, unsigned>& varos, const vector<unsigned>& nyeremeny, map<unsigned /* nyeremeny */, unsigned /* uticelok szama */>& uticelok_szama) {
    // IDE DOLGOZZ!!!

    for (const auto& nyer : nyeremeny) {
        unsigned szaml = 0;
        for (const auto &var: varos) {
            if (var.second <= nyer) {
                szaml++;
            }
        }

        uticelok_szama[nyer] = szaml;
    }
}

auto utazas_lambda = [] (const map<string, unsigned>& varos, const vector<unsigned>& nyeremeny, map<unsigned /* nyeremeny */, unsigned /* uticelok szama */>& uticelok_szama) {
    for (const auto& nyer : nyeremeny) {
        unsigned szaml = 0;
        for (const auto &var: varos) {
            if (var.second <= nyer) {
                szaml++;
            }
        }

        uticelok_szama[nyer] = szaml;
    }
};

#ifndef TEST_BIRO
void test_utazas() {
  map<string, unsigned> varos {
    { "Budapest",  160 },
    { "New York", 7150 },
    { "London",   1590 },
    { "Berlin",    850 }
  };
  vector<unsigned> nyeremeny { 200, 1000, 3000, 4000 };
  map<unsigned, unsigned> hova;
  utazas(varos, nyeremeny, hova);

  for (const auto& elem : hova)
      cout << elem.first << " " << elem.second << endl;

  cout << endl;
  hova.empty();
  utazas_lambda(varos, nyeremeny, hova);
  for (const auto& elem : hova)
      cout << elem.first << " " << elem.second << endl;

//  for (const auto& [tav, db] : hova)
//    cout << tav << " " << db << endl;

  // kimenet
  // 200 1
  // 1000 2
  // 3000 3
  // 4000 3
}
#endif // TEST_BIRO
#endif // TEST_UTICELOK


#ifdef TEST_NAGY_KEZDOBETU

int nagy_kezdobetuk(vector<string> szavak) {
    return count_if(szavak.begin(), szavak.end(), [] (string& szo){return not szo.empty() and isupper(szo[0]);});
}

auto nagy_kezdobetuk_lambda = [](vector<string> szavak){
    return count_if(szavak.begin(), szavak.end(), [] (string& szo){return not szo.empty() and isupper(szo[0]);});
};

// IDE DOLGOZZ!!!

#ifndef TEST_BIRO
void test_nagy_kezdobetuk() {
  cout << nagy_kezdobetuk( { "Alma", "Korte", "barack, Sargabarack", "szilva", "Dio" } ) << endl;
  cout << nagy_kezdobetuk_lambda({ "Alma", "Korte", "barack, Sargabarack", "szilva", "Dio" }) << endl;
  // kimenet
  // 3
}
#endif // TEST_BIRO
#endif // TEST_NAGY_KEZDOBETU


#ifdef TEST_PENZVALTAS

// IDE DOLGOZZ!!!

int penzvaltas(const vector<int>& osszegedk) {
    int szaml = 0;
    for (const int elem : osszegedk) {
        szaml += elem / 100;
        int tmp = elem % 100;
//        cout << "tmp: " << tmp << " " << "szaml: " << szaml << endl;

        szaml += tmp / 10;
        tmp = tmp % 10;
//        cout << "tmp: " << tmp << " " << "szaml: " << szaml << endl;

        szaml += tmp;
//        cout << "tmp: " << tmp << " " << "szaml: " << szaml << endl;
    }

    return szaml;
}

auto penzvaltas_lambda = ([] (const vector<int>& osszegedk) {
    int szaml = 0;
    for_each(osszegedk.begin(), osszegedk.end(), [&szaml](int elem){
        szaml += elem / 100;
        int tmp = elem % 100;
//        cout << "tmp: " << tmp << " " << "szaml: " << szaml << endl;

        szaml += tmp / 10;
        tmp = tmp % 10;
//        cout << "tmp: " << tmp << " " << "szaml: " << szaml << endl;

        szaml += tmp;
//        cout << "tmp: " << tmp << " " << "szaml: " << szaml << endl;
    });

    return szaml;
});

#ifndef TEST_BIRO
void test_penzvaltas() {
  cout << penzvaltas({ 5 }) << endl;
  cout << penzvaltas({ 5, 10 }) << endl;
  cout << penzvaltas({ 5, 17, 102 }) << endl;
  cout << penzvaltas({ 5, 17, 102, 1000 }) << endl;

  cout << endl;

  cout << penzvaltas_lambda({ 5 }) << endl;
  cout << penzvaltas_lambda({ 5, 10 }) << endl;
  cout << penzvaltas_lambda({ 5, 17, 102 }) << endl;
  cout << penzvaltas_lambda({ 5, 17, 102, 1000 }) << endl;

  // kiement
  // 5
  // 6
  // 16
  // 26
}
#endif // TEST_BIRO
#endif // TEST_PENZVALTAS


#ifndef TEST_BIRO

/*int main() {
#ifdef TEST_KEDVENC_SZAMOK
    test_kedvenc_szamok();
#endif // TEST_KEDVENC_SZAMOK

#ifdef TEST_UVEGGOLYOK
    test_uveggolyok_osszeszamolasa();
#endif // TEST_UVEGGOLYOK

#ifdef TEST_UTICELOK
    test_utazas();
#endif // TEST_UTICELOK

#ifdef TEST_NAGY_KEZDOBETU
    test_nagy_kezdobetuk();
#endif // TEST_NAGY_KEZDOBETU

#ifdef TEST_PENZVALTAS
    test_penzvaltas();
#endif // TEST_PENZVALTAS

    return 0;
}*/

#endif // TEST_BIRO
