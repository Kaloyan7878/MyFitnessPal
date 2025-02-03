#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
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
//Function that shows the current date in the corrent format
string getCurrentDate()
{
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);
    char currentDate[11];
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", &localTime);
    return string(currentDate);
}
vector<Meal> extractMealsForDate(const string& username, const string& date) 
{
    vector<Meal> meals;
    string filename = username + "_meals.txt";
    ifstream file(filename);
    if (!file.is_open()) return meals;
    string line;
    bool isDateMatch = false;
    Meal meal;
    while (getline(file, line)) 
    {
        if (line.find("Date: ") != string::npos) 
        {
            isDateMatch = (line.substr(6) == date);
        }
        if (isDateMatch) {
            if (line.find("Food: ") != string::npos) 
            {
                meal.food = line.substr(6);
            }
            else if (line.find("Calories: ") != string::npos) 
            {
                meal.calories = stof(line.substr(10));
                meal.date = date;
                meals.push_back(meal);
            }
        }
    }
    file.close();
    return meals;
}
vector<Training> extractTrainingForDate(const string& username, const string& date) {
    vector<Training> trainings;
    string filename = username + "_training.txt";
    ifstream file(filename);
    if (!file.is_open()) return trainings;
    string line;
    bool isDateMatch = false;
    Training training;
    while (getline(file, line)) 
    {
        if (line.find("Date: ") != string::npos) 
        {
            isDateMatch = (line.substr(6) == date);
        }
        if (isDateMatch) 
        {
            if (line.find("Type: ") != string::npos) 
            {
                training.type = line.substr(6);
            }
            else if (line.find("Calories: ") != string::npos) 
            {
                training.calories = stof(line.substr(10));
                training.date = date;
                trainings.push_back(training);
            }
        }
    }
    file.close();
    return trainings;
}

void saveMealsToFile(const string& username, const vector<Meal>& meals) {
    string filename = username + "_meals.txt";
    ofstream file(filename, ios::trunc);
    for (const auto& meal : meals) 
    {
        file << "Date: " << meal.date << endl;
        file << "Food: " << meal.food << endl;
        file << "Calories: " << meal.calories << endl;
    }
    file.close();
}

void saveTrainingToFile(const string& username, const vector<Training>& trainings) {
    string filename = username + "_training.txt";
    ofstream file(filename, ios::trunc);
    for (const auto& training : trainings) 
    {
        file << "Date: " << training.date << endl;
        file << "Type: " << training.type << endl;
        file << "Calories: " << training.calories << endl;
    }
    file.close();
}
//Function that adds meal to the text file
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
    else 
    {
        cout << "Error opening the file!\n";
    }
}
//Function that allows us to edit the meals for a specific date
void editMeals(const string& username, const string& date) {
    vector<Meal> meals = extractMealsForDate(username, date);
    cout << "\n--- Meals for " << date << " ---\n";
    for (size_t i = 0; i < meals.size(); i++) 
    {
        cout << i + 1 << ". Food: " << meals[i].food << ", Calories: " << meals[i].calories << endl;
    }
    int choice;
    cout << "\nSelect a meal to edit: ";
    cin >> choice;
    if (choice > 0 && choice <= meals.size()) 
    {
        Meal& meal = meals[choice - 1];
        cout << "Editing meal: " << meal.food << ", " << meal.calories << " calories\n";
        cout << "Enter new food: ";
        cin.ignore();
        getline(cin, meal.food);
        cout << "Enter new calories: ";
        cin >> meal.calories;
    }
    else 
    {
        cout << "Invalid choice!\n";
        return;
    }
    saveMealsToFile(username, meals);
    cout << "Meals updated successfully!\n";
}

