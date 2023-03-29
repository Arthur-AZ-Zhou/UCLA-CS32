#include "Set.h"
#include <iostream>

Set::Set() {
    length = 0;
    Node *dummy = new Node;

    head = dummy;
    head->m_next = head;
    head->m_prev = head;
}

Set::Set(const Set &src) {
    length = 0;
    Node *dummy = new Node;

    head = dummy;
    head->m_next = head;
    head->m_prev = head;

    for (int i = 0; i < src.length; i++) {
        ItemType tempVal;
        src.get(i, tempVal);
        insert(tempVal);
    }
}

Set::~Set() {
    Node *i;

    for (i = head->m_next; i != head; i = i->m_next) {
        delete i;
    }
    delete i; //delete the head aka dummy node
}

Set &Set::operator= (const Set &src) {
    if (&src == this) {
        return *this;
    }

    //DELETE OLD SET
    Node *i;

    for (i = head->m_next; i != head; i = i->m_next) {
        delete i;
    }
    delete i; //delete the head aka dummy node

    length = 0;
    Node *dummy = new Node;

    head = dummy;
    head->m_next = head;
    head->m_prev = head;

    for (int i = 0; i < src.length; i++) {
        ItemType tempVal;
        src.get(i, tempVal);
        insert(tempVal);
    }

    return *this;
}

bool Set::empty() const {
    return (length == 0)? true : false;
}

int Set::size() const {
    return length;
}

bool Set::get(int pos, ItemType& value) const {
    int iterator = 0;

    if (0 <= pos && pos < size()) {
        for (Node *j = head->m_next; j != head; j = j->m_next) {
            if (iterator == pos) {
                value = j->m_value;
                return true;
            }

            iterator++;
        }
    }
    
    return false;
}

bool Set::contains(const ItemType& value) const {
    for (Node *i = head->m_next; i != head; i = i->m_next) {
        if (i->m_value == value) {
            return true;
        }
    }

    return false;
}

void Set::dump() const {
    for (Node *i = head->m_next; i != head; i = i->m_next) {
        std::cerr << i->m_value << " ";
    }
    std::cerr << "| size(): " << size() << std::endl;
}

bool Set::insert(const ItemType& value) {
    if (!contains(value)) {
        Node *i;
        Node *newNode = new Node;
        newNode->m_value = value;

        if (head->m_next == head) { //if empty linkedlist (including dummy)
            newNode->m_next = head;
            newNode->m_prev = head;
            head->m_next = newNode;
            head->m_prev = newNode;

            length++;
            return true;
        }
        
        for (i = head->m_next; value > i->m_value; i = i->m_next) { //Node i will point to node after where value is supposed to be put
            if (i == head) { //make sure no infinite repeat
                break;
            }
        }
        newNode->m_next = i;
        newNode->m_prev = i->m_prev;
        i->m_prev->m_next = newNode;
        i->m_prev = newNode;

        length++;
        return true;
    }

    return false;
}

bool Set::erase(const ItemType& value) {
    if (contains(value)) {
        for (Node *i = head->m_next; i != head; i = i->m_next) {
            if (i->m_value == value) {
                i->m_prev->m_next = i->m_next;
                i->m_next->m_prev = i->m_prev;
                delete i;

                length--;
                return true;
            }
        }
    }

    return false;
}

void Set::swap(Set& other) {
    Set oldSet(*this);
    *this = other;
    other = oldSet;
}

void unite(const Set& s1, const Set& s2, Set& result) {
    int imaOrphan = result.size();

    for (int r = 0; r < imaOrphan; r++) {
        ItemType tempVal;
        result.get(0, tempVal);
        result.erase(tempVal);
    }
    //insert both into result bc insert() already accounts for repeats
    for (int i = 0; i < s1.size(); i++) {
        ItemType tempVal;
        s1.get(i, tempVal);
        result.insert(tempVal);
    }
    for (int j = 0; j < s2.size(); j++) {
        ItemType tempVal;
        s2.get(j, tempVal);
        result.insert(tempVal);
    }
}

void butNot(const Set& s1, const Set& s2, Set& result) {
    int imaOrphan = result.size();

    for (int r = 0; r < imaOrphan; r++) {
        ItemType tempVal;
        result.get(0, tempVal);
        result.erase(tempVal);
    }
    for (int i = 0; i < s1.size(); i++) {
        ItemType tempVal;
        s1.get(i, tempVal);
        if (!s2.contains(tempVal)) {
            result.insert(tempVal);
        }
    }
}