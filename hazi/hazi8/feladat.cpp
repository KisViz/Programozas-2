#include <iostream>
#include <cassert>

using std::string;

/////////////////////////
//Ide dolgozz!!

class VilagitoDisz {
    unsigned fenyesseg;
    bool bekapcsolva;

public:
    explicit VilagitoDisz(unsigned int fenyesseg = 0) : fenyesseg(fenyesseg), bekapcsolva(false) {}

    unsigned int get_fenyesseg() const {
        return bekapcsolva ? fenyesseg : 0;
    }

    bool is_bekapcsolva() const {
        return bekapcsolva;
    }

    VilagitoDisz& operator++() {
        bekapcsolva = true;
        return *this;
    }

    VilagitoDisz& operator--() {
        bekapcsolva = false;
        return *this;
    }
};

class KisKaracsonyfa {
    string tipus;
    VilagitoDisz *csucsdisz = nullptr;
public:
    explicit KisKaracsonyfa(const string &tipus = "luc") : tipus(tipus) {}

    const string &get_fa_tipus() const {
        return tipus;
    }

    VilagitoDisz *get_csucs_disz() const {
        return csucsdisz;
    }

    void disz_felhelyezese(const VilagitoDisz& uj) {
        delete csucsdisz;
        csucsdisz = new VilagitoDisz(uj);
    }

    void bekapcsol() {
        if (csucsdisz) {
            ++(*csucsdisz);
        }
    }

    void kikapcsol() {
        if (csucsdisz) {
            --(*csucsdisz);
        }
    }

    unsigned get_fenyesseg() const {
        return csucsdisz ? csucsdisz->get_fenyesseg() : 0;
    }

    KisKaracsonyfa(const KisKaracsonyfa &other) {
        this->tipus = other.tipus;
        this->csucsdisz = new VilagitoDisz(*other.csucsdisz);
    }

    ~KisKaracsonyfa() {
        delete csucsdisz;
    }

    KisKaracsonyfa& operator= (const KisKaracsonyfa& other) {
        if (&other == this) {
            return *this;
        }

        this->tipus = other.tipus;
        delete csucsdisz;
        this->csucsdisz = new VilagitoDisz(*other.csucsdisz);

        return *this;
    }
};

////////////////////////

//=== Teszteles bekapcsolasa kikommentezessel
#define TEST_vilagitodisz
#define TEST_pre_operators
#define TEST_kiskaracsonyfa
#define TEST_felhelyez
#define TEST_kibekapcsol
#define TEST_get_fenyesseg
#define TEST_masolo_ctor
#define TEST_ertekadas_operator
//=== Teszteles bekapcsolas vege

/*
Készíts egy VilagitoDisz nevű osztályt, mely egy karácsonyfa díszítésére alkalmas! Adattagok:
- fenyesseg: a dísz fényessége (unsigned)
- bekapcsolva: a dísz állapota, világít-e vagy sem (bool)

Készítsd el a VilagitoDisz konstruktorát is, mely a fényességet várja és állítja be.
Default konstruktorként (default paraméter érték) a 0 értéket állítsa be! A bekapcsolva adattag default értéke false.
*/
void test_vilagitodisz(){
#if defined TEST_vilagitodisz && !defined TEST_BIRO
    const VilagitoDisz vd;
    assert(vd.get_fenyesseg() == 0);
    assert(!vd.is_bekapcsolva());

    const VilagitoDisz vd2(50);
    assert(!vd2.is_bekapcsolva());
#endif

}


/*
Definiáld felül a VilagitoDisz pre ++ és pre -- operátorát!
A ++ operátor kapcsolja be a világítást, a -- operátor kapcsolja ki azt.
Az operátorok pre verzióként működjenek, azaz a módosított értékkel az eredeti objektumot adják vissza!
*/
void test_pre_operators(){
#if defined TEST_pre_operators && !defined TEST_BIRO
    VilagitoDisz vd;
    ++vd;
    assert(vd.is_bekapcsolva());
    --vd;
    assert(!vd.is_bekapcsolva());
#endif

}

/*
Készíts egy KisKaracsonyfa nevű osztályt! Adattagok:
- csucs_disz: a KisKarácsonyfára helyezhető egyetlen dísz (VilagitoDisz*)  & KisKarácsonyfára helyezhető egyetlen dísz   \\ \hline
- fa_tipus: a fa típusa  &   std::string   & A fa típusa                                 \\ \hline


Valósítsd meg a KisKaracsonyfa konstruktorát, mely a fa típusát várja paraméterként!
Default paraméter értékként a "luc" értéket add meg!
A csucs_disz paramétert nullptr -el inicializálja!
*/
void test_kiskaracsonyfa(){
#if defined TEST_kiskaracsonyfa && !defined TEST_BIRO
    KisKaracsonyfa fa;
    assert(fa.get_fa_tipus() == "luc");
    assert(fa.get_csucs_disz() == nullptr);

    KisKaracsonyfa fa2("cedrus");
    assert(fa2.get_fa_tipus() == "cedrus");
    assert(fa2.get_csucs_disz() == nullptr);
#endif
}


