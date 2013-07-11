#include "../includes/AwaPI.h"
#include "../includes/components/Avance.h"

int main(void)
{
    
    try {
        if (!AwaPI::init((char*)"tcp://192.168.11.144:8687", (char*)"/Users/sylvain/Documents/Git/API/AwaPI/components.xml")) {
			//if (!AwaPI.init("tcp://127.0.0.1:8687", "/Users/sylvain/Documents/Git/API/AwaPI/components.xml")) {
            AwaPI::shutdown();
            return -1;
        }
        Avance *av = (Avance*)AwaPI::getComponentById((char*)"avance");
        av->start(100);
        //AwaPI::getComponentById((char*)"avoider")->exec((char*)"avoid");
    } catch (char* message) {
        printf("%s\n", message);
        AwaPI::shutdown();
    }
    //waitMs(60000);
    AwaPI::shutdown();
}