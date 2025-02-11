#include <iostream>
#include <string>
#include "Database.h"
#include "User.h"
#include "HealthCalculator.h"

using std::cout;
using std::cin;
using std::string;

// Function to log a new weight entry
// This prompts the user to enter their details and stores them in the database.
void logNewEntry(Database& db) {
    while (true) {
        string logDay, date, name;
        char gender;
        int age, activityLevel;
        double height, weight, goalWeight, weeklyLoss;
        char confirm;

        // Collect user details
        cout << "What log day is it (e.g., 1, 2, 3...)? ";
        cin >> logDay;

        cout << "Enter today's date (MM/DD/YY): ";
        cin >> date;

        cout << "Enter your name: ";
        cin >> name;

        cout << "Enter gender (M for Male, F for Female): ";
        cin >> gender;

        cout << "Enter age: ";
        cin >> age;
        cout << "Enter height in inches: ";
        cin >> height;
        cout << "Enter current weight in pounds: ";
        cin >> weight;

        cout << "Select your activity level (1-5): ";
        cin >> activityLevel;

        cout << "Enter goal weight in pounds: ";
        cin >> goalWeight;
        cout << "Enter how many pounds you want to lose per week: ";
        cin >> weeklyLoss;

        // Display confirmation message
        cout << "\nYou entered the following details:\n";
        cout << "Log Day: " << logDay << "\nDate: " << date << "\nName: " << name << "\nGender: " << gender
             << "\nAge: " << age << "\nHeight: " << height << " inches\nWeight: " << weight << " lbs"
             << "\nActivity Level: " << activityLevel << "\nGoal Weight: " << goalWeight
             << "\nWeekly Weight Loss: " << weeklyLoss << " lbs\n";

        cout << "Is this information correct? (Y/N): ";
        cin >> confirm;

        // If confirmed, save data to the database
        if (confirm == 'Y' || confirm == 'y') {
            User user(logDay, date, name, gender, age, height, weight, activityLevel, goalWeight, weeklyLoss);
            db.insertUser(user); // ✅ Store user data in the database
            HealthCalculator::displayCaloricInfo(user); // ✅ Display caloric information
            break; // Exit the loop
        } else {
            cout << "Restarting input...\n\n"; // Restart data entry if incorrect
        }
    }
}

// Function to delete a specific log entry based on date
void deleteLog(Database& db) {
    string date;
    cout << "Enter the date (MM/DD/YY) of the log to delete: ";
    cin >> date;
    db.deleteLogByDate(date); // Delete log from database
}

// Function to generate a weight trend graph for a specific user
void generateUserGraph(Database& db) {
    std::string userName;
    cout << "Enter the name of the user to generate a weight trend graph: ";
    cin >> userName;
    db.generateWeightGraph(userName); // Generate and display weight trend graph
}

// Function to update a past log entry
void updateLog(Database& db) {
    string date;
    double newWeight;
    int newActivityLevel;

    cout << "Enter the date (MM/DD/YY) of the log you want to update: ";
    cin >> date;

    cout << "Enter new weight in pounds: ";
    cin >> newWeight;

    cout << "Enter new activity level (1-5): ";
    cin >> newActivityLevel;

    db.updateLogByDate(date, newWeight, newActivityLevel); // Update database entry
}

int main() {
    // Create or open the SQLite database
    Database db("weightloss.db");
    db.createTable(); // Ensure the Users table exists

    int choice; // Variable to store user's menu selection

    // Main menu loop
    do {
        cout << "\n=== Weight Loss Tracker ===\n";
        cout << "1. Log New Weight Entry\n";
        cout << "2. View Past Logs\n";
        cout << "3. Generate Weight Trend Graph\n";
        cout << "4. Delete a Past Log by Date\n";
        cout << "5. Update a Past Log by Date\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle user's menu selection
        if (choice == 1) {
            logNewEntry(db); // Log a new weight entry
        } else if (choice == 2) {
            db.viewAllLogs(); // View all logs
        } else if (choice == 3) {
            generateUserGraph(db); // Generate a weight trend graph
        } else if (choice == 4) {
            deleteLog(db); // Delete a past log
        } else if (choice == 5) {
            updateLog(db); // Update a past log
        }

    } while (choice != 6); // Keep running until the user selects Exit (6)

    return 0; // End the program
}
