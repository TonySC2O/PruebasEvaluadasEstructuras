
#include <iostream>
#include <string>
#include <vector>
#include "../Casa/Casa.cpp"
#include "ManagerHabitaciones.cpp"

using namespace std;

#ifndef MGCASA 

#define MGCASA 1

class ManagerCasa{

    private:
        Casa *casa;
        ManagerHabitaciones *mgHabitaciones;
    
    public:
        ManagerCasa(){
            casa = new Casa();
        }

        void CrearCasa(vector<string> pHabitaciones, vector<int> pCantidadHabit){
            for(int i = 0; i < pHabitaciones.size(); i++){
                for(int j = 0; j < pCantidadHabit.at(i); j++){
                    cout << "----------------------------" << endl;
                    cout << "Creando " << pHabitaciones.at(i) << "..." << endl;
                    this->casa->addHabitacion(this->mgHabitaciones->CrearHabitacion(pHabitaciones.at(i)));
                }
            }
        }

        Casa* getCasa(){
            return casa;
        }
};

#endif