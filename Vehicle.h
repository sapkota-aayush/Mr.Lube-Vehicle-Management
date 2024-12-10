#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

class Vehicle {
private:
    string licensePlate;
    string province;

public:
    // Constructor
    Vehicle(const string& licensePlate, const string& province);

    // Getter and setter for licensePlate
    string getLicensePlate() const;
    void setLicensePlate(const string& licensePlate);

    // Getter and setter for province
    string getProvince() const;
    void setProvince(const string& province);

    // Save vehicle data to the database
    void saveToDatabase();

    // Display vehicle information
    void displayVehicleInfo() const;
};

#endif // VEHICLE_H
