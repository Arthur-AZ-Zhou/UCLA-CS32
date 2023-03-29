#include "CardSet.h"
#include <iostream>

CardSet::CardSet() {
    
}

int CardSet::size() const {
    return setOfCards.size();
}

void CardSet::print() const {
    for (int i = 0; i < size(); i++) {
        ItemType temp;
        setOfCards.get(i, temp);
        std::cout << temp << std::endl;
    }
}

bool CardSet::add(unsigned long cardNumber) {
    return setOfCards.insert(cardNumber);
}