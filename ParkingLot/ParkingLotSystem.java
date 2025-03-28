import java.util.ArrayList;
import java.util.List;

// Enum for vehicle size
enum VehicleSize {
    MOTORCYCLE, COMPACT, LARGE
}

// Base Vehicle class
abstract class Vehicle {
    protected List<ParkingSpot> parkingSpots = new ArrayList<>();
    protected String licensePlate;
    protected int spotsNeeded;
    protected VehicleSize size;

    public Vehicle(String licensePlate, int spotsNeeded, VehicleSize size) {
        this.licensePlate = licensePlate;
        this.spotsNeeded = spotsNeeded;
        this.size = size;
    }

    public int getSpotsNeeded() {
        return spotsNeeded;
    }

    public VehicleSize getSize() {
        return size;
    }

    public void parkInSpot(ParkingSpot spot) {
        parkingSpots.add(spot);
    }

    public void clearSpots() {
        for (ParkingSpot spot : parkingSpots) {
            spot.removeVehicle();
        }
        parkingSpots.clear();
    }

    public abstract boolean canFitInSpot(ParkingSpot spot);
}

// Bus class
class Bus extends Vehicle {
    public Bus(String licensePlate) {
        super(licensePlate, 5, VehicleSize.LARGE);
    }

    @Override
    public boolean canFitInSpot(ParkingSpot spot) {
        return spot.canFitVehicle(this);
    }
}

// Car class
class Car extends Vehicle {
    public Car(String licensePlate) {
        super(licensePlate, 1, VehicleSize.COMPACT);
    }

    @Override
    public boolean canFitInSpot(ParkingSpot spot) {
        return spot.canFitVehicle(this);
    }
}

// Motorcycle class
class Motorcycle extends Vehicle {
    public Motorcycle(String licensePlate) {
        super(licensePlate, 1, VehicleSize.MOTORCYCLE);
    }

    @Override
    public boolean canFitInSpot(ParkingSpot spot) {
        return spot.canFitVehicle(this);
    }
}

// ParkingSpot class
class ParkingSpot {
    private Vehicle vehicle;
    private VehicleSize spotSize;
    private int row;
    private int spotNumber;

    public ParkingSpot(int row, int spotNumber, VehicleSize size) {
        this.row = row;
        this.spotNumber = spotNumber;
        this.spotSize = size;
    }

    public boolean isAvailable() {
        return vehicle == null;
    }

    public boolean canFitVehicle(Vehicle vehicle) {
        if (!isAvailable()) return false;

        switch (vehicle.getSize()) {
            case MOTORCYCLE:
                return true;  // Fits in any spot
            case COMPACT:
                return spotSize == VehicleSize.COMPACT || spotSize == VehicleSize.LARGE;
            case LARGE:
                return spotSize == VehicleSize.LARGE;
        }
        return false;
    }

    public boolean park(Vehicle v) {
        if (!canFitVehicle(v)) {
            return false;
        }
        vehicle = v;
        v.parkInSpot(this);
        return true;
    }

    public void removeVehicle() {
        vehicle = null;
    }

    public int getRow() {
        return row;
    }

    public int getSpotNumber() {
        return spotNumber;
    }
}

// Main class to demonstrate the functionality
public class ParkingLotSystem {
    public static void main(String[] args) {
        ParkingSpot spot1 = new ParkingSpot(1, 1, VehicleSize.COMPACT);
        ParkingSpot spot2 = new ParkingSpot(1, 2, VehicleSize.LARGE);

        Car car = new Car("CAR-1234");
        Bus bus = new Bus("BUS-5678");
        Motorcycle moto = new Motorcycle("MOTO-9999");

        System.out.println("Parking car: " + (spot1.park(car) ? "Success" : "Failed"));
        System.out.println("Parking bus: " + (spot2.park(bus) ? "Success" : "Failed"));
        System.out.println("Parking motorcycle: " + (spot1.park(moto) ? "Success" : "Failed"));

        // Clear spots
        car.clearSpots();
        bus.clearSpots();
        moto.clearSpots();

        System.out.println("Spot 1 available: " + (spot1.isAvailable() ? "Yes" : "No"));
        System.out.println("Spot 2 available: " + (spot2.isAvailable() ? "Yes" : "No"));
    }
}