void editTraining(const string& username, const string& date) {
    vector<Training> trainings = extractTrainingForDate(username, date);
    for (size_t i = 0; i < trainings.size(); i++) 
    {
        cout << i + 1 << ". Type: " << trainings[i].type << ", Calories: " << trainings[i].calories << endl;
    }
    int choice;
    cout << "\nSelect a training to edit: ";
    cin >> choice;
    if (choice > 0 && choice <= trainings.size()) 
    {
        Training& training = trainings[choice - 1];
        cout << "Editing training: " << training.type << ", " << training.calories << " calories\n";
        cout << "Enter new training type: ";
        cin.ignore();
        getline(cin, training.type);
        cout << "Enter new calories burned: ";
        cin >> training.calories;
    }
    else 
    {
        cout << "Invalid choice!\n";
        return;
    }
    saveTrainingToFile(username, trainings);
    cout << "Trainings updated successfully!\n";
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
    while (getline(file, line)) 
    {
        if (line.find("Username: " + username) != string::npos) 
        {
            user.username = username;
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
            break;
        }
    }
    file.close();
    if (!found) 
    {
        cout << "User not found in the file!" << endl;
    }
    return user;
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
    cin.ignore();
    getline(cin, user.activityLevel);
    cout << "Enter goal (cutting/maintaining/gaining): ";
    cin >> user.goal;
    for (;;)
    {
        cout << "Enter account type (Standard/Premium): ";
        cin >> user.accountType;
        if (user.accountType == "Standard" || user.accountType == "Premium") break;
        else cout<<"Wrong input!";
    }
    ofstream file("users.txt", ios::app);
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
    ifstream file("users.txt");
    string line;
    bool found = false;
    string storedUsername, storedPassword;
    while (getline(file, line)) 
    {
        if (line.find("Username: " + username) != string::npos) 
        {
            storedUsername = username;
            getline(file, line);
            storedPassword = line.substr(line.find(": ") + 2); 
            if (storedPassword == password) 
            {
                currentLoggedInUser = username;
                cout << "Login successful! Welcome, " << username << "!\n";
                found = true;
                break;
            }
        }
    }
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
    float activityCoefficient = 1.2;
    if (user.activityLevel == "low")
    {
        activityCoefficient = 1.375;
    }
    else if (user.activityLevel == "moderate")
    {
        activityCoefficient = 1.55;
    }
    else if (user.activityLevel == "high")
    {
        activityCoefficient = 1.725;
    }
    else if (user.activityLevel == "very high")
    {
        activityCoefficient = 1.9;
    }
    else
    {
        cout << "Invalid activity level. Defaulting" << endl;
    }
    float maintenanceCalories = bmr * activityCoefficient;
    if (user.goal == "cutting") return maintenanceCalories - 550;
    else if (user.goal == "maintaining") return maintenanceCalories;
    else return maintenanceCalories + 550;
}
float caloricBalance(const string& username, const string& date)
{
    string currentDate = date;
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
    if (!trainingInputFile.is_open()) 
    {
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
    if (user.goal == "cutting") 
    {
        proteinPercentage = 0.35;
        fatPercentage = 0.30;
        carbPercentage = 0.35;
    }
    else if (user.goal == "maintaining") 
    {
        proteinPercentage = 0.25;
        fatPercentage = 0.30;
        carbPercentage = 0.45;
    }
    else if (user.goal == "gaining") 
    {
        proteinPercentage = 0.20;
        fatPercentage = 0.25;
        carbPercentage = 0.55;
    }
    else 
    {
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
    vector<Meal> meals;
    vector<Training> trainings;
    saveMealsToFile(username, meals);
    saveTrainingToFile(username,trainings);
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
    if (user.accountType == "Premium") calculateMacros(user);
}
void generateDailyReport(const string& username,const string& date)
{
    vector<Meal> meals = extractMealsForDate(username, date);
    vector<Training> trainings = extractTrainingForDate(username, date);
    float totalMealCalories = 0.0;
    float totalTrainingCalories = 0.0;
    cout << "--- Daily Report for " << date << " ---\n";
    cout << "--- Daily Report for " << date << " ---\n";
    cout << "\nMeals:\n";
    if (meals.empty())
    {
        cout << "No meals recorded for today.\n";
    }
    else
    {
        for (int i = 0; i < meals.size(); i++) 
        {
            cout << "Meal " << (i + 1) << ": Food: " << meals[i].food << ", Calories: " << meals[i].calories << endl;
            totalMealCalories += meals[i].calories;
        }
    }
    cout << "\nTraining Sessions:\n";
    if (trainings.empty())
    {
        cout << "No training recorded for today.\n";
    }
    else
    {
        for (int i = 0; i < trainings.size(); i++) 
        {
            cout << "Training " << (i + 1) << ": Type: " << trainings[i].type << ", Calories burned: " << trainings[i].calories << endl;
            totalTrainingCalories += trainings[i].calories;
        }
    }
    float caloricBalanceToday = caloricBalance(username,date);
    cout << "\nCaloric Balance for " << date << ":\n";
    cout << "Total Calories from Meals: " << totalMealCalories << " kcal\n";
    cout << "Total Calories Burned in Training: " << totalTrainingCalories << " kcal\n";
    cout << "Caloric Balance: " << caloricBalanceToday << " kcal\n";
}

//Function that deletes data from a specific file of a specific date
void deleteData(const string& username, const string& date, const string& fileType)
{
    string filename = username + "_" + fileType + ".txt";
    ifstream inputfile(filename);
    if (!inputfile.is_open())
    {
        cout << "Error opening the file!";
        return;
    }
    vector<string> lines;
    string line;
    bool isTargetDate = false;
    while (getline(inputfile, line))
    {
        if (line.find("Date: ") != string::npos)
        {
            if (line.substr(6) == date) isTargetDate = true;
            else isTargetDate = false;
        }
        if (!isTargetDate) lines.push_back(line);
    }
    inputfile.close();
    ofstream outputfile(filename);
    if (!outputfile.is_open())
    {
        cout << "Error opening the file!";
        return;
    }
    for (size_t i = 0; i < lines.size(); i++)
    {
        outputfile << lines[i] << "\n";
    }
    outputfile.close();
}
void updateData(const string& username)
{
    User user = extractUserData(username);
    cout << "\n--- Update Your Data ---\n";
    cout << "Current age: " << user.age << ". Enter new age (0 to keep current): ";
    unsigned newAge;
    cin >> newAge;
    if (newAge != 0) user.age = newAge;
    cout << "Current height: " << user.height << " cm. Enter new height (0 to keep current): ";
    float newHeight;
    cin >> newHeight;
    if (newHeight != 0) user.height = newHeight;
    cout << "Current weight: " << user.weight << " kg. Enter new weight (0 to keep current): ";
    float newWeight;
    cin >> newWeight;
    if (newWeight != 0) user.weight = newWeight;
    cout << "Current activity level: " << user.activityLevel << ". Enter new activity level (low/moderate/high/very high) (leave empty to keep current): ";
    string newActivityLevel;
    cin >> newActivityLevel;
    if (!newActivityLevel.empty()) user.activityLevel = newActivityLevel;
    cout << "Current goal: " << user.goal << ". Enter new goal (cutting/maintaining/gaining) (leave empty to keep current): ";
    string newGoal;
    cin >> newGoal;
    if (!newGoal.empty()) user.goal = newGoal;
    user.maintenanceCalories = recommendedCalories(user);

    ifstream file("users.txt");
    ofstream tempFile("temp.txt");
    string line;
    while (getline(file, line))
    {
        if (line.find("Username: " + username) != string::npos)
        {
            tempFile << "Username: " << user.username << endl;
            tempFile << "Password: " << user.password << endl;
            tempFile << "Age: " << user.age << endl;
            tempFile << "Gender: " << user.gender << endl;
            tempFile << "Height: " << user.height << " cm" << endl;
            tempFile << "Weight: " << user.weight << " kg" << endl;
            tempFile << "Activity Level: " << user.activityLevel << endl;
            tempFile << "Goal: " << user.goal << endl;
            tempFile << "Account Type: " << user.accountType << endl;
            //tempFile << "-----------------------------" << endl;
            for (int i = 0; i < 8; i++)
            {
                getline(file, line);
            }
        }
        else tempFile << line << endl;
    }
    file.close();
    tempFile.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
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
            if (!currentLoggedInUser.empty()) displayUserData(currentLoggedInUser);
            else cout << "Login failed!";
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
            cout << "\n--- User Menu ---\n";
            cout << "1. Add meal\n";
            cout << "2. Add training session\n";
            cout << "3. Edit today's meals\n";
            cout << "4. Edit today's training sessions\n";
            cout << "5. View report for previous dates\n";
            cout << "6. View today's report\n";
            cout << "7. Delete data for specific date\n";
            cout << "8. Update data\n";
            cout << "9. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) addMeal(currentLoggedInUser);
            else if (choice == 2) 
            {
                addTraining(currentLoggedInUser);
            }
            else if (choice == 3)
            {
                editMeals(currentLoggedInUser, getCurrentDate());
            }
            else if (choice == 4)
            {
                editTraining(currentLoggedInUser, getCurrentDate());
            }
            else if (choice == 5)
            {
                cout << "Please type a date (YYYY-MM-DD Format):";
                string date;
                cin >> date;
                generateDailyReport(currentLoggedInUser, date);
            }
            else if (choice == 6)
            {
                generateDailyReport(currentLoggedInUser, getCurrentDate());
            }
            else if (choice == 7)
            {
                cout << "Please type a date (YYYY-MM-DD Format): \n";
                string date; 
                cin >> date;
                deleteData(currentLoggedInUser, date, "meals");
                deleteData(currentLoggedInUser, date, "training");
                cout << "Data for date: " << date << " has been deleted!";
            }
            else if (choice == 8) 
            {
                updateData(currentLoggedInUser);
            }
            else if (choice == 9)
            {
                cout << "Logging out...\n";
                currentLoggedInUser = "";
                break;
            }
            else 
            {
                cout << "Invalid choice! Please try again.\n";
            }
        }
    } while (true);
}