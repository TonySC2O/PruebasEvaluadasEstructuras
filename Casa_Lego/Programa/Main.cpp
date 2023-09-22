#include <iostream>
#include <string>
#include <vector>
#include "ManagerCasa.cpp"
#include "../Casa/Casa.cpp"

using namespace std;

int main(){
    ManagerCasa mgCasa;

    vector<string> habitaciones {"Sala", "Cocina", "Comedor",
                                 "Cuarto", "Garage", "Baño"};
    vector<int> cantidadHabitaciones {1, 1, 1, 2, 1, 2};

    mgCasa.CrearCasa(habitaciones, cantidadHabitaciones);

    Casa *casaCreada = mgCasa.getCasa();

    casaCreada->MostrarCasa();

    return 0;
}