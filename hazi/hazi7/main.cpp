#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;

#ifndef TEST_BIRO
#define JARAT_SET
#define MIN_AR
#define SZAMOL
#define FILTER
#define FULLSORT
#define FULLCOST
#define AKCIO
#endif // TEST_BIRO

class Jarat {
    string honnan, hova;
    unsigned ar;


public:
    Jarat(const string& honnan, const string& hova, unsigned ar) :
            honnan(honnan), hova(hova),
            ar(ar) { }


    const string &getHonnan() const {
        return honnan;
    }

    const string &getHova() const {
        return hova;
    }

    unsigned int getAr() const {
        return ar;
    }

    void setAr(unsigned a){
        ar = a;
    }

    friend ostream& operator<<(ostream& os, const Jarat& t) {
        return os << t.honnan << "-" << t.hova << " (" << t.ar << " forint)";
    }

    //IDE DOLGOZZ!!
    bool operator< (const Jarat& jarat) const {
        if (honnan != jarat.honnan) {
            return honnan < jarat.honnan;
        }

        return hova < jarat.hova;
    }


};



#ifdef JARAT_SET

//IDE DOLGOZZ!!

set<Jarat> jarat_set(const vector<Jarat>& jaratok) {
    set<Jarat> setbe;
    for_each(jaratok.begin(), jaratok.end(), [&setbe] (const Jarat& jarat) {setbe.insert(jarat);});
    return setbe;
}

#ifndef TEST_BIRO
void test_jarat_set() {
  cout << endl << " --- test_jarat_set ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 32000);
  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Budapest","Berlin", 2000);
  jaratok.emplace_back("Tokio","Berlin", 200220);
  jaratok.emplace_back("Tokio","Budapest", 221000);

  set<Jarat> halmaz = jarat_set(jaratok);
  for(auto j : halmaz){
    cout << j << endl;
  }


  //kimenet
  //Budapest-Bagdad (86000 forint)
  //Budapest-Berlin (32000 forint)
  //Tokio-Berlin (200220 forint)
  //Tokio-Budapest (221000 forint)

}
#endif // TEST_BIRO
#endif // JARAT_SET



#ifdef MIN_AR

//IDE DOLGOZZ!!
void legolcsobb (const vector<Jarat>& jaratok, map<string, unsigned>& ki) {
    for_each(jaratok.begin(), jaratok.end(), [&jaratok, &ki] (const Jarat& jarat) {
        string kulcs = jarat.getHonnan() + jarat.getHova();
        try {
            if (ki.at(kulcs) > jarat.getAr()) {
                ki[kulcs] = jarat.getAr();
            }
        } catch (...) {
            ki[kulcs] = jarat.getAr();
        }

/*        if (ki[kulcs] > jarat.getAr()) {
            ki[kulcs] = jarat.getAr();
        }
        if (!ki[kulcs]) {
            ki[kulcs] = jarat.getAr();
        }*/
    });
}

#ifndef TEST_BIRO
void test_min_ar() {
  cout << endl << " --- test_legolcsobb ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);
  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Budapest","Berlin", 32000);
  jaratok.emplace_back("Tokio","Berlin", 200220);
  jaratok.emplace_back("Tokio","Budapest", 221000);
  jaratok.emplace_back("Budapest","Bagdad", 8600);
  jaratok.emplace_back("Tokio","Berlin", 200);
  jaratok.emplace_back("Tokio","Berlin", 100);

  map<string, unsigned> olcso_jaratok;
  legolcsobb(jaratok, olcso_jaratok);

  for(const auto& p : olcso_jaratok){
    cout << p.first << " : " << p.second << endl;
  }

  // kimenet
  //BudapestBagdad : 8600
  //BudapestBerlin : 2000
  //TokioBerlin : 100
  //TokioBudapest : 221000


}
#endif // TEST_BIRO
#endif // MIN_AR


#ifdef SZAMOL

//IDE DOLGOZZ!!
int szamol(const vector<Jarat>& jaratok, const string& varos) {
    return count_if(jaratok.begin(), jaratok.end(), [&varos] (const Jarat& jarat) {return jarat.getHova() == varos;});
}

#ifndef TEST_BIRO
void test_szamol() {
  cout << endl << " --- szamol ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);
  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Budapest","Berlin", 32000);
  jaratok.emplace_back("Tokio","Berlin", 200220);
  jaratok.emplace_back("Tokio","Budapest", 221000);
  jaratok.emplace_back("Budapest","Bagdad", 8600);
  jaratok.emplace_back("Tokio","Berlin", 200);


  cout << szamol(jaratok, "Berlin") << endl;

  jaratok.emplace_back("Tokio","Berlin", 100);
  jaratok.emplace_back("Berlin","Moszkva", 10340);

  cout << szamol(jaratok, "Berlin") << endl;

  // kimenet
  //4
  //5


}
#endif // TEST_BIRO
#endif // SZAMOL


#ifdef FILTER

//IDE DOLGOZZ!!
vector<Jarat> filter(const vector<Jarat>& jaratok, const string& varos1, const string& varos2) {
    vector<Jarat> utak;
    for_each(jaratok.begin(), jaratok.end(), [&] (const Jarat& jarat) {if(jarat.getHonnan() == varos1 && jarat.getHova() == varos2) {utak.emplace_back(jarat);}});
    for_each(jaratok.begin(), jaratok.end(), [&] (const Jarat& jarat) {if(jarat.getHonnan() == varos2 && jarat.getHova() == varos1) {utak.emplace_back(jarat);}});
    return utak;
}

