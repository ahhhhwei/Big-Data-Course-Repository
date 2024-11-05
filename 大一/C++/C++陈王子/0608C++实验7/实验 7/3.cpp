#include <iostream>
#include <string>
using namespace std;

class Vehicle {
public:
    int doors;
    int cylinders;
    int transmissionType;
    string color;
    double fuelLevel;

    Vehicle(int _doors, int _cylinders, int _transmissionType, string _color, double _fuelLevel) {
        doors = _doors;
        cylinders = _cylinders;
        transmissionType = _transmissionType;
        color = _color;
        fuelLevel = _fuelLevel;
    }

    virtual void print() {
        cout << "Vehicle" << endl;
        cout << "\tNumber of doors: " << doors << endl;
        cout << "\tNumber of cylinders: " << cylinders << endl;
        cout << "\tTransmission type: " << transmissionType << endl;
        cout << "\tColor: " << color << endl;
        cout << "\tFuel level: " << fuelLevel << endl;
    }
};

class Taxi : public Vehicle {
public:
    bool passenger;

    Taxi(int _doors, int _cylinders, int _transmissionType, string _color, double _fuelLevel, bool _passenger) : Vehicle(_doors, _cylinders, _transmissionType, _color, _fuelLevel) {
        passenger = _passenger;
    }

    void print() override {
        cout << "Taxi" << endl;
        cout << "\tNumber of doors: " << doors << endl;
        cout << "\tNumber of cylinders: " << cylinders << endl;
        cout << "\tTransmission type: " << transmissionType << endl;
        cout << "\tColor: " << color << endl;
        cout << "\tFuel level: " << fuelLevel << endl;
        if (passenger) {
            cout << "\tThe taxi has passengers." << endl;
        }
        else {
            cout << "\tThe taxi has no passengers." << endl;
        }
    }
};

class Truck : public Vehicle {
public:
    bool cargo;

    Truck(int _doors, int _cylinders, int _transmissionType, string _color, double _fuelLevel, bool _cargo) : Vehicle(_doors, _cylinders, _transmissionType, _color, _fuelLevel) {
        cargo = _cargo;
    }

    void print() override {
        cout << "Truck" << endl;
        cout << "\tNumber of doors: " << doors << endl;
        cout << "\tNumber of cylinders: " << cylinders << endl;
        cout << "\tTransmission type: " << transmissionType << endl;
        cout << "\tColor: " << color << endl;
        cout << "\tFuel level: " << fuelLevel << endl;
        if (cargo) {
            cout << "\tThe truck is carrying cargo." << endl;
        }
        else {
            cout << "\tThe truck is not carrying cargo." << endl;
        }
    }
};

int main() {
    Vehicle v(2, 6, 3, "blue", 14.6);
    v.print();

    Taxi t(4, 6, 5, "yellow", 3.3, false);
    t.print();

    Truck tr(2, 16, 8, "black", 7.54, true);
    tr.print();

    return 0;
}
