#include <iostream>
#include <string>
#include "Habitacion.cpp"
#include "../Soporte/List.cpp"

using namespace std;

#ifndef CASA 

#define CASA 1

class Casa{

    private:
        List<Habitacion>* habitaciones;
    
    public:

        Casa(){
            this->habitaciones = new List<Habitacion>();
        }

        void addHabitacion(Habitacion *pHabitacion){
            this->habitaciones->add(pHabitacion);
        }
    
        void MostrarCasa(){
            
            cout << "Casa:" << endl;
            for(int i = 0; i < this->habitaciones->getSize(); i++){
                cout << "------------------------------------" << endl
                << "Habitacion: " << this->habitaciones->find(i)->getNombre() << endl
                << "Partes: " << endl;
                for(int j = 0; j < this->habitaciones->find(i)->getPartes()->getSize(); j++){
                    cout << "- " << this->habitaciones->find(i)->getPartes()->find(j)->getNombre() << endl;
                }
                
            }
        }
};

#endif