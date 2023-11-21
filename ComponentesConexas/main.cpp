#include <iostream>
#include "grafo.h"
#include "AutoElectrico.h"
#include "NodoGrafo.h"
#include "INodo.h"
#include "GraphDiscover.h"
#include <vector>

using namespace std;

int main() {
    Grafo grafoCarretera(true);

    AutoElectrico tesla("Tesla Model 3");
    AutoElectrico nissan("Nissan Leaf");
    AutoElectrico bmw("BMW i3");
    AutoElectrico chevy("Chevy Bolt");
    AutoElectrico ford("Ford Mustang Mach-E");
    AutoElectrico vw("Volkswagen ID.3");
    AutoElectrico audi("Audi e-tron");
    AutoElectrico hyundai("Hyundai Kona Electric");
    AutoElectrico kia("Kia Soul EV");
    AutoElectrico porsche("Porsche Taycan");
    AutoElectrico rivian("Rivian R1T");
    AutoElectrico lucid("Lucid Air");
    AutoElectrico jaguar("Jaguar I-PACE");
    AutoElectrico mazda("Mazda MX-30");
    AutoElectrico volvo("Volvo XC40 Recharge");
    AutoElectrico polestar("Polestar 2");
    AutoElectrico mustang("Ford Mustang Mach-E");

    grafoCarretera.addNode(&tesla);
    grafoCarretera.addNode(&nissan);
    grafoCarretera.addNode(&bmw);
    grafoCarretera.addNode(&chevy);
    grafoCarretera.addNode(&ford);
    grafoCarretera.addNode(&vw);
    grafoCarretera.addNode(&audi);
    grafoCarretera.addNode(&hyundai);
    grafoCarretera.addNode(&kia);
    grafoCarretera.addNode(&porsche);
    grafoCarretera.addNode(&rivian);
    grafoCarretera.addNode(&lucid);
    grafoCarretera.addNode(&jaguar);
    grafoCarretera.addNode(&mazda);
    grafoCarretera.addNode(&volvo);
    grafoCarretera.addNode(&polestar);
    grafoCarretera.addNode(&mustang);

    grafoCarretera.addArc(&tesla, &nissan, 50);
    grafoCarretera.addArc(&nissan, &mustang, 10);
    grafoCarretera.addArc(&mustang, &volvo, 70);
    grafoCarretera.addArc(&volvo, &rivian, 80);
    grafoCarretera.addArc(&rivian, &tesla, 90);
    grafoCarretera.addArc(&bmw, &audi, 80);
    grafoCarretera.addArc(&audi, &polestar, 50);
    grafoCarretera.addArc(&polestar, &jaguar, 20);
    grafoCarretera.addArc(&jaguar, &hyundai, 30);
    grafoCarretera.addArc(&hyundai, &bmw, 10);
    grafoCarretera.addArc(&kia, &vw, 20);
    grafoCarretera.addArc(&lucid, &kia, 40);
    grafoCarretera.addArc(&lucid, &vw, 10);
    grafoCarretera.addArc(&porsche, &lucid, 60);
    grafoCarretera.addArc(&ford, &kia, 10);
    grafoCarretera.addArc(&mazda, &ford, 60);
    grafoCarretera.addArc(&lucid, &hyundai, 20);
    grafoCarretera.addArc(&chevy, &porsche, 80);
    grafoCarretera.addArc(&chevy, &ford, 10);

    cout << "Path: " << endl;

    vector<INodo*> camino = grafoCarretera.path(&tesla, &volvo);

    if (!camino.empty()) {
        for (INodo* nodo : camino) {
            cout << nodo->getNombre() << endl;
        }
        cout << endl;
    } else {
        cout << "No se encontró un camino entre los nodos." << endl;
    }

    cout << "DeepPath: " << endl;

    vector<INodo> deepPath = grafoCarretera.deepPath(&tesla);

    for(INodo nodo : deepPath){
        cout << nodo.getNombre() << endl;
    }
    cout << endl;
    
    cout << "Componentes conexas: " << endl;

    vector<vector<INodo*>> compConexos = grafoCarretera.getCompConexos();

    for(vector<INodo*> conexos: compConexos){
        cout << "==============" << endl;
        for(INodo* nodo: conexos){
            cout << nodo->getNombre() << endl;
        }
    }

    GraphDiscover descubridor;
    vector<Path *> *caminos = descubridor.getPathsByWarshall(&chevy, &kia, &grafoCarretera);

    // Mostrar los caminos encontrados
    for (Path* path : *caminos) {
        cout << "Camino encontrado: ";
        for(int i = 0; i < path->path.size(); i++){
            cout << path->path.at(i)->getNombre();
            if(i < path->path.size()-1){
                cout << " --> ";
            }
        }
        cout << endl;
    }

    cout << "termino bien" << endl;

}
