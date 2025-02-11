Weight Loss Tracker

What is it?

The Weight Loss Tracker is a C++ program designed to help users track and manage their weight loss journey. It allows users to enter their information, stores it in an SQLite database, calculates their daily caloric needs, and provides insights into their progress. This program was originally built as a learning project for C++, but with the added features, it has become a practical tool for anyone looking to monitor their weight loss effectively.

Key Features

Log daily weight entries and store them in an SQLite database

Calculate Basal Metabolic Rate (BMR) and Total Daily Energy Expenditure (TDEE) based on user inputs

View past weight logs to track progress over time

Generate a weight trend graph using Gnuplot to visualize weight changes

Update or delete past logs if incorrect data was entered

Object-Oriented Programming (OOP) design for maintainability and scalability

Technologies Used

C++ for program logic and calculations

SQLite for storing and managing user data

Gnuplot for generating weight trend graphs

g++ for compiling and running the program

How to Run the Program

1. Install Required Dependencies

Mac (Homebrew)

brew install sqlite3 gnuplot

Linux (Ubuntu/Debian)

sudo apt update
sudo apt install g++ sqlite3 libsqlite3-dev gnuplot

Windows (MSYS2)

pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-sqlite3 mingw-w64-x86_64-gnuplot

2. Compile the Program

g++ weightloss.cpp Database.cpp User.cpp HealthCalculator.cpp -o weightloss -I/opt/homebrew/include -L/opt/homebrew/lib -lsqlite3

3. Run the Program

./weightloss

4. Generate a Weight Trend Graph

Once multiple weight entries are logged:

Select option 3 (Generate Weight Trend Graph)

Enter the name of the user whose weight trend you want to visualize

Open the generated graph using:

open weight_trend.png   # (Mac)
xdg-open weight_trend.png   # (Linux)
start weight_trend.png   # (Windows)

Future Improvements

While the program is fully functional, some potential enhancements include:

Adding a graphical user interface (GUI) for easier interaction

Supporting multiple users with separate tracking

Implementing real-time analytics for better progress insights

This project has been an excellent learning experience, and I look forward to expanding its capabilities further.

Kenny Monterroso

