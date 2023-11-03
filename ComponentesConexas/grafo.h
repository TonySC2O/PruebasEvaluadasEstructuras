#ifndef _GRAFO_
#define _GRAFO_ 1
#include <vector>
#include "NodoGrafo.h"
#include "INodo.h"
#include <map>
#include <queue>
#include "Arco.h"

using namespace std;

class Grafo
{
private:
    vector<NodoGrafo *> listaNodos;
    bool esDirigido = true;
    std::map<int, NodoGrafo *> hashNodos;

    void resetNodes()
    {
        for (std::vector<NodoGrafo *>::iterator current = listaNodos.begin(); current != listaNodos.end(); ++current)
        {
            NodoGrafo *actual = (*current);
            actual->procesado = false;
            actual->visitado = false;
        }
    }

    NodoGrafo *findNotVisited()
    {
        NodoGrafo *result = nullptr;
        for (std::vector<NodoGrafo *>::iterator current = listaNodos.begin(); current != listaNodos.end(); ++current)
        {
            NodoGrafo *actual = (*current);
            if (!actual->visitado)
            {
                result = actual;
                break;
            }
        }
        return result;
    }
    
    void deepPathRecursive(NodoGrafo *nodo, vector<NodoGrafo *> &result)
    {
        result.push_back(nodo);
        nodo->visitado = true;

        vector<Arco *> *adyacentes = nodo->getArcs();
        for (int indiceArcos = 0; indiceArcos < adyacentes->size(); ++indiceArcos)
        {
            Arco *arco = adyacentes->at(indiceArcos);
            NodoGrafo *adyacente = (NodoGrafo *)arco->getDestino();
            if (!adyacente->visitado)
            {
                deepPathRecursive(adyacente, result);
            }
        }
    }

public:
    Grafo(bool pDirigido)
    {
        this->esDirigido = pDirigido;
    }

    int getSize()
    {
        return this->listaNodos.size();
    }

    void addNode(INodo *pNodo)
    {
        NodoGrafo *nuevoNodo = new NodoGrafo(pNodo);
        this->listaNodos.push_back(nuevoNodo);
        hashNodos.insert(pair<int, NodoGrafo *>(pNodo->getId(), nuevoNodo));
    }

    void addArc(NodoGrafo *pOrigen, NodoGrafo *pDestino)
    {
        this->addArc(pOrigen, pDestino, 0);
    }

    void addArc(NodoGrafo *pOrigen, NodoGrafo *pDestino, int pPeso)
    {
        Arco *newArc = new Arco(pOrigen, pDestino, pPeso);

        pOrigen->addArc(newArc);
        if (!this->esDirigido)
        {
            Arco *reverseArc = new Arco(pDestino, pOrigen, pPeso);
            pDestino->addArc(reverseArc);
        }
    }

    void addArc(INodo *pOrigen, INodo *pDestino)
    {
        this->addArc(pOrigen->getId(), pDestino->getId(), 0);
    }

    void addArc(INodo *pOrigen, INodo *pDestino, int pPeso)
    {
        this->addArc(pOrigen->getId(), pDestino->getId(), pPeso);
    }

    void addArc(int pOrigen, int pDestino)
    {
        this->addArc(pOrigen, pDestino, 0);
    }

    void addArc(int pOrigen, int pDestino, int pPeso)
    {
        this->addArc(this->getNodo(pOrigen), this->getNodo(pDestino), pPeso);
    }

    NodoGrafo *getNodo(int pId)
    {
        return hashNodos.at(pId);
    }

    vector<INodo> deepPath(INodo *pOrigen)
    { // Recorrido en profundidad
        vector<INodo> result;
        resetNodes(); // Restablecer el estado de los nodos

        NodoGrafo *nodoOrigen = getNodo(pOrigen->getId());
        if (nodoOrigen != nullptr) {
            vector<NodoGrafo*> resultNodes;
            deepPathRecursive(nodoOrigen, resultNodes);

            // Convertir los resultados de NodoGrafo a INodo
            for (NodoGrafo* node : resultNodes) {
                result.push_back(*node->getInfo());
            }
        }

        return result;
    }

    vector<vector<pair<INodo*, int>>> getConexas()
    {
        vector<vector<pair<INodo*, int>>> result;
        resetNodes(); // Restablecer el estado de los nodos

        for (NodoGrafo* nodo : listaNodos)
        {
            if (!nodo->visitado)
            {
                vector<pair<INodo*, int>> component;
                component.push_back({nodo->getInfo(), 0});
                ConexasSupport(nodo, component);
                result.push_back(component);
            }
        }

        return result;
    }

    void ConexasSupport(NodoGrafo* nodo, vector<pair<INodo*, int>>& component)
    {
        nodo->visitado = true;
        for (Arco* arco : *(nodo->getArcs()))
        {
            NodoGrafo* adyacente = (NodoGrafo*)arco->getDestino();
            component.push_back({adyacente->getInfo(), arco->getPeso()});    
            ConexasSupport(adyacente, component);
        }
    }

    
    void Deep_first_search(NodoGrafo* nodo, vector<INodo*>& componenteConexa) {
        nodo->visitado = true;
        componenteConexa.push_back(nodo->getInfo());

        vector<Arco*> *adyacentes = nodo->getArcs();
        for (int i = 0; i < adyacentes->size(); i++) {
            Arco* arco = adyacentes->at(i);
            NodoGrafo* adyacente = static_cast<NodoGrafo*>(arco->getDestino());
            if (!adyacente->visitado) {
                Deep_first_search(adyacente, componenteConexa);
            }
        }
    }

    vector<INodo *> broadPath(INodo *pOrigen)
    {
        vector<INodo *> result;
        queue<NodoGrafo *> nodosProcesados;
        int visitados = 0;

        resetNodes();

        NodoGrafo *puntoPartida = this->getNodo(pOrigen->getId());
        nodosProcesados.push(puntoPartida);
        puntoPartida->procesado = true;

        do
        {
            while (!nodosProcesados.empty())
            {
                NodoGrafo *actual = nodosProcesados.front();
                nodosProcesados.pop();

                actual->visitado = true;
                visitados++;
                result.push_back(actual->getInfo());

                vector<Arco *> *adyacentes = actual->getArcs();

                for (int indiceArcos = 0; indiceArcos < adyacentes->size(); ++indiceArcos)
                {
                    Arco *arco = adyacentes->at(indiceArcos);
                    NodoGrafo *adyacente = (NodoGrafo *)arco->getDestino();
                    if (!adyacente->procesado)
                    {
                        nodosProcesados.push(adyacente);
                        adyacente->procesado = true;
                    }
                }
            }

            if (visitados < this->getSize())
            {
                puntoPartida = this->findNotVisited();
                nodosProcesados.push(puntoPartida);
                puntoPartida->procesado = true;
            }
        } while (visitados < this->getSize());

        return result;
    }

    vector<INodo> path(INodo *pOrigen, INodo *pDestino)
    { // debe retornar un camino, el primero que encuentre estre el nodo oriegn y destino
        // en caso de que no haya camino, result se retorna vacío
        vector<INodo> result;

        return result;
    }

    void printCounters()
    {
        for (std::vector<NodoGrafo *>::iterator current = listaNodos.begin(); current != listaNodos.end(); ++current)
        {
            NodoGrafo *actual = (*current);
            cout << actual->getInfo()->getId() << " tiene " << actual->getArcs()->size() << endl;
        }
    }
};

#endif