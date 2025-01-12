#include <iostream>

using namespace std;

class Plane {
private:
    string call_sign;
    bool is_prioritized;
    unsigned fuel_amount;

public:

    Plane(): call_sign("AIR-123"), is_prioritized(false), fuel_amount(1600) {}

    Plane(const string &callSign, bool isPrioritized, unsigned int fuelAmount) : call_sign(callSign),
                                                                                 is_prioritized(isPrioritized),
                                                                                 fuel_amount(fuelAmount) {}

    const string &getCallSign() const {
        return call_sign;
    }

    void setCallSign(const string &callSign) {
        call_sign = callSign;
    }

    bool isPrioritized() const {
        return is_prioritized;
    }

    void setIsPrioritized(bool isPrioritized) {
        is_prioritized = isPrioritized;
    }

    unsigned int getFuelAmount() const {
        return fuel_amount;
    }

    void setFuelAmount(unsigned int fuelAmount) {
        fuel_amount = fuelAmount;
    }

    string to_string() const {
        return "Plane: "+ call_sign + ", take off=" + (is_prioritized ? "priority" : "normal")  + ", fuel=" + std::to_string(fuel_amount) + "gal;";
    }
};

class Airport {
private:
    string iata_code;
    Plane takeoff_schedule[5];
    int takeoff_index;

public:

    explicit Airport(const string &iataCode = "LHBP") : iata_code(iataCode), takeoff_index(0){}

    const string &getIataCode() const {
        return iata_code;
    }

    void setIataCode(const string &iataCode) {
        iata_code = iataCode;
    }

    int getTakeoffIndex() const {
        return takeoff_index;
    }

    void setTakeoffIndex(int takeoffIndex) {
        takeoff_index = takeoffIndex;
    }

    Airport& operator += (const Plane& repulo) {
        if (takeoff_index < 5) {
//            cout << "belep1" << endl;

            if (repulo.isPrioritized()) {
                for (int i = 0; i < takeoff_index; ++i) {
                    takeoff_schedule[i + 1] = takeoff_schedule[i];
                }

                takeoff_index++;
                takeoff_schedule[0] = repulo;
            } else {
//                cout << "belep2" << endl;

                takeoff_schedule[takeoff_index] = repulo;
                takeoff_index++;
            }
        } else {
            throw std::range_error("Nincs tobb hely, vagy nem letezo repulogep!");
        }

        return *this;
    }

    string print_takeoff_schedule() const {
        string uj = "Takeoff schedule for " + iata_code + ":\n";
        for (int i = 0; i < takeoff_index; ++i) {
            uj += to_string(i + 1) + ") " + takeoff_schedule[i].to_string() + "\n";
        }

        return uj.substr(0,uj.length()-1);;
    }
};

/*int main() {

    Plane p1;
    Plane p2 = Plane("alma", false, 3);
    Plane p3 = Plane("beka", false, 3232);
    Plane p4 = Plane("dw", true, 666);
    Plane p5 = Plane("nem", false, 34);

    Airport airport;

    airport += p1;
    airport += p2;
    airport += p3;
    airport += p4;
    airport += p5;
//    airport += p1;


    cout << airport.print_takeoff_schedule() << endl;

    return 0;
}*/
