#include "iostream"
#include "map"

using namespace std;

class Safe {
    unsigned szam;
    string tulajNev;
    unsigned galleonSzam;

public:
    Safe(int szam, const string &tulajNev, int galleonSzam) : szam(szam), tulajNev(tulajNev),
                                                              galleonSzam(galleonSzam) {}

    Safe() = default;

    Safe &operator+=(const unsigned osszeg) {
        galleonSzam += osszeg;
        return *this;
    }

    Safe &operator-=(const unsigned osszeg) {
        if (osszeg <= galleonSzam) {
            galleonSzam -= osszeg;
            cout << "Sikeres felvétel!";
        } else {
            cout << "Nincs elegendő pénz!";
        }
        return *this;
    }

    Safe &operator<<(Safe &safe) {
        if (safe.galleonSzam >= 10) {
            safe.galleonSzam -= 10;
            this->galleonSzam += 10;
            cout << "10 galleon átutalva!";
        } else {
            safe.galleonSzam -= 10;
        }

        return *this;
    }

    void print() const {
        cout << "Tulajdonosa:" << tulajNev << ",száma:" << szam << ",egyenleg:" << galleonSzam << endl;

    }

    unsigned int getSzam() const {
        return szam;
    }

    const string &getTulajNev() const {
        return tulajNev;
    }

    unsigned int getGalleonSzam() const {
        return galleonSzam;
    }
};

class Gringotts {
    map<unsigned, Safe> szefek;

public:
    unsigned getSize() const {
        return szefek.size();
    }

    Gringotts& operator+=(const Safe& safe) {
        szefek[safe.getGalleonSzam()] = safe;
        return *this;
    }

    void printStatus() const {
        for (auto& elem : szefek) {
            elem.second.print();
        }
    }

    void withdraw(const unsigned szam,const string& tulaj,const unsigned osszeg) {
        for (auto& elem : szefek) {
            if (elem.first == szam && elem.second.getTulajNev() == tulaj) {
                elem.second -= osszeg;
                return;
            }
        }

        cout << "Hibás adatok!";
    }
};


int main() {
    // Tesztesetek a Safe osztályhoz
    Safe szef1(1, "Harry", 100);  // Széf száma: 1, tulajdonos: Harry, galleonok: 100
    Safe szef2(2, "Ron", 50);     // Széf száma: 2, tulajdonos: Ron, galleonok: 50

    // Pénz hozzáadása
    szef1 += 50;   // Harry széfje most 150 galleon lesz
    szef1.print(); // Tulajdonosa:Harry,száma:1,egyenleg:150

    // Pénz levétele
    szef1 -= 100;  // Harry széfje 50 galleon lesz
    szef1.print(); // Tulajdonosa:Harry,száma:1,egyenleg:50

    // Sikertelen levétel
    szef1 -= 100;  // "Nincs elegendő pénz!"
    szef1.print(); // Tulajdonosa:Harry,száma:1,egyenleg:50

    // Pénz átutalása Ron széfjére
    szef1 << szef2 <<szef2;  // 10 galleon átutalva Harry széfjéről Ron széfjére
    szef1.print();   // Tulajdonosa:Harry,száma:1,egyenleg:40
    szef2.print();   // Tulajdonosa:Ron,száma:2,egyenleg:60

    // Tesztesetek a Gringotts osztályhoz
    Gringotts bank;

    // Széfek hozzáadása a bankhoz
    bank += szef1;
    bank += szef2;

    // Bank mérete
    cout << "Aktív széfek száma: " << bank.getSize() << endl; // 2

    // Bank státuszának kiírása
    bank.printStatus();
    // Tulajdonosa:Harry,száma:1,egyenleg:40
    // Tulajdonosa:Ron,száma:2,egyenleg:60

    // Pénz levétele egy széf száma és tulajdonos alapján
    bank.withdraw(1, "Harry", 30); // Sikeres felvétel!
    bank.withdraw(2, "Ron", 100);  // Nincs elegendő pénz!

    // Frissített státusz
    bank.printStatus();
    // Tulajdonosa:Harry,száma:1,egyenleg:10
    // Tulajdonosa:Ron,száma:2,egyenleg:60

    return 0;
}