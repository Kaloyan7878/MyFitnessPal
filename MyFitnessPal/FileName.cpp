#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct User
{
    string username;
    string password;
    unsigned age;
    string gender;
    float height; // in cm
    float weight; // in kg
    string activityLevel; // low, medium, high
    string goal; // lose, maintain, gain weight
    string accountType; // Standard or Premium
};
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
void registerUser() {
    User user;

    cout << "=== Registration: ===" << endl;

    //Check if username is unique:
    do
    {
        cout << "Enter username: ";
        cin >> user.username;
        if (!isUsernameFree(user.username)) {
            cout << "Username not free." << endl;
        }
    } while (!isUsernameFree(user.username));

    cout << "Enter password: ";
    cin >> user.password;

    cout << "Enter age: ";
    cin >> user.age;

    cout << "Enter gener(m/f): ";
    cin >> user.gender;

    cout << "Enter height(cm): ";
    cin >> user.height;

    cout << "Enter weight(kg): ";
    cin >> user.weight;

    cout << "Enter activity level (low/moderate/high): ";
    cin >> user.activityLevel;

    cout << "Enter goal(cutting/gaining): ";
    cin >> user.goal;

    do 
    {
        cout << "Enter account type(Standard/Premium): ";
        cin >> user.accountType;
        if (user.accountType != "Standard" && user.accountType != "Premium")
        {
            cout << "Error, enter 'Standard' ??? 'Premium'." << endl;
        }
    } while (user.accountType != "Standard" && user.accountType != "Premium");

    //Adding to the file
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
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
    else {
        cout << "Error!" << endl;
    }
}
int main()
{
	string username, password;
    unsigned choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            cout << "Exiting.\n";
            break;
        case 4:
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
}