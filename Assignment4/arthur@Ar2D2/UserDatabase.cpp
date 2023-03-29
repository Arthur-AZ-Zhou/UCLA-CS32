#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

UserDatabase::UserDatabase() {
    m_loadCalled = false;
}

UserDatabase::~UserDatabase() {
    
}

bool UserDatabase::load(const string& filename) { //must be nlogn, loop thru all users and insert works
    // cout << "load called" << endl;
    if (m_loadCalled) {
        return false;
    }

    m_loadCalled = true;
    ifstream file(filename);
    // cout << "filename: " << filename << endl;

    string line;
    string userName;
    string email;
    int numMoviesWatched;
    vector<string> watchHistory; 

    // cout << "is file open? " << (file.is_open()? "Yes" : "No") << endl;
    // getline(file, line);
    // cout << line << endl;
    // getline(file, line);
    // cout << line << endl;
    // getline(file, line);
    // cout << line << endl;
    while (getline(file, line)) { 
        userName = line;
        // cout << "userName: " << userName << endl;
        if (!getline(file, line)) {
            file.close();
            return false;
        }
        email = line;
        // cout << "email: " << email << endl;
        if (!getline(file, line)) {
            file.close();
            return false;
        }
        numMoviesWatched = stoi(line);
        // cout << "numMoviesWatched: " << numMoviesWatched << endl;
        for (int i = 0; i < numMoviesWatched; i++) {
            if (!getline(file, line)) {
                file.close();
                return false;
            }
            // cout << "movieID: " <<  line << endl;
            watchHistory.push_back(line);
        }

        // cout << "NEW USER" << endl;
        User newUser(userName, email, watchHistory);
        tmmStringUser.insert(email, newUser);
        watchHistory.clear();
        getline(file, line); //move onto next line
    }

    file.close();
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const { //logn, bing chilling
    if (!tmmStringUser.find(email).is_valid()) {
        return nullptr;
    } else {
        return &(tmmStringUser.find(email).get_value());
    }
}
