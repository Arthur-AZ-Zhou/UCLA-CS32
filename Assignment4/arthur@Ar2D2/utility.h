#ifndef UTILITY_H
#define UTILITY_H

#include "User.h"
#include "Movie.h"
#include "treemm.h"

#include <vector>
#include <string>
#include <iostream>
using namespace std;    

class utility {
    public: 
        static void printStringVector(const vector<string>& printVector);
        static void printUser(const User& user);
        static void printMovie(const Movie& movie);
        // static void printTreeIntUser(TreeMultimap<int, User>::BTNODE *cur);
        static void printIterForIntUser(TreeMultimap<int, User>::Iterator& it);
    private:

};

#endif //UTILITY_H