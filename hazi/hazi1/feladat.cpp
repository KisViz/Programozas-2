#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;


/////////////////////////
//Ide dolgozz!!

int count_mM() {
    string s;
    cin >> s;
    int szaml = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'M' || s[i] == 'm') {
            szaml++;
        }
    }
    return szaml;
}

string repeater() {
    string s;
    int k;
    cin >> k >> s;

    if (k < 0) {
        return "hiba";
    }

    string uj;
    for (int i = 0; i < k; ++i) {
        uj += s;
    }
    return uj;
}

string multiplier(const unsigned int szam) {
    return to_string(szam * 3);
}

/*
Készíts egy függvényt, amely két string-et vár paraméterül. A string-ek egy-egy egész számot tartalmaznak.
A függvény visszatérési értéke az a szám lesz (sztringről egész számmá konvertálva), amelyiknek az értéke kisebb.
Amennyiben az egyik sztring üres vagy a konverzió nem elvégezhető, akkor a másik sztring számértéke legyen visszaadva.
Ha mindét sztring üres vagy nem konvertálható, akkor a visszatérési érték -999 legyen.
A függvény semmit se írjon ki a standard outputra!
*/

int strmin(const string elso, const string masodik) {

    bool elso_hibas = false, masodik_hibas = false;

    try {
        stoi(elso);
    } catch (exception){
        elso_hibas = true;
    }

    try {
        stoi(masodik);
    } catch (exception) {
        masodik_hibas = true;
    }

    if ( !elso_hibas && !masodik_hibas ) {
        if (stoi(elso) < stoi(masodik)) {
            return stoi(elso);
        } else {
            return stoi(masodik);
        }
    } else if (!elso_hibas) {
        return stoi(elso);
    } else if (!masodik_hibas) {
        return stoi(masodik);
    } else {
        return -999;
    }
}

////////////////////////

//=== Teszteles bekapcsolasa kikommentezessel
//#define TEST_count_mM
//#define TEST_repeater
//#define TEST_multiplier
#define TEST_strmin
//=== Teszteles bekapcsolas vege


/*
Készíts egy függvényt, amely beolvas egy tetszőleges hosszúságú sztringet a standard inputról, 
majd megszámolja hány darab m és M betű található benne.
A két betű darabszámának összege legyen a függvény visszatérési értéke. A függvény egész számmal térjen vissza.
A függvény semmit se írjon ki a standard outputra!
*/
void test_count_mM(){
  #if defined TEST_count_mM && !defined TEST_BIRO
  cout << "1-es feladat tesztelese" << endl;
  int m = count_mM();
  cout << "A beolvasott m es M karaketerk szama: " << m << endl;
  #endif 
}

/*
Készíts egy függvényt, amely beolvas előbb egy egész számot, utána pedig egy tetszőleges hosszúságú sztringet a standard inputról. 
A függvény visszatérési értéke egy sztring legyen, amelyben annyiszor van megismételve (szóköz vagy egyéb elválasztójelek nélkül) 
a beolvasott sztring, amennyi a beolvasott egész értéke.
Ha a beolvasott szám negatív a visszaadott sztring értéke "hiba" legyen. 
A függvény semmit se írjon ki a standard outputra!
*/
void test_repeater(){
  #if defined TEST_repeater && !defined TEST_BIRO
  cout << "2-es feladat tesztelese" << endl;
  string reps = repeater();
  cout << reps << endl;
  #endif
}

/*
Készíts egy függvényt, amelynek paramétere egy előjel nélküli egész szám. 
A függvény visszatérési értéke egy sztring legyen, amelyben a paraméterül kapott szám 3-szorosa van sztringgé konvertálva.
A függvény semmit se írjon ki a standard outputra!
*/
void test_multiplier(){
  #if defined TEST_multiplier && !defined TEST_BIRO
  cout << "3-as feladat tesztelese" << endl;
  string multi1 = multiplier(8);
  assert(multi1 == "24");
  #endif
}

/*
Készíts egy függvényt, amely két string-et vár paraméterül. A string-ek egy-egy egész számot tartalmaznak. 
A függvény visszatérési értéke az a szám lesz (sztringről egész számmá konvertálva), amelyiknek az értéke kisebb. 
Amennyiben az egyik sztring üres vagy a konverzió nem elvégezhető, akkor a másik sztring számértéke legyen visszaadva. 
Ha mindét sztring üres vagy nem konvertálható, akkor a visszatérési érték -999 legyen. 
A függvény semmit se írjon ki a standard outputra!
*/
void test_strmin(){
  #if defined TEST_strmin && !defined TEST_BIRO
  cout << "4-es feladat tesztelese" << endl;
  int min = strmin("", "");
  assert(min == -999);
  min = strmin("Harry", "Potter");
  assert(min == -999);
  min = strmin("-5asd2", "-3");
  assert(min == -3);
  #endif
  
}

int main(){

  test_count_mM();
  test_repeater();
  test_multiplier();
  test_strmin();

  return 0;
}
