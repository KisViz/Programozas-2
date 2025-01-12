#include "iostream"
#include "vector"
#include "algorithm"
#include "numeric"

using namespace std;

int main() {
    vector<int> v_int = {1,3,6,56,85,1,22,12,56,3};

    for_each(v_int.begin(),v_int.end(), [](int elem) { cout<< elem << " "; });
    cout << endl << endl;

    int szaml = count_if(v_int.begin(), v_int.end(),[] (int elem) { return elem > 50; });
    cout << szaml << " " << count_if(v_int.begin(), v_int.end(),[&szaml] (int elem) { return elem > 50; }) << endl;
    cout << endl;


    auto iter = remove_if(v_int.begin(), v_int.end(), [] (int elem) { return elem < 5; });
    //nem torli egybol, csak a vegere rakra a rosszakat!!!!!
    for_each(v_int.begin(),v_int.end(), [](int elem) { cout<< elem << " "; });
    cout << endl;
    for_each(v_int.begin(), iter, [](int elem) { cout<< elem << " "; });
    cout << endl;
    v_int.erase(iter, v_int.end()); //igy torlod
    for_each(v_int.begin(),v_int.end(), [](int elem) { cout<< elem << " "; });
    cout << endl << endl;

    //az elso elofordulast adj vissza iteratorban
    iter = find_if(v_int.begin(), v_int.end(), [] (int elem) {return elem == 56;});
    cout << *iter << endl << endl;

    vector<int> masolat;
    copy_if(v_int.begin(),v_int.end(), back_inserter(masolat), [] (int elem) {return elem > 50;});
    for_each(masolat.begin(), masolat.end(), [] (int elem) {cout <<elem << " ";});
    cout << endl << endl;

    vector<int> masik;
    masik = v_int;
    transform(v_int.begin(), v_int.end(), masik.begin(), [](int elem) {elem++; return elem;});
    for_each(masik.begin(), masik.end(), [] (int elem) {cout <<elem << " ";});
    cout << endl << endl;

    iter = max_element(v_int.begin(), v_int.end(), [](int elem1, int elem2) {return elem1 < elem2;});
    cout << *iter << endl << endl;

    //numeric-ban
    int ossz = accumulate(v_int.begin(), v_int.end(), 0);
    cout << ossz << endl << endl;

    return 0;
};