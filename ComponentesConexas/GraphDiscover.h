#ifndef _GRAPHDISCOVER_
#define _GRAPHDISCOVER_ 1

#include <iostream>
#include <unordered_map>
#include "INodo.h"
#include "grafo.h"

using namespace std;

struct Path
{
    INodo *origen = nullptr;
    INodo *destino = nullptr;
    int peso;

    vector<INodo *> path;
};

struct DistancePath
{
    INodo *keyNode = nullptr;
    INodo *LastNodo = nullptr;
    bool procesado = false;
    int peso = 999999999;
};

class GraphDiscover
{
public:
    vector<Path *> *getPathsByWarshall(INodo *pOrigen, INodo *pDestino, Grafo *pGrafo)
    {
        vector<Path *> *allPaths = new vector<Path *>();

        // Obtener nodos del grafo
        vector<NodoGrafo *> nodosGrafo = pGrafo->getListaNodos();

        // Matriz de caminos para almacenar los caminos entre nodos
        vector<vector<vector<INodo *>>> caminos(pGrafo->getSize(), vector<vector<INodo *>>(pGrafo->getSize()));

        // Mapear los nodos a un índice (suponiendo que la lista de nodos ya está ordenada)
        map<INodo*, int> nodoIndice;
        int indice = 0;
        for (NodoGrafo* nodo : nodosGrafo) {
            nodoIndice[nodo->getInfo()] = indice++;
        }

        // Inicializar la matriz de caminos con caminos directos entre nodos adyacentes
        for (NodoGrafo *origen : nodosGrafo)
        {
            int indiceOrigen = nodoIndice[origen->getInfo()];

            for (Arco *arco : *(origen->getArcs()))
            {
                NodoGrafo *destino = static_cast<NodoGrafo *>(arco->getDestino());
                int indiceDestino = nodoIndice[destino->getInfo()];

                caminos[indiceOrigen][indiceDestino].push_back(origen->getInfo());
                caminos[indiceOrigen][indiceDestino].push_back(destino->getInfo());
            }
        }

        // Algoritmo de Warshall
        for (int k = 0; k < pGrafo->getSize(); ++k) {
            for (int i = 0; i < pGrafo->getSize(); ++i) {
                for (int j = 0; j < pGrafo->getSize(); ++j) {
                    if (!caminos[i][k].empty() && !caminos[k][j].empty()) {
                        vector<INodo *> nuevoCamino = caminos[i][k];
                        nuevoCamino.insert(nuevoCamino.end(), caminos[k][j].begin() + 1, caminos[k][j].end());

                        if (caminos[i][j].empty() || nuevoCamino.size() < caminos[i][j].size()) {
                            caminos[i][j] = nuevoCamino;
                            cout << "Se ha encontrado un nuevo camino entre " << nodosGrafo[i]->getInfo()->getNombre() << " y " << nodosGrafo[j]->getInfo()->getNombre() << endl;
                }
                    }
                }
            }
        }

        // Construir los objetos Path para todos los caminos encontrados desde pOrigen a pDestino
        for (int i = 0; i < pGrafo->getSize(); ++i) {
            for (int j = 0; j < pGrafo->getSize(); ++j) {
                vector<INodo *> caminoActual = caminos[i][j];
                if (!caminoActual.empty() && caminoActual.front() == pOrigen && caminoActual.back() == pDestino) {
                    Path *path = new Path();
                    path->origen = pOrigen;
                    path->destino = pDestino;
                    path->path = caminoActual;
                    allPaths->push_back(path);
                    cout << "Se ha encontrado un camino de " << pOrigen->getNombre() << " a " << pDestino->getNombre() << endl;
                }
            }
        }

        return allPaths;
    }


    /*Path *getShorterPath(INodo *pOrigen, INodo *pDestino, Grafo *pGrafo)
    {
        vector<DistancePath *> *pendingNodesV = new vector<DistancePath *>();
        vector<DistancePath *> *processedNodesF = new vector<DistancePath *>();
        DistancePath *currentMin;

        // el método usa el algoritmo de Dijkstra implementado con listas de adyacencia,
        // el cuál retorna el camino más corto de pOrigen a pDestino en el struct Path
        // currentMin has the current minimal peso Arc from pOrigin to all nodes from pendingNodesV
        // pendingNodesV will have all the nodes for the Dijkstra algorithm and acting as V array
        // proccessedNodesF will have all the proccesed nodes F, acting as the D array too
    }*/

private:
};

#endif