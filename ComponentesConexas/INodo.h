#ifndef _INODO_
#define _INODO_ 1

using namespace std;

class INodo {
    public:
        int getId() {
            return id;
        }

        void setId(int pId) {
            this->id = pId;
        }
            
        virtual string getNombre() {
            return nombre;
        }
        
    protected:
        int id;
        string nombre;
};

#endif