/*
Írj egy disz_felhelyezese metódust, mely egy VilagitoDisz-t vár paraméterben, figyelj annak pontos típusára!
A metódus törölje a fán lévő díszt (ha van) és foglaljon dinamikusan egy új díszt, lemásolva a paraméterben kapottat.
A metódus ne térjen vissza semmivel.
*/
void test_felhelyez(){
#if defined TEST_felhelyez && !defined TEST_BIRO
    KisKaracsonyfa fa;
    {
        const VilagitoDisz vd;
        fa.disz_felhelyezese(vd);
        assert(fa.get_csucs_disz()->get_fenyesseg() == 0);
    }
    {
        VilagitoDisz vd2(20);
        ++vd2;
        fa.disz_felhelyezese(vd2);
        assert(fa.get_csucs_disz()->get_fenyesseg() == 20);
    }
#endif

}


/*
Legyen egy void bekapcsol() és egy void kikapcsol() metódus, melyek rendre be vagy kikapcsolják a csúcsdíszt, ha van a fán!
*/
void test_kibekapcsol(){
#if defined TEST_kibekapcsol && !defined TEST_BIRO
    KisKaracsonyfa fa;
    const VilagitoDisz vd2(20);

    fa.disz_felhelyezese(vd2);
    fa.bekapcsol();
    assert(fa.get_csucs_disz()->is_bekapcsolva());

    fa.kikapcsol();
    assert(!(fa.get_csucs_disz()->is_bekapcsolva()));
#endif
}


/*
Legyen egy get_fenyesseg metódus, mely a fa aktuális fényességét határozza meg!
Ha nincsen csúcsdísz a fán, adjon vissza nullát, különben a dísz fényességét!
Visszatérési típusát a csúcsdísz metódusához igazítsd! (Egyezzen meg vele!)
*/
void test_get_fenyesseg(){
#if defined TEST_get_fenyesseg && !defined TEST_BIRO
    KisKaracsonyfa fa;
    VilagitoDisz vd2(20);
    ++vd2; //bekapcsol
    fa.disz_felhelyezese(vd2);
    assert(fa.get_fenyesseg() == 20);
#endif
}


/*
Valósítsd meg a KisKaracsonyfa másoló konstruktorát, mely az adattagokat lemásolja!
Figyelj a dinamikusan foglalt adattagok helyes kezelésére!
*/
void test_masolo_ctor(){
#if defined TEST_masolo_ctor && !defined TEST_BIRO
    KisKaracsonyfa fa;
    VilagitoDisz vd2(20);
    ++vd2; //bekapcsol
    fa.disz_felhelyezese(vd2);
    assert(fa.get_fenyesseg() == 20);
    {
        KisKaracsonyfa fa2(fa);
        assert(fa.get_csucs_disz()->get_fenyesseg() == 20);
    }
    assert(fa.get_csucs_disz()->get_fenyesseg() == 20);
#endif
}


/*
Valósítsd meg a értékadás (assignment) operátort!
Az operátor kezelje a lehetséges hibákat és hasonlóan működjön a másoló konstruktorhoz!
Figyelj a dinamikusan foglalt adattagok helyes kezelésére!
*/
void test_ertekadas_operator(){
#if defined TEST_ertekadas_operator && !defined TEST_BIRO
    KisKaracsonyfa fa1("cedrus");
    {
        KisKaracsonyfa fa2;
        VilagitoDisz vd1(20), vd2(30);
        ++vd1; //bekapcsol
        ++vd2; //bekapcsol
        fa1.disz_felhelyezese(vd1);
        fa2.disz_felhelyezese(vd2);
        fa1=fa2;
    }
    assert(fa1.get_csucs_disz()->get_fenyesseg() == 30);
    assert(fa1.get_fa_tipus() == "luc");
#endif
}



int main(){
    test_vilagitodisz();
    test_pre_operators();
    test_kiskaracsonyfa();
    test_felhelyez();
    test_kibekapcsol();
    test_get_fenyesseg();
    test_masolo_ctor();
    test_ertekadas_operator();
    return 0;

}
