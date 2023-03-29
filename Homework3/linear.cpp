// #include <iostream>
// #include <string>
// #include <cmath>
// using namespace std;

// bool somePredicate(double x) {
//     return x > 0;
// }

bool anyTrue(const double a[], int n) {

    if (n <= 0) {
        return false;
    }

    if (somePredicate(a[0])) {
        return true;
    }
        
    return anyTrue(a + 1, n - 1);
}

int countTrue(const double a[], int n) {
    if (n <= 0) {
        return 0;
    }

    return (somePredicate(a[0]))? countTrue(a + 1, n - 1) + 1 : countTrue(a + 1, n - 1);
}

int firstTrue(const double a[], int n) {
    if (n <= 0) {
        return -1;
    }

    if (somePredicate(a[0])) {
        return 0;
    } else {
        return firstTrue(a + 1, n - 1) + 1;
    }
}

int indexOfMinimum(const double a[], int n) {
    if (n <= 0) {
        return -1;
    }

    if (a[0] <= indexOfMinimum(a + 1, n - 1)) {
        return 0;
    } else {
        return indexOfMinimum(a + 1, n - 1) + 1;
    }
}

bool isIn(const double a1[], int n1, const double a2[], int n2) {
    if (n1 <= 0) {
        return true;
    }

    if (n1 > n2) {
        return false;
    }

    if (a1[0] == a2[0]) {
        return isIn(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    } else {
        return isIn(a1, n1, a2 + 1, n2 - 1);
    }

    return false;
}

// int main() {
//     int n = 5;
//     double arr[n] = {-10.1, -13, -4, 3.14, 9};
//     bool lol = anyTrue(arr, n);
//     cout << "anyTrue(arr, n): " << ((lol)? "true" : "false") << endl;

//     int nn = 5;
//     double arrr[nn] = {-10.1, -13, -4, -3.14, -9};
//     bool lol1 = anyTrue(arrr, nn);
//     cout << "anyTrue(arrr, nn): " << ((lol1)? "true" : "false") << endl;

//     int n1 = 10;
//     double arr1[n1] = {12, 3.14, -2, -1.34, 69, 420, 911, 3, -40, 0};
//     cout << "countTrue(arr1, n1): " << countTrue(arr1, n1) << endl;

//     int n2 = 7;
//     double arr2[n2] = {0, -3, 0, -2, -13, -14, 15};
//     cout << "firstTrue(arr2, n2): " << firstTrue(arr2, n2) << endl;

//     int n3 = 5;
//     double arr3[n3] = {2, 3, -4, 10, 12};
//     cout << "indexOfMinimum(arr3, n3): " << indexOfMinimum(arr3, n3) << endl;

//     int n4 = 3;
//     int n5 = 7;
//     double arr4[n4] = {10, 20, 30};
//     double arr5[n5] = {10, 50, 40, 20, 50, 40, 30};
//     cout << "isIn(arr4, n4, arr5, n5): " << (isIn(arr4, n4, arr5, n5)? "true" : "false") << endl;
// }