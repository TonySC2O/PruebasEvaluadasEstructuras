
#include <iostream>
#include <string>
#include <vector>
#include "../Casa/Habitacion.cpp"
#include "../Casa/ParteHabitacion.cpp"

#ifndef MGHABIT

#define MGHABIT 1

class ManagerHabitaciones{
    
    public:

        Habitacion* CrearHabitacion(string pNombre){
            
            vector<string> partes = {"Piso", "Paredes", "Ventana", "Puerta", "Techo"};

            Habitacion *habitacion = new Habitacion(pNombre);

            int largo = partes.size();

            for(int i = 0; i < largo; i++){
                cout << "Creando " << partes.at(i) << endl;
                ParteHabitacion *parte = ColocarParte(partes.at(i), i+1);
                habitacion->addParte(parte);
            }
            return habitacion;
        }

        ParteHabitacion* ColocarParte(string pNombre, int pImportancia){
            ParteHabitacion* parte = new ParteHabitacion(pNombre, pImportancia);
            return parte;
        }
};

#endif