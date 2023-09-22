#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

#ifndef LEGO

#define LEGO 1

class Lego {
    private: 
        int num;

    public:
        Lego(int pNum) {
            this->num = pNum;
        }

        int getNum() {
            return num;
        }
};

#endif