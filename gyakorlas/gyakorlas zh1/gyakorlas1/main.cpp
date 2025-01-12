#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

#ifndef TEST_BIRO
#  define STL_ARRAY_TO_SET
#  define STL_SUMMARY
#  define STL_VECTOR_UPDATE
#endif // TEST_BIRO


#ifdef STL_ARRAY_TO_SET

//IDE DOLGOZZ!!

int array_to_set(const unsigned arr[], const unsigned len, set<unsigned>& halm) {
    int szaml = 0;
    for (int i = 0; i < len; ++i) {
        if (halm.find(arr[i]) != halm.end()) { //ezt egyszerubb lenne .contains()-zal, de c++17 -et inditottam es csak c++20 -tol van:(
            szaml += arr[i];                      //de haj jol latom biron is c++17 van
//            cout << arr[i] <<endl;
            //ha meg nincs benne akkor a halmaz vegere mutato iteratort kapunk, egyebkent egy valid iteratort, ezert kell ellenorizni a .end() -et
        } else {
            halm.insert(arr[i]);
        }
    }

    return szaml;
}


// ---------- test ----------
#ifndef TEST_BIRO
void test_array_to_set() {
  unsigned input[] = {2,4,5, 42};
  set<unsigned> output;
  unsigned result = array_to_set(input, 4, output);
  cout << result << endl;
  //set tartalma: 2, 4, 5
}
#endif // TEST_BIRO
#endif // STL_ARRAY_TO_SET


#ifdef STL_SUMMARY

//IDE DOLGOZZ!!

map<unsigned, unsigned> summary(const map<string, unsigned> terkep) {

    map<unsigned, unsigned> jegyek;
    for (int i = 1; i < 6; ++i) {
        jegyek[i] = 0;
    }

    for (auto& elem : terkep) {
        jegyek[elem.second]++;
    }

    return jegyek;
}


// ---------- test ----------
#ifndef TEST_BIRO
void test_summary() {
  map<std::string, unsigned> mapOfMarks = {
        {"Kis Ferenc",2},
        {"Nagy Ferenc",4},
        {"Kozepes Ferenc",2}
    };
  map<unsigned, unsigned> stat = summary(mapOfMarks);
  cout << stat.size() << endl;

    /*for (auto& elem : stat) {
        cout << elem.first << ": " << elem.second << endl;
    }*/
  //stat tartalma: 1: 0, 2: 2, 3: 0, 4: 1, 5: 0
}
#endif // TEST_BIRO
#endif // STL_SUMMARY


#ifdef STL_VECTOR_UPDATE

struct Hallgato{
  string nev;
  unsigned jegy;
};

//IDE DOLGOZZ!!

void vector_update(vector<Hallgato>& hallgatok, Hallgato hallgato) {

    for (auto& elem : hallgatok) {
        if (elem.nev == hallgato.nev) {
            elem.jegy = hallgato.jegy;
            return;
        }
    }
    hallgatok.push_back(hallgato);
}


// ---------- test ----------
#ifndef TEST_BIRO
void test_vector_update() {
    vector<Hallgato> vec = {
        {"Kis Ferenc",2},
        {"Nagy Ferenc",4},
        {"Kozepes Ferenc",2}
    };
    Hallgato h = {"Kozepes Ferenc", 5};
    vector_update(vec, h);
    cout << "Uj jegy:" << vec[2].jegy << endl;
}
#endif // TEST_BIRO
#endif // STL_VECTOR_UPDATE


#ifndef TEST_BIRO
int main() {

#ifdef STL_ARRAY_TO_SET
    test_array_to_set();
#endif //STL_ARRAY_TO_SET

#ifdef STL_SUMMARY
    test_summary();
#endif //STL_SUMMARY

#ifdef STL_VECTOR_UPDATE
    test_vector_update();
#endif //STL_VECTOR_UPDATE

    return 0;
}
#endif // TEST_BIRO