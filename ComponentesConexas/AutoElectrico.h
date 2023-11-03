#ifndef _PERSONA_
#define _PERSONA_ 1

#include <iostream>
#include "INodo.h"

using namespace std;

class AutoElectrico : public INodo {
    public:
        AutoElectrico(string pNombre) {
            this->setId(rand()*99999999999);
            this->nombre = pNombre;
        }
        
        string getNombre() override {
            return this->nombre;
        }

        void setNombre(string pNombre) {
            this->nombre = pNombre;
        }
};

#endif