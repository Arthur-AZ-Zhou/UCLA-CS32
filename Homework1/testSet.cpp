#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main() {
    Set s1;
    s1.insert("alpha");
    s1.insert("bravo");
    s1.insert("charlie");
    s1.insert("delta");
    s1.insert("echo");
    s1.insert("foxtrot");
    s1.insert("gamma");
    s1.dump();
    s1.erase("delta");
    s1.dump();
    s1.erase("alpha");
    s1.dump();
    s1.erase("gamma");
    s1.dump();
    s1.erase("fatass");
    s1.dump();
    Set s2;
    s2.dump();
    s2.insert("hotel");
    s2.dump();
    s1.swap(s2);
    s1.dump();
    s2.dump();
    Set s3;
    s3.swap(s2);
    s2.dump();
    s3.dump();

    // Set s;
    // s.insert("b");
    // s.insert("h");
    // s.insert("k");
    // s.insert("a");
    // s.erase("h");
    // s.dump();
    // Set ss;
    // ss.insert("c");
    // ss.insert("a");
    // ss.insert("z");
    // ss.insert("i");
    // ss.insert("e");
    // ss.insert("n");
    // ss.insert("b");
    // ss.dump();
    // ss.swap(s);
    // s.dump();
    // ss.dump();

    // Set s;
    // assert(s.empty());
    // ItemType x = "arepa";
    // assert( !s.get(42, x)  &&  x == "arepa"); // x unchanged by get failure
    // s.insert("chapati");
    // assert(s.size() == 1);
    // assert(s.get(0, x)  &&  x == "chapati");
    // cout << "Passed all tests" << endl;

    // Set ss;
    // ss.insert("lavash");
    // ss.insert("roti");
    // ss.insert("chapati");
    // ss.insert("injera");
    // ss.insert("roti");
    // ss.insert("matzo");
    // ss.insert("injera");
    // assert(ss.size() == 5);  // duplicate "roti" and "injera" were not added
    // string x;
    // ss.get(0, x);
    // assert(x == "chapati");  // "chapati" is greater than exactly 0 items in ss
    // ss.get(4, x);
    // assert(x == "roti");  // "roti" is greater than exactly 4 items in ss
    // ss.get(2, x);
    // assert(x == "lavash");  // "lavash" is greater than exactly 2 items in ss

    // Set ss1;
    // ss1.insert("laobing");
    // Set ss2;
    // ss2.insert("matzo");
    // ss2.insert("pita");
    // ss1.swap(ss2);
    // assert(ss1.size() == 2  &&  ss1.contains("matzo")  &&  ss1.contains("pita")  &&
    //        ss2.size() == 1  &&  ss2.contains("laobing"));

    // Set ss;
    // ss.insert("dosa");
    // assert(!ss.contains(""));
    // ss.insert("tortilla");
    // ss.insert("");
    // ss.insert("focaccia");
    // assert(ss.contains(""));
    // ss.erase("dosa");
    // assert(ss.size() == 3  &&  ss.contains("focaccia")  &&  ss.contains("tortilla")  &&
    //             ss.contains(""));
    // string v;
    // assert(ss.get(1, v)  &&  v == "focaccia");
    // assert(ss.get(0, v)  &&  v == "");
}

// #include "Set.h"
// #include <iostream>
// #include <cassert>
// using namespace std;

// int main() {
//     Set s;
//     assert(s.empty());
//     ItemType x = 9876543;
//     assert( !s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
//     s.insert(123456789);
//     assert(s.size() == 1);
//     assert(s.get(0, x)  &&  x == 123456789);
//     cout << "Passed all tests" << endl;
// }

