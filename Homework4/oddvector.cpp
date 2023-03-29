#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

void removeOdd(vector<int>& v) {
    if (v.empty()) {
        return;
    }

    for (int i = 0; i < v.size(); i++) {
        // cout << "v[i]: " << v[i] << endl;
        if (v[i] % 2 != 0) {
            // cout << v[i] << " is odd, erasing" << endl;
            v.erase(v.begin() + i); //erase parameter has to be random access iterator
            i--;
        }
    }
}

void test() {
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    vector<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdd(x);
    assert(x.size() == 4);
    sort(x.begin(), x.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(x[k] == expect[k]);
}

int main() {
    test();
    cout << "Passed" << endl;
}