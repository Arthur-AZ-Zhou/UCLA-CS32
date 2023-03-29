#ifndef NEWSET_H
#define NEWSET_H

#include <string>
using ItemType = std::string;

const int DEFAULT_MAX_ITEMS = 160;

class Set {
    public:
        //Constructors
        Set();
        Set(int len);
        Set(const Set &src); //copy constructor

        //Destructor
        ~Set();

        //Assignment Operator
        Set &operator= (const Set &src);

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
        ItemType *array;
        int length;
        int capacity;

        void sort();
};

#endif //for NEWSET_H

