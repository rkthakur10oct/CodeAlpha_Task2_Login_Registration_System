#include "user_utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <filesystem> // C++17 for auto directory creation

namespace fs = std::filesystem;
using namespace std;

string getMaskedPassword() {
    string pass;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            }
        } else {
            pass += ch;
            cout << '*';
        }
    }
    cout << endl;
    return pass;
}

bool isUsernameTaken(const string& username) {
    ifstream fin("data/users.txt");
    string line, user, pass;
    while (getline(fin, line)) {
        istringstream iss(line);
        iss >> user >> pass;
        if (user == username) return true;
    }
    return false;
}

void registerUser() {
    string username, password;
    cout << "\n--- Registration ---\n";
    cout << "Enter Username: ";
    cin >> username;

    if (isUsernameTaken(username)) {
        cout << "❌ Username already exists.\n";
        return;
    }

    cout << "Enter Password (min 8 chars): ";
    password = getMaskedPassword();

    if (password.length() < 8) {
        cout << "❌ Password too short.\n";
        return;
    }

    // ✅ Ensure data folder exists
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }

    ofstream fout("data/users.txt", ios::app);
    if (!fout) {
        cout << "❌ Failed to open file for writing.\n";
        return;
    }

    fout << username << " " << password << endl;
    fout.close();
    cout << "✅ Registration Successful!\n";
}

bool loginUser() {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    password = getMaskedPassword();

    // ✅ Ensure data file exists before trying to read
    if (!fs::exists("data/users.txt")) {
        cout << "❌ No users registered yet.\n";
        return false;
    }

    ifstream fin("data/users.txt");
    string line, user, pass;
    while (getline(fin, line)) {
        istringstream iss(line);
        iss >> user >> pass;
        if (user == username && pass == password) {
            cout << "✅ Login Successful!\n";
            return true;
        }
    }

    cout << "❌ Invalid username or password.\n";
    return false;
}
