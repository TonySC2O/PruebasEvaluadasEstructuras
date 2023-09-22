#include <iostream>
#include <string>

using namespace std;

#ifndef PARTE 

#define PARTE 1

class ParteHabitacion{

    private:
        string nombre;
        int importancia;
        
    public:
        ParteHabitacion(string pNombre, int pImportancia){
            this->nombre = pNombre;
            this->importancia = pImportancia;
        }

        string getNombre(){
            return nombre;
        }

};

#endif