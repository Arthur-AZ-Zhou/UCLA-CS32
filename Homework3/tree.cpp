#include <iostream>
#include <string>
using namespace std;

int countIsIn(const double a1[], int n1, const double a2[], int n2) {
    if (n1 <= 0) {
        return 1;
    }

    if (n2 <= 0) {
        return 0;
    }

    if (a1[0] == a2[0]) {
        return countIsIn(a1, n1, a2 + 1, n2 - 1) + countIsIn(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    } else {
        return countIsIn(a1, n1, a2 + 1, n2 - 1);
    }
}

void exchange(double& x, double& y) {
    double t = x;
    x = y;
    y = t;
}

void divide(double a[], int n, double divider, int& firstNotGreater, int& firstLess) {
    if (n < 0) {
        n = 0;
    }

    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess) {
        if (a[firstUnknown] < divider) {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        } else {
            if (a[firstUnknown] > divider) {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

void order(double a[], int n) {
    if (n <= 1) {
        return;
    }

    int firstNotGreater;
    int firstLess;

    divide(a, n, a[0], firstNotGreater, firstLess);
    order(a, firstNotGreater);
    order(a + firstLess, n - firstLess);
}

// int main() {
//     double a2[7] = {10, 50, 40, 20, 50, 40, 30}; 
//     double a11[3] = {10, 20, 40};
//     double a12[3] = {10, 40, 30};
//     double a13[3] = {20, 10, 40};
//     double a14[3] = {50, 40, 30};

//     cout << "countIsIn(a11, 3, a2, 7): " << countIsIn(a11, 3, a2, 7) << endl;
//     cout << "countIsIn(a12, 3, a2, 7): " << countIsIn(a12, 3, a2, 7) << endl;
//     cout << "countIsIn(a13, 3, a2, 7): " << countIsIn(a13, 3, a2, 7) << endl;
//     cout << "countIsIn(a14, 3, a2, 7): " << countIsIn(a14, 3, a2, 7) << endl;

//     double arr[10] = {3, 5, 1, 7, 8, 4, 4, 10, -2, 3.14};
//     order(arr, 10);
//     for (int i = 0; i < 10; i++) {
//         cout << arr[i] << " ";
//     }
//     cout << endl;
// }