#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum class VehicleSize { Motorcycle, Compact, Large };

class ParkingSpot;

class Vehicle {
protected:
    vector<ParkingSpot*> parkingSpots;
    string licensePlate;
    int spotsNeeded;
    VehicleSize size;

public:
    Vehicle(string plate, int spots, VehicleSize sz)
        : licensePlate(plate), spotsNeeded(spots), size(sz) {}

    virtual ~Vehicle() {}

    int getSpotsNeeded() const {
        return spotsNeeded;
    }

    VehicleSize getSize() const {
        return size;
    }

    void parkInSpot(ParkingSpot* spot) {
        parkingSpots.push_back(spot);
    }

    void clearSpots();

    virtual bool canFitInSpot(ParkingSpot* spot) const = 0;
};

class Bus : public Vehicle {
public:
    Bus(string plate) : Vehicle(plate, 5, VehicleSize::Large) {}

    bool canFitInSpot(ParkingSpot* spot) const override;
};

class Car : public Vehicle {
public:
    Car(string plate) : Vehicle(plate, 1, VehicleSize::Compact) {}

    bool canFitInSpot(ParkingSpot* spot) const override;
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(string plate) : Vehicle(plate, 1, VehicleSize::Motorcycle) {}

    bool canFitInSpot(ParkingSpot* spot) const override;
};

class ParkingSpot {
private:
    Vehicle* vehicle;
    VehicleSize spotSize;
    int row;
    int spotNumber;

public:
    ParkingSpot(int r, int n, VehicleSize size)
        : vehicle(nullptr), row(r), spotNumber(n), spotSize(size) {}

    bool isAvailable() const {
        return vehicle == nullptr;
    }

    bool canFitVehicle(const Vehicle* v) const {
        if (!isAvailable()) return false;

        switch (v->getSize()) {
            case VehicleSize::Motorcycle:
                return true;  // Fits in any spot
            case VehicleSize::Compact:
                return spotSize == VehicleSize::Compact || spotSize == VehicleSize::Large;
            case VehicleSize::Large:
                return spotSize == VehicleSize::Large;
        }
        return false;
    }

    bool park(Vehicle* v) {
        if (!canFitVehicle(v)) return false;
        vehicle = v;
        v->parkInSpot(this);
        return true;
    }

    void removeVehicle() {
        vehicle = nullptr;
    }

    int getRow() const {
        return row;
    }

    int getSpotNumber() const {
        return spotNumber;
    }
};

bool Bus::canFitInSpot(ParkingSpot* spot) const {
    return spot->canFitVehicle(this);
}

bool Car::canFitInSpot(ParkingSpot* spot) const {
    return spot->canFitVehicle(this);
}

bool Motorcycle::canFitInSpot(ParkingSpot* spot) const {
    return spot->canFitVehicle(this);
}

void Vehicle::clearSpots() {
    for (auto spot : parkingSpots) {
        spot->removeVehicle();
    }
    parkingSpots.clear();
}

int main() {
    ParkingSpot spot1(1, 1, VehicleSize::Compact);
    ParkingSpot spot2(1, 2, VehicleSize::Large);

    Car car("CAR-1234");
    Bus bus("BUS-5678");
    Motorcycle moto("MOTO-9999");

    cout << "Parking car: " << (spot1.park(&car) ? "Success" : "Failed") << endl;
    cout << "Parking bus: " << (spot2.park(&bus) ? "Success" : "Failed") << endl;
    cout << "Parking motorcycle: " << (spot1.park(&moto) ? "Success" : "Failed") << endl;

    car.clearSpots();
    bus.clearSpots();
    moto.clearSpots();

    cout << "Spot 1 available: " << (spot1.isAvailable() ? "Yes" : "No") << endl;
    cout << "Spot 2 available: " << (spot2.isAvailable() ? "Yes" : "No") << endl;

    return 0;
}
