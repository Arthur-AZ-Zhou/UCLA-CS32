#ifndef SET_H
#define SET_H

#include <string>
using ItemType = std::string;

const int DEFAULT_MAX_ITEMS = 160;

class Set {
    public:
        //Constructor
        Set();
        // Set(const Set &src); //copy constructor

        // //Assignment Operator
        // Set &operator= (const Set &src);

        //Accessors
        bool empty() const; 
        int size() const;
        bool get(int i, ItemType& value) const;
        bool contains(const ItemType& value) const;
        void dump() const;

        //Mutators
        bool insert(const ItemType value);
        bool erase(const ItemType& value);
        void swap(Set& other);

    private: 
        ItemType array[DEFAULT_MAX_ITEMS];
        int length;

        void sort();
};

#endif //for SET_H