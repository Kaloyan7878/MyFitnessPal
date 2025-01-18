#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

struct User
{
    string username;
    string password;
    unsigned age;
    string gender;
    float height;
    float weight;
    string activityLevel; 
    string goal;
    string accountType;
    float maintenanceCalories;
};

struct Meal 
{
    string date;
    string food;
    float calories;
};

struct Training
{
    string date;
    string type;
    float calories;
};
//Function that shos the current date in the corrent format
string getCurrentDate()
{
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);
    char currentDate[11];
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", &localTime);
    return string(currentDate);
}
//Function that creates a file which stores he data about he meals of the user on different dates
void addMeal(const string& username) 
{
    Meal meal;
    cout << "--- Add a meal: ---\n";

    meal.date = getCurrentDate();

    cout << "Name of the food: ";
    cin.ignore();
    getline(cin, meal.food);

    cout << "Calories: ";
    cin >> meal.calories;

    ofstream file(username + "_meals.txt", ios::app);
    if (file.is_open()) 
    {
        file << "Date: " << meal.date << endl;
        file << "Food: " << meal.food << endl;
        file << "Calories: " << meal.calories << endl;
        file << "-----------------------------" << endl;

        file.close();
        cout << "Meal was added!\n";
    }
    else {
        cout << "Error opening the file!\n";
    }
}

void addTraining(const string& username)
{
    Training training;
    cout << "--- Add a training: ---\n";

    training.date = getCurrentDate();

    cout << "Type of training: ";
    cin.ignore();
    getline(cin, training.type);

    cout << "Calories: ";
    cin >> training.calories;

    ofstream file(username + "_training.txt", ios::app);
    if (file.is_open())
    {
        file << "Date: " << training.date << endl;
        file << "Type: " << training.type << endl;
        file << "Calories: " << training.calories << endl;
        file << "-----------------------------" << endl;

        file.close();
        cout << "Training was added!\n";
    }
    else 
    {
        cout << "Error opening the file!\n";
    }
}

User users[100];
int userCount = 0;
string currentLoggedInUser = "";

