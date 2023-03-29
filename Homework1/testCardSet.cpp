#include "CardSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main() {
    CardSet cs;
    assert(cs.size() == 0);
    assert(cs.add(18) && cs.add(3.14) && cs.add(42069) && cs.add(911) && !cs.add(911));
    assert(cs.size() == 4);  
    cs.print();
}