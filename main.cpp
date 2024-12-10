#include <iostream>
#include <windows.h>
#include <string>
#include<iomanip>
#include "Utility.h"  // For validation functions
#include "AuthSystem.h"  // Assuming AuthSystem is defined elsewhere
#include "Vehicle.h"

using namespace std;

// For screen clearing purpose
void clearScreen()
{
    system("CLS");
}

// Function to set console text color
void SetConsoleColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to change background to blue and text to yellow for splash screen
void ShowSplashScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD bufferSize = csbi.dwSize;
    COORD topLeft = { 0, 0 };
    DWORD written;

    // Fill entire screen with blue background
    FillConsoleOutputAttribute(hConsole, BACKGROUND_BLUE, bufferSize.X * bufferSize.Y, topLeft, &written);
    FillConsoleOutputCharacter(hConsole, ' ', bufferSize.X * bufferSize.Y, topLeft, &written);

    // Set cursor to top-left corner
    SetConsoleCursorPosition(hConsole, topLeft);

    // Print "MR. LUBE" in yellow text on blue background, centered
    const string text = "M R . L U B E";
    int spaces = (bufferSize.X - text.length()) / 2;

    // Set text to yellow for the company name
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << string(spaces, ' ') << text << endl;

    // Reset text color to default after splash screen
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
}

// Function to set the console background to blue and text to white for the rest of the program
void SetBlueBackground()
{
    // Set background to blue and text to white
    system("color 1F");  // 1 = Blue background, F = White text
}

// Vehicle menu and input handling
void displayVehicleMenu()
{
    cout << "\n--- Vehicle Information Menu ---\n";
    cout << "Please enter the vehicle details below:\n";
}

int main()
{
    string bayId, password;

    // Show splash screen
    ShowSplashScreen();

    // Set blue background and white text for the rest of the program
    SetBlueBackground();

    // Prompt user for Bay ID and validate input
    cout << "\nEnter Bay ID: ";
    cin >> bayId;
    while (!isValidInput(bayId)) {
        cout << "Invalid Bay ID. Please try again: ";
        cin >> bayId;
    }

    // Prompt user for Password and validate input
    cout << "Enter Password: ";
    cin >> password;
    while (!isValidInput(password)) {
        cout << "Invalid Password. Please try again: ";
        cin >> password;
    }

    // Create AuthSystem object and authenticate
    AuthSystem auth;
    if (auth.authenticate(bayId, password)) {
        cout << "Authentication successful." << endl;

        // Clear screen and show vehicle menu
        clearScreen();
        displayVehicleMenu();

        // Vehicle information
        string licensePlate, province;

        // Validate license plate
        cout << "Enter License Plate (Format: XXX-1234): ";
        cin >> licensePlate;
        while (!isValidLiscencePlate(licensePlate)) {
            cout << "Invalid License Plate format. Please try again (XXX-1234): ";
            cin >> licensePlate;
        }

        // Collect and validate province
        cout << "Enter Province(ON, QB, BC, AB): ";
        cin >> province;
        while (!isValidProvince(province)) {
            cout << "Invalid Province. Please try again: ";
            cin >> province;
        }

        // Create a Vehicle object with the provided details
        Vehicle vehicle(licensePlate, province);

        // Save the vehicle info to the database
        vehicle.saveToDatabase();

        // Display the vehicle info (for confirmation)
        vehicle.displayVehicleInfo();

        cout << "Vehicle information saved successfully!" << endl;
    }
    else {
        cout << "Authentication failed. Please try again." << endl;
    }

    return 0;
}
