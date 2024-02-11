#include <iostream>
#include <string>
#include "Plane.h"
#ifndef PILOT_H
#define PILOT_H

//*******************************QUESTION 6 (Pilot Class) ***************************************//
class Pilot
{
private:
    std::string name;

public:
    //Constructor
    Pilot(std::string PilotName, Plane* plane) :myPlane(plane)
    {
        name = PilotName;
        std::cout << "Pilot " << name << " with certificate number " << &name << " is at the gate, ready to board the plane.\n";
    }
    //Deconstructor
    ~Pilot()
    {
        std::cout << name << " is out of the plane.\n";
    }
    //Get function
    std::string getName()
    {
        return name;
    }
    //Pointer
    Plane* myPlane;

};
//***************************End QUESTION 6 (Pilot Class)*************************************//

#endif