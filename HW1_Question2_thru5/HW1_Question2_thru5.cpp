#include <iostream>
#include <map>          //for map container
#include <string>
#include <algorithm>    // std::swap
#include "Plane.h"



//**********************************Main Function**********************************//
int main()
{

    std::cout << "############################################### QUESTION 5 #####################################\n";
    int FlightSpeed = 450; //mph...have to convert to miles per second

    Plane PlaneObject("SCE", "PHL"); //object of Plane

    PlaneObject.setVel(FlightSpeed);

    double timeStep = 15;
    int maxIterations = 1000; 

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
        std::cout << "Time: " << i * timeStep << " seconds, Position: " << PlaneObject.getPos() << " miles. \n";
    }


    return 0;

}