#ifndef TEST_BIRO
void test_filter() {
  cout << endl << " --- filter ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);
  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Berlin","Budapest", 32000);
  jaratok.emplace_back("Berlin","Bagdad", 200220);
  jaratok.emplace_back("Berlin","Budapest", 52000);

  auto result = filter(jaratok, "Berlin", "Budapest");
  for(const auto& j : result){
    cout << j << endl;
  }
  cout << "----" << endl;

  result = filter(jaratok, "Budapest", "Berlin");
  for(const auto& j : result){
    cout << j << endl;
  }
  // kimenet
  //Berlin-Budapest (32000 forint)
  //Berlin-Budapest (52000 forint)
  //Budapest-Berlin (2000 forint)
  //----
  //Budapest-Berlin (2000 forint)
  //Berlin-Budapest (32000 forint)
  //Berlin-Budapest (52000 forint)



}
#endif // TEST_BIRO
#endif // FILTER


#ifdef FULLSORT

//IDE DOLGOZZ!!
void fullSort(vector<Jarat>& jaratok) {
    sort(jaratok.begin(), jaratok.end(), [](const Jarat& elso, const Jarat& masodik) {return elso.getAr() < masodik.getAr();});
}



#ifndef TEST_BIRO
void test_fullsort() {
  cout << endl << " --- fullSort ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);

  fullSort(jaratok);
  for(const auto& j : jaratok){
    cout << j << endl;
  }
  cout << endl;

  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Berlin","Budapest", 32000);
  jaratok.emplace_back("Berlin","Bagdad", 200220);
  jaratok.emplace_back("Berlin","Budapest", 52000);
  jaratok.emplace_back("Budapest","Bagdad", 76000);
  jaratok.emplace_back("Budapest","Washington", 1900);

  fullSort(jaratok);
  for(const auto& j : jaratok){
    cout << j << endl;
  }
  }
  // kimenet
  //Budapest-Berlin (2000 forint)
  //
  //Budapest-Washington (1900 forint)
  //Budapest-Berlin (2000 forint)
  //Berlin-Budapest (32000 forint)
  //Berlin-Budapest (52000 forint)
  //Budapest-Bagdad (76000 forint)
  //Budapest-Bagdad (86000 forint)
  //Berlin-Bagdad (200220 forint)

#endif // TEST_BIRO
#endif // FULLSORT

#ifdef FULLCOST

//IDE DOLGOZZ!!
unsigned fullCost (const vector<Jarat>& jaratok, unsigned limit) {
    return accumulate(jaratok.begin(), jaratok.end(),0, [&limit] (unsigned sum, const Jarat& jarat) {return sum + (jarat.getAr() < limit ? jarat.getAr() : 0);});
}

#ifndef TEST_BIRO
void test_fullcost() {
  cout << endl << " --- fullCost ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);

  cout << "Repjegyek összege 5000-es limittel:" << fullCost(jaratok, 5000) << endl;
  cout << "Repjegyek összege 1000-es limittel:" << fullCost(jaratok, 1000) << endl;

  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Berlin","Budapest", 32000);
  jaratok.emplace_back("Berlin","Bagdad", 200220);
  jaratok.emplace_back("Berlin","Budapest", 52000);
  jaratok.emplace_back("Budapest","Bagdad", 76000);
  jaratok.emplace_back("Budapest","Washington", 1900);

  cout << "Repjegyek összege 80000-es limittel:" << fullCost(jaratok, 80000) << endl;
}
// kimenet
//Repjegyek összege 5000-es limittel:2000
//Repjegyek összege 1000-es limittel:0
//Repjegyek összege 80000-es limittel:163900

#endif // TEST_BIRO
#endif // FULLCOST

#ifdef AKCIO

//IDE DOLGOZZ!!
vector<Jarat> akcio(const vector<Jarat>& jaratok, const unsigned szazalek) {
    if (szazalek > 100) {
        throw exception();
    }
    vector<Jarat> csokk = jaratok;
    transform(jaratok.begin(),jaratok.end(),csokk.begin(),[&szazalek] (const Jarat& jarat) {
        Jarat tmp = jarat;
        tmp.setAr((jarat.getAr() * (100- szazalek) )/ 100);
        return tmp;
    });

    return csokk;
}

#ifndef TEST_BIRO
void test_akcio() {
  cout << endl << " --- akcio ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);
  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Berlin","Budapest", 32000);
  jaratok.emplace_back("Berlin","Bagdad", 200220);
  jaratok.emplace_back("Berlin","Budapest", 52000);
  jaratok.emplace_back("Budapest","Bagdad", 76000);
  jaratok.emplace_back("Budapest","Washington", 1900);

  vector<Jarat> results = akcio(jaratok, 20);
  for(const auto& j : results){
    cout << j << endl;
  }
}
// kimenet
//Budapest-Berlin (1600 forint)
//Budapest-Bagdad (68800 forint)
//Berlin-Budapest (25600 forint)
//Berlin-Bagdad (160176 forint)
//Berlin-Budapest (41600 forint)
//Budapest-Bagdad (60800 forint)
//Budapest-Washington (1520 forint)

#endif // TEST_BIRO
#endif // AKCIO



#ifndef TEST_BIRO

int main() {
#ifdef JARAT_SET
  test_jarat_set();
#endif

#ifdef MIN_AR
  test_min_ar();
#endif

#ifdef SZAMOL
  test_szamol();
#endif

#ifdef FILTER
  test_filter();
#endif

#ifdef FULLSORT
  test_fullsort();
#endif

#ifdef FULLCOST
  test_fullcost();
#endif

#ifdef AKCIO
  test_akcio();
#endif

}
#endif
