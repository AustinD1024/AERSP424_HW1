#include <iostream>
#include <map>          //for map container
#include <string>
#include <algorithm>    // std::swap
#include "Plane.h"
#include "Pilot.h"

int main()
{

    int FlightSpeed = 450; //mph...have to convert to miles per second

    Plane PlaneObject("SCE", "PHL"); //object of Plane

    PlaneObject.setVel(FlightSpeed);

    double timeStep = 15;
    int maxIterations = 1000;


    Pilot Pilot1("Alpha", &PlaneObject);
    Pilot Pilot2("Bravo", {});



    std::cout << "Plane created with a tail number " << Pilot1.myPlane << std::endl;

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

        PlaneObject.operate(dt); //Function Call to operate


        if (i == 0)
        {
            std::cout << "Pilot " << Pilot1.getName() << " with certificate number " << &Pilot1 << " is in control of plane: " << Pilot1.myPlane << "\n";
            std::cout << "Pilot " << Pilot2.getName() << " with certificate number " << &Pilot2 << " is in control of plane: " << Pilot2.myPlane << "\n\n";
        }
        if (i != 0 && PlaneObject.getPos() == 0 && PlaneObject.getAt_SCE() == 1)
        {
            std::swap(Pilot1.myPlane, Pilot2.myPlane);

            if (Pilot1.myPlane == 0)
            {
                std::cout << "The Plane " << Pilot2.myPlane << " is at SCE\n";
                std::cout << "Pilot " << Pilot2.getName() << " with certificate number " << &Pilot2 << " is in control of plane: " << Pilot2.myPlane << "\n";
                std::cout << "Pilot " << Pilot1.getName() << " with certificate number " << &Pilot1 << " is in control of plane: " << Pilot1.myPlane << "\n\n";

            }
            else
            {
                std::cout << "The Plane " << Pilot1.myPlane << " is at SCE\n";
                std::cout << "Pilot " << Pilot1.getName() << " with certificate number " << &Pilot1 << " is in control of plane: " << Pilot1.myPlane << "\n";
                std::cout << "Pilot " << Pilot2.getName() << " with certificate number " << &Pilot2 << " is in control of plane: " << Pilot2.myPlane << "\n\n";

            }


        }

    }

    delete Pilot1.myPlane;
    delete Pilot2.myPlane;

    return 0;
};