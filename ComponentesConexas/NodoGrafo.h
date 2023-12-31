#ifndef _NODOGRAFO_
#define _NODOGRAFO_ 1
#include "Arco.h"
#include <vector>
#include "INodo.h"

using namespace std;

class NodoGrafo {
    private:
        INodo* dato;
        vector<Arco*>* listaArcos;
        bool visitado = false;
        bool procesado = false;

    public:

        NodoGrafo(INodo* pDato) {
            this->dato = pDato;
            this->listaArcos = new vector<Arco*>();
        }

        NodoGrafo() {
            this->listaArcos = new vector<Arco*>();            
        }

        void setProcesado(bool pProcesado) {
           this->procesado = pProcesado; 
        }

        bool isProcesado() {
            return procesado;
        }

        void setVisitado(bool pVisitado) {
           this->visitado = pVisitado; 
        }

        bool isVisitado() {
            return visitado;
        }

        void setInfo(INodo* pDato) {
           this->dato = pDato; 
        }

        INodo* getInfo() {
            return dato;
        }

        void addArc(Arco* pArco) {
            this->listaArcos->push_back(pArco);
        }

        vector<Arco*>* getArcs() {
            return this->listaArcos;
        }
};

#endif