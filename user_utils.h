#ifndef USER_UTILS_H
#define USER_UTILS_H

#include <string>
using namespace std;

bool isUsernameTaken(const string& username);
void registerUser();
bool loginUser();
string getMaskedPassword();

#endif
