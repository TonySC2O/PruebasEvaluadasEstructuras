
#include "Node.cpp"
#include <unordered_map>

#ifndef LIST 

#define LIST 1

using namespace std;

// Se crea un template para las clases Stack y  Queue para reescribir sus métodos.
template <typename T> 
class List {

    // Variables
    private:
        Node<T> *first; // El header de la lista
        Node<T> *last; // El ultimo elemento de la lista.
        Node<T> *searchPosition; // La posición a buscar en caso de necesitarla.
        unordered_map<int, Node<T>*> nodeIndex; // Variable similar a un diccionario.
        int size; // Tamaño de la lista.

    public:
        // Constructor
        List() {
            first = NULL;
            last = NULL;
            size = 0;
        }
        
        // Getter de First.
        Node<T>* getFirst() {
            return this->first;
        }

        // Getter de size.
        int getSize(){
            return size;
        }

        // Añade un elemento a la lista.
        void add(T *pData) {
            Node<T> *newNode = new Node<T>(pData);

            if (size>0) {
                this->last->setNext(newNode);
                newNode->setPrev(this->last);
            } else {
                this->first = newNode;
            }
            this->last = newNode;

            nodeIndex[size] = newNode;
            size++;
        }

        // Inserta un elemento en una posición n de la lista.
        void insert(int pPosition, T *pData) {
            
            if (pPosition<getSize() && first!=NULL) {
                Node<T> *newNodo = new Node<T>(pData);

                T* result = find(pPosition); 

                newNodo->setNext(searchPosition);
                if (searchPosition->getPrev()!=NULL) {
                    searchPosition->getPrev()->setNext(newNodo);
                    newNodo->setPrev(searchPosition->getPrev());
                    searchPosition->setPrev(newNodo);  
                } else {
                    this->first->setPrev(newNodo);
                    this->first = newNodo;
                }
                
                for(int indexToAdjust=getSize()-1; indexToAdjust>=pPosition; indexToAdjust--) {
                    if (nodeIndex.find(indexToAdjust) != nodeIndex.end()) {
                        nodeIndex[indexToAdjust+1] = nodeIndex[indexToAdjust]; 
                    }
                }

                nodeIndex[pPosition] = newNodo;
                size++;
                
            } else {
                add(pData);
            }
        }

        // Verifica si la lista está vacia o no.
        bool isEmpty(){
            return !size;
        }

        // Devuelve un puntero del elemento encontrado en n posición.
        T* find(int pPosition) {
            T* result = NULL;
            searchPosition = NULL;

            if (nodeIndex.find(pPosition) != nodeIndex.end()) {
                searchPosition = nodeIndex[pPosition];
                result = searchPosition->getElement();
            }

            return result;
        }

        // Elimina un elemento en n posición.
        T* remove(int pPosition) {
            T* result = NULL;
            if (first!=NULL && pPosition<getSize()) {
                searchPosition = first;

                if (pPosition!=0) {
                    T* data = find(pPosition);

                    searchPosition->getPrev()->setNext(searchPosition->getNext());

                    if (searchPosition==last) {
                        last = searchPosition->getPrev();
                    } else {
                        searchPosition->getNext()->setPrev(searchPosition->getPrev());
                    }
                    searchPosition->setNext(NULL);
                    searchPosition->setPrev(NULL);

                    result = searchPosition->getElement();
                } else {
                    first = first->getNext();
                    searchPosition->setNext(NULL);

                    if (first!=NULL) {
                        first->setPrev(NULL); 
                    } else {
                        last = NULL;
                    }
                    result = searchPosition->getElement();
                }

                int indexToAdjust=pPosition;
                for(; indexToAdjust<getSize()-1; indexToAdjust++) {
                    if (nodeIndex.find(indexToAdjust) != nodeIndex.end()) {
                        nodeIndex[indexToAdjust] = nodeIndex[indexToAdjust+1]; 
                    }
                }

                nodeIndex.erase(indexToAdjust+1);

                size--;
            }
            return result;
        };

        // Reinicia el nodo que busca las posiciones.
        void resetSearch() {
            searchPosition = first;
        }

        // Avanza por la lista buscando la posición deseada.
        T* next() {
            T* result = NULL;
            if (searchPosition!=NULL) {
                result = searchPosition->getElement();
                searchPosition = searchPosition->getNext();
            }
            return result;
        }
};

#endif