User extractUserData(const string& username) 
{
    ifstream file("users.txt");
    string line;
    User user;
    bool found = false;

    // Read the file line by line to find the user's data
    while (getline(file, line)) 
    {
        if (line.find("Username: " + username) != string::npos) 
        {
            user.username = username;

            // Extract remaining data from the file
            for (int i = 0; i < 8; ++i) 
            {
                getline(file, line);
                if (i == 0) user.password = line.substr(line.find(": ") + 2);
                if (i == 1) user.age = stoi(line.substr(line.find(": ") + 2));
                if (i == 2) user.gender = line.substr(line.find(": ") + 2);
                if (i == 3) user.height = stof(line.substr(line.find(": ") + 2));
                if (i == 4) user.weight = stof(line.substr(line.find(": ") + 2));
                if (i == 5) user.activityLevel = line.substr(line.find(": ") + 2);
                if (i == 6) user.goal = line.substr(line.find(": ") + 2);
                if (i == 7) user.accountType = line.substr(line.find(": ") + 2);
            }

            found = true;
            break;  // Exit the loop once the user is found
        }
    }

    file.close();
    if (!found) 
    {
        cout << "User not found in the file!" << endl;
    }

    return user;  // Return the populated User object
}
// Function to check if the username is unique:
bool isUsernameFree(string username)
{
    ifstream file("users.txt", ios::app);
    string line;
    if (!file.is_open()) 
    {
        cout << "Error: Could not open the file!" << endl;
        return false;
    }
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line);
            if (line.find("Username: " + username) != string::npos)
            {
                file.close();
                return false;
            }
        }
    }
    file.close();
    return true;
}
void registerUser() 
{
    User user;

    cout << "=== Registration: ===" << endl;

    // Check if username is unique:
    do 
    {
        cout << "Enter username: ";
        cin >> user.username;
        if (!isUsernameFree(user.username)) 
        {
            cout << "Username not free." << endl;
        }
    } while (!isUsernameFree(user.username));

    cout << "Enter password: ";
    cin >> user.password;

    cout << "Enter age: ";
    cin >> user.age;

    cout << "Enter gender (m/f): ";
    cin >> user.gender;

    cout << "Enter height (cm): ";
    cin >> user.height;

    cout << "Enter weight (kg): ";
    cin >> user.weight;

    cout << "Enter activity level (low/moderate/high/very high): ";
    cin >> user.activityLevel;

    cout << "Enter goal (cutting/maintaining/gaining): ";
    cin >> user.goal;

    do 
    {
        cout << "Enter account type (Standard/Premium): ";
        cin >> user.accountType;
        if (user.accountType != "Standard" || user.accountType != "Premium") 
        {
            cout << "Error, enter 'Standard' or 'Premium'." << endl;
        }
    } while (user.accountType != "Standard" || user.accountType != "Premium");

    // Write user data to users.txt
    ofstream file("users.txt", ios::app);  // Open users.txt
    if (file.is_open()) 
    {
        file << "Username: " << user.username << endl;
        file << "Password: " << user.password << endl;
        file << "Age: " << user.age << endl;
        file << "Gender: " << user.gender << endl;
        file << "Height: " << user.height << " cm" << endl;
        file << "Weight: " << user.weight << " kg" << endl;
        file << "Activity Level: " << user.activityLevel << endl;
        file << "Goal: " << user.goal << endl;
        file << "Account Type: " << user.accountType << endl;
        file << "-----------------------------" << endl;
        file.close();
        cout << "Registration is successful!" << endl;
    }
    else 
    {
        cout << "Error writing user data!" << endl;
    }
}
void loginUser()
{
    string username, password;
    cout << "\n--- User Login ---\n";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");  // Open the file to read user data
    string line;
    bool found = false;  // Flag to check if we found the user
    string storedUsername, storedPassword;

    // Read the file line by line
    while (getline(file, line)) 
    {
        // Look for the username line
        if (line.find("Username: " + username) != string::npos) 
        {
            storedUsername = username;  // Set stored username to the one from input

            // Read the next line for the password
            getline(file, line);  // Read password line
            storedPassword = line.substr(line.find(": ") + 2);  // Extract password part

            // Check if the password matches
            if (storedPassword == password) 
            {
                currentLoggedInUser = username;  // Set the current logged-in user
                cout << "Login successful! Welcome, " << username << "!\n";
                found = true;  // Mark that the user was found and logged in
                break;
            }
        }
    }

    // If no matching username or password is found
    if (!found) 
    {
        cout << "Invalid username or password!\n";
    }

    file.close();
}
unsigned recommendedCalories(const User& user)
{
    float bmr;
    if (user.gender == "m" || user.gender == "M")
    {
        bmr = 88.362 + (13.397 * user.weight) + (4.799 * user.height) - (5.677 * user.age);
    }
    else
    {
        bmr = 447.593 + (9.247 * user.weight) + (3.098 * user.height) - (4.330 * user.age);
    }
    float activityCoefficient = 1.2; // Default: sedentary
    if (user.activityLevel == "low")
    {
        activityCoefficient = 1.375; // Light activity (1-3 days per week)
    }
    else if (user.activityLevel == "moderate")
    {
        activityCoefficient = 1.55; // Moderate activity (3-5 days per week)
    }
    else if (user.activityLevel == "active")
    {
        activityCoefficient = 1.725; // Active work (6-7 days per week)
    }
    else if (user.activityLevel == "very active")
    {
        activityCoefficient = 1.9; // Very active (intense physical activity)
    }
    else
    {
        cout << "Invalid activity level. Defaulting to sedentary." << endl;
    }
    float maintenanceCalories = bmr * activityCoefficient;
    if (user.goal == "cutting") return maintenanceCalories - 550;
    else if (user.goal == "maintaining") return maintenanceCalories;
    else return maintenanceCalories + 550;
}
float caloricBalance(const string& username)
{
    string currentDate = getCurrentDate();
    string filename = username + "_meals.txt";
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Could not open file " << filename << "!" << endl;
        return -1;
    }
    string line;
    float totalCalories = 0.0;
    bool foundTodayMeals = false;
    while (getline(file, line))
    {
        if (line.find("Date: ") != string::npos) 
        {
            string date = line.substr(6);
            if (date == currentDate) foundTodayMeals = true;
            else foundTodayMeals = false;
        }
        if (foundTodayMeals) 
        {
            if (line.find("Calories: ") != string::npos) 
            {
                float calories = stof(line.substr(10));
                totalCalories += calories;
            }
        }
    }
    file.close();
    string trainingFile = username + "_training.txt";
    ifstream trainingInputFile(trainingFile);
    if (!trainingInputFile.is_open()) {
        cout << "Error: Could not open file " << trainingFile << "!" << endl;
        return -1;
    }
    float totalCaloriesBurned = 0.0;
    bool foundTodayTrainings = false;
    while (getline(trainingInputFile, line)) {
        if (line.find("Date: ") != string::npos) 
        {
            string date = line.substr(6);
            if (date == currentDate) 
            {
                foundTodayTrainings = true;
            }
            else 
            {
                foundTodayTrainings = false;
            }
        }
        if (foundTodayTrainings) 
        {
            if (line.find("Calories: ") != string::npos) {
                float caloriesBurned = stof(line.substr(10));
                totalCaloriesBurned += caloriesBurned;
            }
        }
    }
    trainingInputFile.close();
    return totalCalories - totalCaloriesBurned;
}
//Function that calculates macros for the premium users
void calculateMacros(const User& user) 
{
    cout << "--- Macronutrient Distribution ---\n";
    float totalCalories = recommendedCalories(user);

    float proteinPercentage = 0.0, fatPercentage = 0.0, carbPercentage = 0.0;

    if (user.goal == "cutting") {
        proteinPercentage = 0.35;
        fatPercentage = 0.30;
        carbPercentage = 0.35;
    }
    else if (user.goal == "maintaining") {
        proteinPercentage = 0.25;
        fatPercentage = 0.30;
        carbPercentage = 0.45;
    }
    else if (user.goal == "gaining") {
        proteinPercentage = 0.20;
        fatPercentage = 0.25;
        carbPercentage = 0.55;
    }
    else {
        cout << "Invalid goal.\n";
        return;
    }
    float proteinCalories = totalCalories * proteinPercentage;
    float fatCalories = totalCalories * fatPercentage;
    float carbCalories = totalCalories * carbPercentage;
    float proteinGrams = proteinCalories / 4;
    float fatGrams = fatCalories / 9;
    float carbGrams = carbCalories / 4;
    cout << "Protein: " << proteinGrams << " grams\n";
    cout << "Fat: " << fatGrams << " grams\n";
    cout << "Carbohydrates: " << carbGrams << " grams\n";
}

