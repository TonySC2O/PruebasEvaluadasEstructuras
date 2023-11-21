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
            actual->setProcesado(false);
            actual->setVisitado(false);
        }
    }

    NodoGrafo *findNotVisited()
    {
        NodoGrafo *result = nullptr;
        for (std::vector<NodoGrafo *>::iterator current = listaNodos.begin(); current != listaNodos.end(); ++current)
        {
            NodoGrafo *actual = (*current);
            if (!actual->isVisitado())
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
        nodo->setVisitado(true);

        vector<Arco *> *adyacentes = nodo->getArcs();
        for (int indiceArcos = 0; indiceArcos < adyacentes->size(); ++indiceArcos)
        {
            Arco *arco = adyacentes->at(indiceArcos);
            NodoGrafo *adyacente = (NodoGrafo *)arco->getDestino();
            if (!adyacente->isVisitado())
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

    vector<NodoGrafo *> getListaNodos(){
        return listaNodos;
    }

    vector<INodo> deepPath(INodo *pOrigen)
    {
        vector<INodo> result;
        resetNodes();

        NodoGrafo *nodoOrigen = getNodo(pOrigen->getId());
        if (nodoOrigen != nullptr) {
            vector<NodoGrafo*> resultNodes;
            deepPathRecursive(nodoOrigen, resultNodes);

            for (NodoGrafo* node : resultNodes) {
                result.push_back(*node->getInfo());
            }
        }

        return result;
    }
        
    vector<vector<INodo*>> getCompConexos(){
        vector<vector<INodo*>> compConexos;
        resetNodes();

        for(NodoGrafo* nodo: listaNodos){
            if(!nodo->isVisitado()){
                vector<INodo*> conexos;
                conexos.push_back(nodo->getInfo());
                getConexosNodo(nodo, &conexos);
                compConexos.push_back(conexos);
            }
        }
        return compConexos;
    }

    void getConexosNodo(NodoGrafo* nodo, vector<INodo*>* conexos){
        nodo->setVisitado(true);
        for (Arco* arco : *(nodo->getArcs()))
        {
            NodoGrafo* destino = (NodoGrafo*)arco->getDestino();
            if(!destino->isVisitado()){
                conexos->push_back(destino->getInfo());
                getConexosNodo(destino, conexos);
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
        puntoPartida->setProcesado(true);

        do
        {
            while (!nodosProcesados.empty())
            {
                NodoGrafo *actual = nodosProcesados.front();
                nodosProcesados.pop();

                actual->setVisitado(true);
                visitados++;
                result.push_back(actual->getInfo());

                vector<Arco *> *adyacentes = actual->getArcs();

                for (int indiceArcos = 0; indiceArcos < adyacentes->size(); ++indiceArcos)
                {
                    Arco *arco = adyacentes->at(indiceArcos);
                    NodoGrafo *adyacente = (NodoGrafo *)arco->getDestino();
                    if (!adyacente->isProcesado())
                    {
                        nodosProcesados.push(adyacente);
                        adyacente->setProcesado(true);
                    }
                }
            }

            if (visitados < this->getSize())
            {
                puntoPartida = this->findNotVisited();
                nodosProcesados.push(puntoPartida);
                puntoPartida->setProcesado(true);
            }
        } while (visitados < this->getSize());

        return result;
    }

    vector<INodo*> path(INodo *pOrigen, INodo *pDestino) {
        vector<INodo*> result;
        resetNodes();

        NodoGrafo *origen = this->getNodo(pOrigen->getId());
        NodoGrafo *destino = this->getNodo(pDestino->getId());

        if (origen == nullptr || destino == nullptr) {
            return result;
        }

        queue<pair<NodoGrafo*, vector<INodo*>>> nodosPorRecorrer;
        vector<INodo*> path;
        path.push_back(origen->getInfo());
        nodosPorRecorrer.push({origen, path});

        while (!nodosPorRecorrer.empty()) {
            auto current = nodosPorRecorrer.front();
            nodosPorRecorrer.pop();
            NodoGrafo *nodoActual = current.first;
            vector<INodo*> pathActual = current.second;

            if (nodoActual == destino) {
                // Se encontró un camino hacia el nodo destino
                result = pathActual;
                break;
            }

            for (Arco *arco : *(nodoActual->getArcs())) {
                NodoGrafo *adyacente = static_cast<NodoGrafo*>(arco->getDestino());

                if (!adyacente->isVisitado()) {

                    adyacente->setVisitado(true);

                    // Copiar el camino actual y agregar el nodo adyacente
                    vector<INodo*> nuevoCamino = pathActual;
                    nuevoCamino.push_back(adyacente->getInfo());

                    // Agregar el nodo adyacente junto con el nuevo camino a la cola
                    nodosPorRecorrer.push({adyacente, nuevoCamino});
                }
            }
        }

        return result;
    }

    void printCounters()
    {
        for (std::vector<NodoGrafo *>::iterator current = listaNodos.begin(); current != listaNodos.end(); ++current)
        {
            NodoGrafo *actual = (*current);
            cout << actual->getInfo()->getNombre() << " tiene " << actual->getArcs()->size() << endl;
        }
    }
};

#endif