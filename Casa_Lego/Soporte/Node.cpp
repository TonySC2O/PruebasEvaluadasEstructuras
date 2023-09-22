#include <iostream>

#ifndef NODE 

#define NODE 1

using namespace std;

template <class T>
class Node {
    private:
        T *element;
        Node *next;
        Node *previous;
    
    public:
        Node() {
            element = NULL;
            next = NULL;
            previous = NULL;
        }

        Node(T *pElement) {
            this->element = pElement;
            next = NULL;
            previous = NULL;
        }

        T* getElement() {
            return element;
        }

        void seNews(T *pElement) {
            this->element = pElement;
        }

        Node* getNext() {
            return next;
        }

        void setNext(Node *pValue) {
            this->next = pValue;
        }

        Node* getPrev() {
            return previous;
        }

        void setPrev(Node *pValue) {
            this->previous = pValue;    
        }
};

#endif