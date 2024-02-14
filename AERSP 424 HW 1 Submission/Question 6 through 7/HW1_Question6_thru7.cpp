#include <iostream>
#include <map>          //for map container
#include <string>
#include <algorithm>    // std::swap
#include "Pilot.h"
#include "Plane.h"


int main()
{

    int FlightSpeed = 450; //mph...have to convert to miles per second



    double timeStep = 15;
    int maxIterations = 1000;


    Pilot Pilot2("Bravo");
    Pilot Pilot1("Alpha");
    
    Plane PlaneObject("SCE", "PHL");//object of Plane

    Pilot1.myPlane = &PlaneObject;
    Pilot2.myPlane = {};
    
    Pilot1.myPlane->setVel(FlightSpeed);
    

   

    double dt;
    for (int i = 0; i < maxIterations; i++)
    {
        if (i == 0)
        {
            dt = 0;
        }
        else
        {
            dt = timeStep / 3600;
        }

        //Checks if Pilot 1 is not in control of the plane, if true Pilot 2 operates
        if (i != 0 && int(Pilot1.myPlane) == 0)
        {
            Pilot2.myPlane->operate(dt); //Function Call to operate
            if (Pilot2.myPlane->getPos() == 0 && Pilot2.myPlane->getAt_SCE() == 1)
            {
                std::swap(Pilot1.myPlane, Pilot2.myPlane);
                std::cout << "The Plane " << Pilot1.myPlane << " is at SCE\n";
                std::cout << "Pilot " << Pilot1.getName() << " with certificate number " << &Pilot1 << " is in control of plane: " << Pilot1.myPlane << "\n";
                std::cout << "Pilot " << Pilot2.getName() << " with certificate number " << &Pilot2 << " is in control of plane: " << Pilot2.myPlane << "\n\n";

            }
        }
        else
        {
            Pilot1.myPlane->operate(dt); //Function Call to operate
            if (Pilot1.myPlane->getPos() == 0 && Pilot1.myPlane->getAt_SCE() == 1)
            {
                std::swap(Pilot1.myPlane, Pilot2.myPlane);
                std::cout << "The Plane " << Pilot2.myPlane << " is at SCE\n";
                std::cout << "Pilot " << Pilot2.getName() << " with certificate number " << &Pilot2 << " is in control of plane: " << Pilot2.myPlane << "\n";
                std::cout << "Pilot " << Pilot1.getName() << " with certificate number " << &Pilot1 << " is in control of plane: " << Pilot1.myPlane << "\n\n";

            }
        }

        if (i == 0)
        {
            std::cout << "Pilot " << Pilot1.getName() << " with certificate number " << &Pilot1 << " is in control of plane: " << Pilot1.myPlane << "\n";
            std::cout << "Pilot " << Pilot2.getName() << " with certificate number " << &Pilot2 << " is in control of plane: " << Pilot2.myPlane << "\n\n";
        }


    }

    return 0;
};