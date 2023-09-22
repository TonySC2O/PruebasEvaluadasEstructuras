
#include <iostream>
#include <string>
#include <string>
#include "ParteHabitacion.cpp"
#include "../Soporte/List.cpp"

using namespace std;

#ifndef HABIT 

#define HABIT 1

class Habitacion{

    private:
        string nombre;
        List<ParteHabitacion>* partes;
    
    public:

        Habitacion(string nNombre){
            this->nombre = nNombre;
            this->partes = new List<ParteHabitacion>();
        }

        void addParte(ParteHabitacion *pParte){
            this->partes->add(pParte);
        }

        string getNombre(){
            return nombre;
        }

        List<ParteHabitacion>* getPartes(){
            return partes;
        }
};

#endif