#include <iostream>
#include "vector"
#include "set"
#include "algorithm"

#include "functional"

using namespace std;

#ifndef MY_BADGE
/**
 * Badge osztály, ami egy elért teljesítményt jelent.
 * Van címe, mely a teljesítmény típusára utal és fokozata, mely 0 - 4 lehet.
 */
class Badge {
    string cim;
    unsigned fokozat;
public:
    /**
     * Konstruktor.
     * @param cim a badge címe
     */
    Badge( const string & cim, unsigned fokozat = 0 ) : cim ( cim ), fokozat( fokozat ) {}

    /**
     * Default constructor a tárolókhoz.
     */
    Badge() = default;

    /**
     * Visszaadja a Badge címét.
     * @return a string-ként a badge címe
     */
    const string & getCim() const { return cim; }

    /**
     * Visszaadja a Badge fokozatát.
     * @return fokozat unsigned-ként.
     */
    unsigned getFokozat() const { return fokozat; }

    /**
     * Fokozat nnövelése maximum 4-ig.
     * @return Badge referencia az objektumra.
     */
    Badge& operator++() {
        if ( fokozat <= 3 ) { ++fokozat; }
        return *this;
    }
};
#endif

class Pokemon {
    string _nev;
    unsigned _tamadas;
    unsigned _vedekezes;
public:
    Pokemon(const string & nev // poke neve
            , unsigned tamadas = 10 // poke tamadasi ereje
            , unsigned vedekezes = 10) // poke vedelmi ereje
            : _nev(nev)
            , _tamadas(tamadas)
            , _vedekezes(vedekezes) {}

    /**
     * Visszaadja a Pokemon nevét.
     * @return a Pokemon neve stringként.
    */
    operator string () const { return _nev; }

    virtual /**
     * Getter a támadási erőre
     * @return A támadási erő értéke
     */
    unsigned getTamadas() const { return _tamadas; }

    /**
     * Getter a védekéezési erőre
     * @return A védekéezési erő értéke
     */
    unsigned getVedekezes() const { return _vedekezes; }

    /**
     * Eldönti, hogy a pokemont legyőzi-e az adott értékű támadás.
     * @param tamadasiEro a támadás ereje
     * @return true, ha a pokemonnál erősebb a támadás, egyébként false
     */
    virtual bool operator < ( unsigned tamadasiEro ) const { return _vedekezes < tamadasiEro; }

};

class PokeLabda {
public:
    unsigned _tamadasiEro;
public:
    PokeLabda( unsigned tamadasiEro ) : _tamadasiEro( tamadasiEro ) {}

    /**
     * Megtámadja a pokemont. Ha a támadás ereje nagyobb, mint a pokemon védelme, akkor a pokemon legyőzésre kerül.
     * @param p a megtámadott pokemon
     * @return a legyőzött pokemon
     * @throws "Edzeni kell!", ha a pokemon túl erős
     */
    bool operator () ( const Pokemon p ) const {

        if ( p < _tamadasiEro ) { return true; }

        throw string("Edzeni kell!");
    }

    /**
     * Visszaadja, hogy a pokelabda gyengébb-e egy másiknál.
     * @param labda a másik pokelabda
     * @return true, ha a pokelabda gyengébb, egyébként false
     */
    bool operator < ( const PokeLabda & labda ) const { return _tamadasiEro < labda._tamadasiEro; }
};

// IDE DOLGOZZ!!!
class FenyesPokemon: public Pokemon {
protected:
    unsigned fenyero;
public:
    FenyesPokemon(const string &nev, unsigned int tamadas, unsigned int vedekezes, unsigned int fenyero) : Pokemon(nev,
                                                                                                                   tamadas,
                                                                                                                   vedekezes),
                                                                                                           fenyero(fenyero) {}
    bool operator < (unsigned tamadasiEro) const override{
        tamadasiEro-=fenyero;
        return this->getVedekezes() < tamadasiEro;
    }
};

class PokeTrainer {
protected:
    set<PokeLabda> labdak;
    vector<reference_wrapper<Pokemon>> pokemonok;
    vector<Badge> badgek;

public:
    PokeTrainer() = default;

    PokeTrainer& operator+=(const PokeLabda& pokeLabda) {
        labdak.insert(pokeLabda);
        return *this;
    }

    PokeTrainer& operator>> (const Pokemon& pokemon) {
        for(auto& labda : labdak) {
            try {
                if (labda(pokemon)) {
                    cout << "Elkapva: " + pokemon.operator string() << endl;
                    pokemonok.push_back(const_cast<Pokemon&>(pokemon));
                    break;
                }
            } catch (string& e) {
                cout << e << endl;
            }
        }
        return *this;
    }

    int veszit(const unsigned tamadas) const {
        return count_if(pokemonok.begin(), pokemonok.end(), [&tamadas] (auto& pokemon) {
            return pokemon.get() < tamadas;
        });
    }

    void badge(const vector<Badge>& ujak) {
        badgek = ujak;
        transform(ujak.begin(), ujak.end(), badgek.begin(), [](Badge uj){return ++uj;});
    }

    void badgeLista() const {
        cout << "Badgek:" << endl;
        for_each(badgek.begin(), badgek.end(), [](const auto& b){cout << b.getCim() << " " << b.getFokozat() << endl;});
    }

    void maxBadge() const {
        auto leg = max_element(badgek.begin(), badgek.end(), [](const auto& a, const auto& b){
            return a.getFokozat() < b.getFokozat();
        });
        cout << leg->getFokozat() << endl;
    }
};


/*
int main() {
//    PokeLabda p1(10);
//    PokeLabda p2(20);
//
//    PokeTrainer pt1;
//    pt1 += p1 ;
//    pt1 += p2;
//
//    Pokemon pk1("pelda");
//
//    pt1 >> pk1;

    return 0; // Ezt most tartsd meg!
}*/
