#ifndef SET_H
#define SET_H

#include <string>
using ItemType = char;

class Set {
    public:
        //Constructors
        Set();
        Set(const Set &src); //copy constructor

        //Destructor
        ~Set();

        //Assignment Operator
        Set &operator= (const Set &src);

        //Accessors
        bool empty() const; 
        int size() const;
        bool get(int pos, ItemType& value) const;
        bool contains(const ItemType& value) const;
        void dump() const;

        //Mutators
        bool insert(const ItemType& value);
        bool erase(const ItemType& value);
        void swap(Set& other);

    private:
        struct Node {
            ItemType m_value;
            Node *m_prev;
            Node *m_next;
        };
        Node *head;

        int length;
};

void unite(const Set& s1, const Set& s2, Set& result);

void butNot(const Set& s1, const Set& s2, Set& result);

#endif //for SET_H