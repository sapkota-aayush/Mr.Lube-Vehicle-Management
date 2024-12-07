#include <iostream>
#include <windows.h>
#include <string>
#include "Utility.h"  // Assuming Utility.h contains the isValidInput function
#include "AuthSystem.h"  // Assuming AuthSystem is defined elsewhere

using namespace std;

// Function to set console text color
void SetConsoleColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to change background to blue and text to yellow for splash screen
void ShowSplashScreen()
{
    // Set background to blue and text to yellow
    system("color 1F");

    // Print "MR. LUBE" in ASCII art
    SetConsoleColor(14);  // Yellow color for the text
    cout << "*********************************************\n";
    cout << "*                                           *\n";
    cout << "*               M R . L U B E               *\n";
    cout << "*                                           *\n";
    cout << "*********************************************\n";

    // Reset text color to white
    SetConsoleColor(7);  // White color
}

int main()
{
    ShowSplashScreen();

    string bayId, password;

    // Prompt user for Bay ID and validate input
    cout << "Enter Bay ID: ";
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
    }
    else {
        cout << "Authentication failed. Please try again." << endl;
    }

    return 0;
}
