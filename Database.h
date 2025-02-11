#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <string>
#include "User.h"  
class Database {
private:
    sqlite3* db;  // SQLite database connection object
    char* errorMessage;  // Holds error messages from SQLite operations

    // This function is used as a callback when retrieving data from SQLite.
    // It simply prints out each column's name and value for a given row.
    static int callback(void* NotUsed, int argc, char** argv, char** colName) {
        for (int i = 0; i < argc; i++) {
            std::cout << colName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\n";
        }
        std::cout << "---------------------\n";  // Separate rows visually
        return 0;
    }

public:
    // Constructor: Opens a connection to the SQLite database
    Database(const std::string& dbName) {
        if (sqlite3_open(dbName.c_str(), &db)) {
            std::cerr << "Error opening database: " << sqlite3_errmsg(db) << "\n";
        } else {
            std::cout << "Database connected successfully!\n";
        }
    }

    // Destructor: Closes the database connection when the object is destroyed
    ~Database() {
        sqlite3_close(db);
    }

    // Creates the "Users" table if it does not already exist
    void createTable() {
        std::string sql = "CREATE TABLE IF NOT EXISTS Users ("
                          "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "LogDay TEXT NOT NULL, "
                          "Date TEXT NOT NULL, "
                          "Name TEXT NOT NULL, "
                          "Gender TEXT NOT NULL, "
                          "Age INTEGER NOT NULL, "
                          "Height REAL NOT NULL, "
                          "CurrentWeight REAL NOT NULL, "
                          "GoalWeight REAL NOT NULL, "
                          "ActivityLevel INTEGER NOT NULL, "
                          "WeeklyLoss REAL NOT NULL);";
        sqlite3_exec(db, sql.c_str(), 0, 0, &errorMessage);  // Execute the SQL statement
    }

    // Inserts a new user's weight loss data into the database
    void insertUser(const User& user) {
        std::string sql = "INSERT INTO Users (LogDay, Date, Name, Gender, Age, Height, CurrentWeight, GoalWeight, ActivityLevel, WeeklyLoss) VALUES ('"
                          + user.getLogDay() + "', '" + user.getDate() + "', '" + user.getName() + "', '" + user.getGender() + "', " 
                          + std::to_string(user.getAge()) + ", " + std::to_string(user.getHeight()) + ", " 
                          + std::to_string(user.getWeight()) + ", " + std::to_string(user.getGoalWeight()) + ", " 
                          + std::to_string(user.getActivityLevel()) + ", " + std::to_string(user.getWeeklyLoss()) + ");";
        sqlite3_exec(db, sql.c_str(), 0, 0, &errorMessage);  // Execute SQL statement
    }

    // Deletes a specific log entry based on the given date
    void deleteLogByDate(const std::string& date) {
        std::string sql = "DELETE FROM Users WHERE Date = '" + date + "';";
        sqlite3_exec(db, sql.c_str(), 0, 0, &errorMessage);
    }

    // Updates an existing log entry by modifying weight and activity level
    void updateLogByDate(const std::string& date, double newWeight, int newActivityLevel) {
        std::string sql = "UPDATE Users SET CurrentWeight = " + std::to_string(newWeight) +
                          ", ActivityLevel = " + std::to_string(newActivityLevel) +
                          " WHERE Date = '" + date + "';";
        sqlite3_exec(db, sql.c_str(), 0, 0, &errorMessage);
    }

    // Displays all past logs from the database
    void viewAllLogs() {
        std::string sql = "SELECT LogDay, Name, Date, CurrentWeight, GoalWeight FROM Users ORDER BY Date ASC;";
        sqlite3_exec(db, sql.c_str(), callback, 0, &errorMessage);
    }

    // Callback function to export user weight data into a file for graphing
    static int exportCallback(void* file, int argc, char** argv, char** colName) {
        std::ofstream* outFile = static_cast<std::ofstream*>(file);
        *outFile << argv[0] << " " << argv[1] << "\n"; // LogDay Weight
        return 0;
    }

    // Generates a weight trend graph for a specific user
    void generateWeightGraph(const std::string& userName) {
        std::ofstream outFile("weight_data.txt");
        if (!outFile) {
            std::cerr << "Error creating data file!\n";
            return;
        }

        // SQL query to fetch weight data for a given user
        std::string sql = "SELECT LogDay, CurrentWeight FROM Users WHERE Name = '" + userName + "' ORDER BY Date ASC;";
        
        // Execute query and write data to file
        if (sqlite3_exec(db, sql.c_str(), exportCallback, &outFile, &errorMessage) != SQLITE_OK) {
            std::cerr << "Error exporting weight data: " << errorMessage << "\n";
            sqlite3_free(errorMessage);
        } else {
            std::cout << "Weight data for " << userName << " exported successfully!\n";
        }
        outFile.close();

        // Create a Gnuplot script to plot the weight trend
        std::ofstream gnuplotScript("plot_script.gp");
        gnuplotScript << "set terminal pngcairo size 800,600\n";
        gnuplotScript << "set output 'weight_trend.png'\n";
        gnuplotScript << "set title 'Weight Trend for " << userName << "'\n";
        gnuplotScript << "set xlabel 'Log Day'\n";
        gnuplotScript << "set ylabel 'Weight (lbs)'\n";
        gnuplotScript << "set grid\n";
        gnuplotScript << "plot 'weight_data.txt' using 1:2 with linespoints title 'Weight Progress'\n";
        gnuplotScript.close();

        // Run the Gnuplot script to generate the graph
        system("gnuplot plot_script.gp");
        std::cout << "Weight trend graph for " << userName << " generated as 'weight_trend.png'.\n";
    }
};

#endif
