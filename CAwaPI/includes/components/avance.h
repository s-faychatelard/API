#ifndef CAWAPI_AVANCE
#define CAWAPI_AVANCE

#include "../component.h"

class Avance : public Component {
public:
    Avance(char* name) : Component(name) {}
    
    void start(int speed);
};

#endif