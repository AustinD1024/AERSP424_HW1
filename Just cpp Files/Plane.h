#include <iostream>
#include <string>
#include <map>
#ifndef PLANE_H
#define PLANE_H
//**************************QUESTION 3/4 (Plane Class)*********************************//
class Plane
{
    //Private Members
private:
    double pos, vel, distance;
    bool at_SCE;
    std::string origin, destination;

    //*****************************CONTAINER FOR QUESTION 2**************************//
    std::map < std::pair < std::string, std::string >, int > FlightMiles;
    //*****************************CONTAINER FOR QUESTION 2**************************//

    //Public Members
public:
    //constructor
    Plane(std::string from, std::string to)
    {

        FlightMiles[{"SCE", "PHL"}] = 160;
        FlightMiles[{"SCE", "ORD"}] = 640;
        FlightMiles[{"SCE", "EWR"}] = 220;


        origin = from;
        destination = to;
        std::pair<std::string, std::string> key = { origin, destination }; //finding distance from container
        distance = FlightMiles[key];
        pos = 0;
        vel = 0;
        at_SCE = 0;
        std::cout << "Plane Created with a tail number " << this << std::endl;
    }

    //deconstructor
    ~Plane()
    {
        std::cout << "Plane Destroyed\n";
    }

    //function operate(double dt);
    void operate(double dt)
    {
        if (pos < distance)
        {
            pos += vel * dt;
            at_SCE = 0;
        }
        else if (destination == "SCE")
        {
            at_SCE = 1;
            //swap origin and destination
            std::string temp = origin;
            origin = destination;
            destination = temp;
            pos = 0;
        }
        else
        {
            //swap origin and destination
            std::string temp = origin;
            origin = destination;
            destination = temp;
            pos = 0;
        }
    }
    //**********************End of QUESTION 4 flowchart*******************************//


    //get functions for pos, origin, destination, at_SCE
    double getPos()
    {
        return pos;
    }

    std::string getOrigin()
    {
        return origin;
    }

    std::string getDestination()
    {
        return destination;
    }

    bool getAt_SCE()
    {
        return at_SCE;
    }

    //get / set functions for vel variable
    double getVel()
    {
        return vel;
    }

    void setVel(int V)
    {
        vel = V;
    }
};

//**************************End of QUESTION 3/4 (Plane Class)****************************************//
#endif