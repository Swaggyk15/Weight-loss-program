#ifndef HEALTHCALCULATOR_H
#define HEALTHCALCULATOR_H

#include "User.h"  // Include User class to access user details
#include <iostream>

class HealthCalculator {
public:
    // Calculates Basal Metabolic Rate (BMR) using the Mifflin-St Jeor formula.
    // This represents the number of calories the body burns at rest.
    static double calculateBMR(const User& user) {
        double kg = user.getWeight() * 0.453592; // Convert weight from pounds to kilograms
        double cm = user.getHeight() * 2.54;     // Convert height from inches to centimeters

        // BMR calculation differs based on gender
        if (user.getGender() == 'F' || user.getGender() == 'f')
            return (10 * kg) + (6.25 * cm) - (5 * user.getAge()) - 161; // Female formula
        else
            return (10 * kg) + (6.25 * cm) - (5 * user.getAge()) + 5;   // Male formula
    }

    // Calculates Total Daily Energy Expenditure (TDEE).
    // TDEE accounts for physical activity and determines how many calories
    // a person should consume daily to maintain their current weight.
    static double calculateTDEE(const User& user) {
        double BMR = calculateBMR(user); // Get the user's BMR
        double activityMultipliers[] = {1.2, 1.375, 1.55, 1.725, 1.9}; // Activity level multipliers
        
        // Validate activity level input
        if (user.getActivityLevel() < 1 || user.getActivityLevel() > 5)
            return -1; // Invalid activity level

        return BMR * activityMultipliers[user.getActivityLevel() - 1]; // Apply the multiplier
    }

    // Displays important caloric information for weight loss.
    // Includes target daily calories, weekly calorie deficit, and estimated time to reach the goal.
    static void displayCaloricInfo(const User& user) {
        double TDEE = calculateTDEE(user); // Get the user's TDEE

        // Handle invalid activity level
        if (TDEE == -1) {
            std::cout << "Invalid activity level selected.\n";
            return;
        }

        // Calculate weekly calorie deficit needed for the user's goal
        double totalDeficit = user.getWeeklyLoss() * 3500; // 1 lb = 3500 calories
        double dailyDeficit = totalDeficit / 7; // Spread deficit across the week
        double targetCalories = TDEE - dailyDeficit; // Target calorie intake per day
        double estimatedWeeks = (user.getWeight() - user.getGoalWeight()) / user.getWeeklyLoss(); // Time to reach goal

        // Display the calculated results
        std::cout << "\n=== Caloric Information ===\n";
        std::cout << "Your estimated daily caloric needs: " << TDEE << " calories.\n";
        std::cout << "Recommended daily intake for weight loss: " << targetCalories << " calories.\n";
        std::cout << "Total weekly calorie deficit: " << totalDeficit << " calories.\n";
        std::cout << "Estimated time to reach goal: " << estimatedWeeks << " weeks.\n";
    }
};

#endif
