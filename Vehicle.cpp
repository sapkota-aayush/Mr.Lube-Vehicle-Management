#include "Vehicle.h"
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

// Constructor definition
Vehicle::Vehicle(const string& licensePlate, const string& province)
    : licensePlate(licensePlate), province(province) {}

// Getter and setter for licensePlate
string Vehicle::getLicensePlate() const {
    return licensePlate;
}

void Vehicle::setLicensePlate(const string& licensePlate) {
    this->licensePlate = licensePlate;
}

// Getter and setter for province
string Vehicle::getProvince() const {
    return province;
}

void Vehicle::setProvince(const string& province) {
    this->province = province;
}

// Save vehicle data to the database
void Vehicle::saveToDatabase() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    try {
        // Create a connection to the MySQL database
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "Happy@890123");  // Replace with MySQL credentials
        con->setSchema("mrlubevehicle");  // Replace with your database name

        // Check if the vehicle already exists
        sql::PreparedStatement* checkStmt = con->prepareStatement(
            "SELECT COUNT(*) FROM vehicles WHERE license_plate = ? AND province = ?"
        );
        checkStmt->setString(1, licensePlate);  // License Plate
        checkStmt->setString(2, province);     // Province
        sql::ResultSet* res = checkStmt->executeQuery();

        // If count > 0, vehicle already exists
        res->next();  // Move to the result row
        int count = res->getInt(1);

        if (count > 0) {
            cout << "This vehicle data already exists in the database!" << endl;
        }
        else {
            // Prepare the insert query
            sql::PreparedStatement* stmt = con->prepareStatement(
                "INSERT INTO vehicles (license_plate, province) VALUES (?, ?)"
            );

            // Set parameters for the query
            stmt->setString(1, licensePlate);  // License Plate
            stmt->setString(2, province);     // Province

            // Execute the query
            stmt->executeUpdate();

            cout << "Vehicle data saved successfully!" << endl;

            // Clean up
            delete stmt;
        }

        // Clean up
        delete checkStmt;
        delete res;
        delete con;
    }
    catch (sql::SQLException& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// Display vehicle information (for testing purposes)
void Vehicle::displayVehicleInfo() const {
    cout << "License Plate: " << licensePlate << endl;
    cout << "Province: " << province << endl;
}
