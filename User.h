#ifndef USER_H
#define USER_H

#include <string>

// The User class represents an individual who is tracking their weight loss progress.
// It stores personal details such as name, age, weight, and fitness goals.
class User {
private:
    std::string logDay;      // Log day number (e.g., "1", "2", "3" for tracking entries)
    std::string date;        // Date the entry was recorded (format: MM/DD/YY)
    std::string name;        // User's name
    char gender;             // User's gender ('M' for male, 'F' for female)
    int age;                 // User's age in years
    double height;           // User's height in inches
    double weight;           // User's current weight in pounds
    int activityLevel;       // Activity level (1-5) indicating how active the user is
    double goalWeight;       // Target weight the user wants to achieve
    double weeklyLoss;       // Desired weekly weight loss in pounds

public:
    // Constructor: Initializes a User object with personal and fitness details.
    User(std::string logDay, std::string date, std::string name, char gender, int age, double height, double weight, 
         int activityLevel, double goalWeight, double weeklyLoss)
        : logDay(logDay), date(date), name(name), gender(gender), age(age), height(height), weight(weight), 
          activityLevel(activityLevel), goalWeight(goalWeight), weeklyLoss(weeklyLoss) {}

    // Getter functions to access private member variables.
    std::string getLogDay() const { return logDay; }         // Returns the log day number
    std::string getDate() const { return date; }             // Returns the date of the log entry
    std::string getName() const { return name; }             // Returns the user's name
    char getGender() const { return gender; }                // Returns the user's gender
    int getAge() const { return age; }                       // Returns the user's age
    double getHeight() const { return height; }              // Returns the user's height in inches
    double getWeight() const { return weight; }              // Returns the user's current weight
    int getActivityLevel() const { return activityLevel; }   // Returns the user's activity level (1-5)
    double getGoalWeight() const { return goalWeight; }      // Returns the user's target weight
    double getWeeklyLoss() const { return weeklyLoss; }      // Returns the desired weekly weight loss
};

#endif
