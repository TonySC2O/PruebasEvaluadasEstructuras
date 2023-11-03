#include <iostream>
#include "grafo.h"
#include "AutoElectrico.h"
#include "WebApp.h"
#include "NodoGrafo.h"
#include "INodo.h"
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
    grafoCarretera.addArc(&tesla, &mustang, 10);
    grafoCarretera.addArc(&bmw, &polestar, 60);
    grafoCarretera.addArc(&volvo, &mazda, 80);

    
    vector<vector<pair<INodo*, int>>> componentesConexasPeso = grafoCarretera.getConexas();

    for (int i = 0; i < componentesConexasPeso.size(); i++)
    {
        for (int j = 0; j < componentesConexasPeso.at(i).size(); j++)
        {
            if (componentesConexasPeso.at(i).size() == 1)
            {
                break;
            }
            
            if(j == 0){
                cout << "================================" << endl;
                cout << "Distancias registradas de " << 
                componentesConexasPeso.at(i).at(j).first->getNombre() << ":" << endl;
            }
            else{
                cout << componentesConexasPeso.at(i).at(j).first->getNombre() << " a " << 
                componentesConexasPeso.at(i).at(j).second << " km" << endl;
            }
        }
    }

    cout << "termino bien" << endl;

}