#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>

using namespace std;

class Tehen{
    string nev;
    unsigned tomeg;
public:
    const string &getNev() const {
        return nev;
    }

    void setNev(const string &nev) {
        Tehen::nev = nev;
    }

    unsigned int getTomeg() const {
        return tomeg;
    }

    void setTomeg(unsigned int tomeg) {
        Tehen::tomeg = tomeg;
    }

    void legel(){
        cout << nev << " legel" << endl;
        tomeg += 5;
    }

    Tehen(const string &nev, unsigned int tomeg) : nev(nev), tomeg(tomeg) {}


};

void print(const Tehen& t){
    cout << t.getNev() << " " << t.getTomeg() << endl;
}

void legeltet(Tehen& t) {
    if (t.getTomeg() < 20) {
        t.legel();
    }
}

/*
int main() {

    std::string hibauzenet = "A tehen tul nehez: ";

    vector<Tehen> tehenek = {{"Riska", 10}, {"Guszti", 5}, {"Borcsa", 30}, {"Emanuel", 24}};
    vector<int> szamok = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto print_lambda = [](const Tehen& t) -> void {
        cout << t.getNev() << " " << t.getTomeg() << endl;
    };

    auto legeltet_lambda = [&hibauzenet](Tehen& t) -> void {
        if (t.getTomeg() < 20) {
            t.legel();
        } else {
            cout << hibauzenet << t.getNev() << " " << t.getTomeg() << endl;
        }
    };

    for_each(tehenek.begin(), tehenek.end(), print_lambda);
    cout << endl;
    for_each(tehenek.begin(), tehenek.end(), legeltet_lambda);
    cout << endl;
    // for_each(tehenek.cbegin(), tehenek.cend(), print);
    for_each(tehenek.cbegin(), tehenek.cend(), print_lambda);

    cout << endl;
    print_lambda(Tehen("Jozsi Blazsi", 43));

    auto sum = accumulate (szamok.begin(), szamok.end(), 0);

    cout << "a szamok osszege: " << sum << endl;

    auto summer = [](unsigned szam, const Tehen& t) -> unsigned {
        return szam + t.getTomeg();
    };

    auto tehentomeg = accumulate(tehenek.begin(), tehenek.end(), 0, summer);
    cout << "tehentomeg: " << tehentomeg << endl;

    auto keres = [](const Tehen &tehen)->bool {
        return tehen.getNev() == "Guszti";
    };
    auto elem = find_if(tehenek.begin(), tehenek.end(), keres);
    if (elem != tehenek.end()) {
        cout << elem->getNev();
    }

    //ez itt kaga:(
    // cout << endl;
    // for_each(tehenek.cbegin(), tehenek.cend(),[](const Tehen &tehen) {cout << tehen.getNev() << " " << tehen.getTomeg() << endl;});
    // cout << endl;
    // for_each(tehenek.begin(), tehenek.end(),[](Tehen &tehen) {tehen.legel();});
    // cout << endl;
    // for_each(tehenek.cbegin(), tehenek.cend(),[](const Tehen &tehen) {cout << tehen.getNev() << " " << tehen.getTomeg() << endl;});

    return 0;
}

*/
