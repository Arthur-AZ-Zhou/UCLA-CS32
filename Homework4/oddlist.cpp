// #include <list>
// #include <vector>
// #include <algorithm>
// #include <iostream>
// #include <cassert>
// using namespace std;

void removeOdd(list<int>& li) {
    if (li.empty()) {
        return;
    }

    list<int> newList;
    list<int>::iterator iter;

    for (iter = li.begin(); iter != li.end(); iter++) {
        // cout << "iter: " << *iter << endl;
        if (*iter % 2 == 0) {
            // cout << *iter << " is even!" << endl;
            newList.push_back(*iter);
        }
    }

    li = newList;
}

// void test() {
//     int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
//     list<int> x(a, a+8);  // construct x from the array
//     assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
//     removeOdd(x);
//     assert(x.size() == 4);
//     vector<int> v(x.begin(), x.end());  // construct v from x
//     sort(v.begin(), v.end());
//     int expect[4] = { 2, 4, 6, 8 };
//     for (int k = 0; k < 4; k++)
//         assert(v[k] == expect[k]);
// }

// int main() {
//     test();
//     cout << "Passed" << endl;
// }