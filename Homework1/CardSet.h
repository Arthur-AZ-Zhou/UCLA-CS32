#ifndef CARDSET_H
#define CARDSET_H

#include "Set.h"

class CardSet {
    public:
        //Constructor
        CardSet(); 

        //Accessors
        int size() const;

        void print() const;

        //Mutators
        bool add(unsigned long cardNumber);

    private:
        Set setOfCards;
};

#endif //for CARDSET_H