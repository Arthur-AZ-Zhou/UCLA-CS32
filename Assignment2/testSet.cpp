#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main() {
    Set s;
    assert(s.empty());
    s.insert("b"); //empty list insert
    s.insert("h"); //insert at end
    s.insert("k");
    s.insert("a"); //insert at start
    s.insert("z");
    s.insert("c"); //insert at middle
    s.insert("k"); //test contains()
    s.dump(); //tests size
    assert(s.contains("a"));
    assert(!s.empty());
    assert(s.size() == 6);
    ItemType x = "noob";
    assert(s.get(0, x) && x == "a");

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

    cout << "Set s: ";
    s.dump();
    cout << "Set s1: ";
    s1.dump();
    s.swap(s1); //test swap
    cout << "Set s: ";
    s.dump();
    cout << "Set s1: ";
    s1.dump();

    Set ss1;
    ss1.insert("laobing");
    Set ss2;
    ss2.insert("matzo");
    ss2.insert("pita");
    ss1.swap(ss2);
    assert(ss1.size() == 2  &&  ss1.contains("matzo")  &&  ss1.contains("pita")  &&
           ss2.size() == 1  &&  ss2.contains("laobing"));

    Set ss;
    ss.insert("dosa");
    assert(!ss.contains(""));
    ss.insert("tortilla");
    ss.insert("");
    ss.insert("focaccia");
    assert(ss.contains(""));
    ss.dump();
    ss.erase("dosa");
    ss.dump();
    assert(ss.size() == 3  &&  ss.contains("focaccia")  &&  ss.contains("tortilla")  &&
                ss.contains(""));
    string v;
    assert(ss.get(1, v)  &&  v == "focaccia");
    assert(ss.get(0, v)  &&  v == "");

    Set uniter1;
    uniter1.insert("a");
    uniter1.insert("b");
    uniter1.insert("c");
    uniter1.insert("d");
    uniter1.insert("e");
    uniter1.dump();
    Set uniter2;
    uniter2.insert("d");
    uniter2.insert("e");
    uniter2.insert("f");
    uniter2.insert("g");
    uniter2.insert("h");
    uniter2.dump();
    Set united;
    unite(uniter1, uniter2, united);
    united.dump();
    Set oneButNotTwo;
    butNot(uniter1, uniter2, oneButNotTwo);
    oneButNotTwo.dump();

    Set num1;
    num1.insert("2");
    num1.insert("8");
    num1.insert("3");
    num1.insert("9");
    num1.insert("5");
    num1.dump();
    Set num2; 
    num2.insert("6");
    num2.insert("3");
    num2.insert("8");
    num2.insert("5");
    num2.insert("10");
    num2.dump();
    Set num1num2uniter;
    num1num2uniter.insert("69"); //test if unite() clears original list
    num1num2uniter.insert("420");
    num1num2uniter.insert("421");
    num1num2uniter.insert("422");
    num1num2uniter.insert("423");
    num1num2uniter.insert("424");
    Set num1ButNotnum2;
    num1ButNotnum2.insert("911"); //tests if butNot() clears original list
    num1ButNotnum2.insert("314");
    num1ButNotnum2.insert("315");
    num1ButNotnum2.insert("316");
    num1ButNotnum2.insert("317");
    num1ButNotnum2.insert("318");
    unite(num1, num2, num1num2uniter);
    num1num2uniter.dump();
    butNot(num1, num2, num1ButNotnum2);
    num1ButNotnum2.dump();
}