// Function to display user data and recommended calories
void displayUserData(const string& username) 
{
    User user = extractUserData(username);  // Get user data from file
    if (user.username.empty()) 
    {
        return;  // If the username was not found, exit the function
    }
    cout << "\n--- User Data ---\n";
    cout << "Username: " << user.username << endl;
    cout << "Age: " << user.age << endl;
    cout << "Gender: " << user.gender << endl;
    cout << "Height: " << user.height << " cm" << endl;
    cout << "Weight: " << user.weight << " kg" << endl;
    cout << "Activity Level: " << user.activityLevel << endl;
    cout << "Goal: " << user.goal << endl;
    cout << "Account Type: " << user.accountType << endl;
    // Calculate and display the recommended daily calories
    float recommendedCal = recommendedCalories(user);
    cout << "Recommended daily calories: " << recommendedCal << " kcal" << endl;
    cout << "Balance: " << caloricBalance(username) << endl;
    if (user.accountType == "Premium") calculateMacros(user);
}

int main()
{
    string username, password;
    unsigned choice;
    do 
    {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) 
        {
            registerUser();
        }
        else if (choice == 2) 
        {
            loginUser();
        }
        else if (choice == 3) 
        {
            cout << "Exiting the program. Goodbye!\n";
            return 0;
        }
        else 
        {
            cout << "Invalid choice! Please try again.\n";
        }

        // If a user logs in, show the user menu
        while (!currentLoggedInUser.empty()) 
        {
            displayUserData(currentLoggedInUser);
            cout << "\n--- User Menu ---\n";
            cout << "1. Add meal\n";
            cout << "2. Add training session\n";
            cout << "3. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) addMeal(currentLoggedInUser);
            else if (choice == 2) 
            {
                addTraining(currentLoggedInUser);
            }
            else if (choice == 3) 
            {
                cout << "Logging out...\n";
                currentLoggedInUser = ""; // Clear the logged-in user
            }
            else 
            {
                cout << "Invalid choice! Please try again.\n";
            }
        }
    } while (true); // Keeps returning to the main menu until the user exits
}