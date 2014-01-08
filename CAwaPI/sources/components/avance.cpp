#include "../../includes/components/avance.h"

#include "../../includes/component.h"
REGISTER_CLASS(Avance);

#include "../../includes/AwaPI.h"
#include "../../includes/device.h"

void Avance::start(int speed)
{
    Device *left = (Device*)AwaPI::getComponentById(alias((char*)"avance"));
    
    printf("%s set speed %d\n", name, speed);
}