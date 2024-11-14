#include <iostream>
void intro();
double fem_bmr_calc(double weight, double height, double age);
double male_bmr_calc(double weight, double height, double age);
double TDEE_calc(double x, double y);
void cal_info(double z, double w, double g);
using std::cout;
using std::cin;
int main(){


    intro();

    cout<< "Please type whether you are a male or female (\"M\"for male, \"F\" for female): ";
    char gender;
    cin >> gender;

    double age;
    cout<< "Please enter your age (Ex: 15, 17, 41 are all acceptable inputs): ";
    cin>> age;

    double height;
    cout<< "Please enter your height in inches (Ex: 72 or 68.5 are acceptable inputs): ";
    cin>> height;

    double weight;
    cout<< "Please enter your current weight (Ex: 150, 170.5, 200 are acceptable inputs): ";
    cin >> weight;

    double BMR; 

    if(gender == 'F'){
        BMR = fem_bmr_calc(weight, height, age);
    }
    else{
        BMR = male_bmr_calc(weight, height, age);
    }

    cout << "Please decide what choice best describes your activity levels: \n\n";
    cout<< "1: you have a sedentary lifestyle (little to no exercise)\n";
    cout<< "2: you have a lightly active lifestyle (light exercise 1-3 days per week)\n";
    cout<< "3: you have a moderately active lifestyle (moderate exercise 3-5 days per week)\n";
    cout<< "4: you have a very active lifestyle (heavy exercise 6-7 days per week)\n";
    cout<< "5: you have an extremely active lifestyle (strenuous training 2 times a day)\n";

    cout<< "\nEnter your choice (1, 2, 3, 4, or 5): ";
    int choice;
    cin>> choice;

    double num; 

    switch(choice){
        case 1:
            num = 1.2;
            break;
        case 2:
            num = 1.375;
            break;
        case 3:
            num = 1.55;
            break;
        case 4:
            num = 1.725;
            break;
        case 5:
            num = 1.9;
            break;
        default:
            cout << "You chose a wrong option";

    }

    double maintenace_cals = TDEE_calc(BMR, num);

    cout<< "\nYour final maintenace calories based on what you have entered is approximately: " << maintenace_cals << '\n';

    cout<< "\nAlso, how many pounds would you like to drop in weight?";
    double goal;
    cin>> goal;

    cout<< "\nLastly, how many pounds would you like to lose per week (1 lb, 1.5 lb, 2 lb...)?";
    double lbs = 0;
    cin >> lbs;

    cal_info(lbs, maintenace_cals, goal);



    return 0;
}
void intro(){
    cout<< "Weight loss is all about playing a numbers gain. For reference, there is a total";
    cout<< " of 3500 calories in 1 pound of fat. Therefore by burning 3500 calories, you can lose 1 pound";
    cout<< " of fat. Many experts recommend that a healthy weight loss is a deficit of 500 calories per day.\n";
    cout<< "You can lose weight by three ways. \n\n";
    cout<< "Method 1: find your maintenance calories and eat 500 less calories than that\n";
    cout<< "Method 2: find your maintenance calories and eat at that per day, then burn 500 calories ";
    cout<< "a day through exercise.\n";
    cout<< "Method 3: find maintenance calories. Then you want to eat 250 less than that as well as burn 250";
    cout<< " calories per day through exercise.\n\n";

    cout<< "Lastly, it is important that you consume healthy foods that are lower in sugar, sodium, and fat\n";
    cout<< "This program will help you by asking some questions about your life, finding your calorie";
    cout<< " maintenance, and what you should aim for when trying to lose a certain amount of pounds per week. ";
    cout<< "Lastly, the program will also tell you how long it should take for you to achieve your goal!\n\n";

    cout<< "With that being said, let's calculate your maintenance calories!\n";

}
double fem_bmr_calc(double weight, double height, double age){

    double result = 0;

    double kg = weight * 0.45359237;

    result = (10*kg) + (6.25*height*2.54) - (5*age) - 161;

    return result;

}
double male_bmr_calc(double weight, double height, double age){
    double result = 0;

    double kg = weight * 0.45359237;

    result = (10*kg) + (6.25*height*2.54) - (5*age) + 5;

    return result;
}
double TDEE_calc(double x, double y){
    return x*y;
}
void cal_info(double z, double w, double g){
    double tots = z * 3500;
    double daily = tots/7;
    double easy_calc = g/z;
    cout << "\nBased on your answers, you should have a total deficit of " << tots << " calories per week.\n";
    cout<< "\nMore specifically, you should aim to eat around "<< w << " calories per day and lose a total of \n";
    cout << daily<< " calories per day through the methods provided at the start of the program.\n";
    cout<< "(Basically you should have a total of " << w - daily << " calories in your system by the end of the day)\n";
    cout<< "\nBy following this program, you should drop " << g << " pounds in approximately " << easy_calc << " weeks!\n";
    cout<< "\nGood luck on your weightloss journey!!\n";
}