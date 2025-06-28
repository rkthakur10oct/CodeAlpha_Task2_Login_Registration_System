#include "user_utils.h"
#include <iostream>
using namespace std;

int main() {
    int choice;
    while (true) {
        cout << "\n=== Login & Registration System ===\n";
        cout << "1. Register\n2. Login\n3. Exit\nChoose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "👋 Exiting... Thank you!\n";
                return 0;
            default:
                cout << "❌ Invalid option!\n";
        }
    }
}
