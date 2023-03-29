#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>

#include <iostream>
using namespace std;

/*
Ok so I think i understand this finally. An iterator should only point to one node, and be able to iterate through that node's map.
The tree should be sorted by the keytype (which we can assume has comparison operators to it). Each node should also contain a vector of values
that will need to be obtained. So if the key alr exists we can just push back the value to the key's array
*/

template <typename KeyType, typename ValueType>
class TreeMultimap {
    public:
        class Iterator { //HAS TO BE O(N) to loop thru given key value (for vector finding items it should be fine)
            public:
                Iterator() { //NEEDS TO BE INVALID SO IS_VALID CAN CHECK
                    // cout << "cooking the iterator()" << endl;
                    m_isValid = false;  
                    m_index = 0;
                    // cout << "done cooking" << endl;
                }

                Iterator(std::vector<ValueType>& vtVector) {
                    // cout << "cooking the iterator(vector)" << endl;
                    m_isValid = true;
                    m_index = 0;
                    // cout << "set primitve members" << endl;
                    m_vtVector = &vtVector;
                    // cout << "done cooking" << endl;
                }

                ValueType& get_value() const { 
                    return (*m_vtVector)[m_index];
                }

                bool is_valid() const { //valid as long as it's in vector range?
                    return m_isValid;
                }

                void advance() {
                    m_index++;
                    if (m_index >= m_vtVector->size()) {
                        m_isValid = false;
                    }
                }

            private:
                bool m_isValid;
                int m_index;
                std::vector<ValueType>* m_vtVector;   
        };

        TreeMultimap() {
            // cout << "making treemultimap rn" << endl;
            m_rootPtr = nullptr;
            // cout << "rootpointer made" << endl;
        }

        ~TreeMultimap() { //FREES ONLY THE TREE NODES, has to erase vtVector
            // cout << "treemap being destroyed rn" << endl;
            freeTree(m_rootPtr);
            // cout << "treemap destroyed successfully" << endl;
        }

        void insert(const KeyType& key, const ValueType& value) { //insert a copy of value, so do like newVal = value
            ValueType newVal = value;
            
            if (m_rootPtr == nullptr) {
                // cout << "inserted into empty tree" << endl;
                m_rootPtr = new BTNODE(key, newVal);
                return;
            }

            BTNODE *current = m_rootPtr;
            for (;;) {
                if (key == current->kt) { //if alr in list just push back value
                    current->vtVector.push_back(newVal);
                    return;
                }

                if (key < current->kt) { //if key is less than current's key go left
                    if (current->left != nullptr) { 
                        current = current->left; //if there's node to left keep going
                    } else {
                        current->left = new BTNODE(key, newVal); //otherwise just make new node
                        return;
                    }
                } else if (key > current->kt) { //if key is greater than current node's key, then go right
                    if (current->right != nullptr) { 
                        current = current->right;
                    } else {
                        current->right = new BTNODE(key, newVal);
                        return;
                    }
                }
            }
        }

        Iterator find(const KeyType& key) const { //has to be O(logn) LEVEL SEARCH, if key not found, return iterator that doesn't point to anything
            BTNODE *temp = search(key, m_rootPtr);

            if (temp == nullptr) { //if not found
                // cout << "lost child" << endl;
                Iterator invalidIter;
                return invalidIter;
            } else {
                // cout << "found child" << endl;
                Iterator validIter(temp->vtVector);
                return validIter;
            }
        }

    private: //PRIVATE IT IF YOU WANNA PRINT
        struct BTNODE {
            BTNODE(const KeyType& key, const ValueType& value) {
                kt = key;
                vtVector.push_back(value);
                left = right = nullptr;
            }

            /*~BTNODE() {
                for (int i = 0; i < vtVector.size(); i++) {
                    delete vtVector[i];
                }

                vtVector.erase();
                delete kt; //HMMMMM???
            }*/

            KeyType kt;
            std::vector<ValueType> vtVector;
            BTNODE *left, *right;
        };

        BTNODE* search(const KeyType& key, BTNODE* ptr) const {
            if (ptr == nullptr) {
                return nullptr; //not found
            } else if (key == ptr->kt) {
                return ptr;
            } else if (key < ptr->kt) {
                return search(key, ptr->left);
            } else {
                return search(key, ptr->right);
            }
        }

        void freeTree(BTNODE* cur) {
            if (cur == nullptr) { //if empty return
                return;
            }

            freeTree(cur->left);
            freeTree(cur->right);

            delete cur;
        }

        BTNODE* m_rootPtr;
};

#endif // TREEMULTIMAP_INCLUDED
