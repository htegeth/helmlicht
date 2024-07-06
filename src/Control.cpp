#include "Control.h"

bool Control::codeChanged = false;
unsigned long Control::currentCode = 0;

/**
 * Setzt den neuen Code und das Flag, ob sich der Wert geändert hat
 */
void Control::setCode(unsigned long newCode)
{
    if (Control::currentCode!=newCode){
        Control::currentCode=newCode;
        Control::codeChanged=true;
    }    
}

/**
 * Fragt den Wert von codeChanged ab und setzt das Flag zurück
 */
bool Control::hasCodeChanged()
{
    if(Control::codeChanged){
        Control::codeChanged = false;
        return true;
    }
    return false;
}

