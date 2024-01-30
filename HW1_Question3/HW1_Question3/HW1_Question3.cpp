// HW1_Question3,4,5.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <map>
#include <string>

class Plane
{
    //Private Members
private:
    double pos, vel, distance;
    bool at_SCE;
    std::string origin, destination;

    //container
    std::map < std::pair < std::string, std::string >, int > FlightMiles;

//Public Members
public:
    //constructor
    Plane(std::string from, std::string to)
    {
        
        //CHECK IF THIS IS WHERE CONTAINER PARAMETERS SHOULD BE???? SHOULD I HAVE EACH COMBINATION? Such PHL --> ORD
        FlightMiles[{"SCE", "PHL"}] = 160;
        //FlightMiles[{"PHL", "SCE"}] = 160;
        FlightMiles[{"SCE", "ORD"}] = 640;
        //FlightMiles[{"ORD", "SCE"}] = 640;
        FlightMiles[{"SCE", "EWR"}] = 220;
        //FlightMiles[{"EWR", "SCE"}] = 220;


        origin = from;
        destination = to;
        std::pair<std::string, std::string> key = { origin, destination }; //finding distance from container
        distance = FlightMiles[key];
        pos = 0;
        vel = 0;
        at_SCE = 0;
        std::cout << "Plane Created at " << this << std::endl;
    }

    //deconstructor
    ~Plane()
    {
        std::cout << "Plane Destroyed\n";
    }

    //function operate(double dt);
    void operate(double dt);

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
    //getter
    double getVel()
    {
        return vel;
    }

    void setVel(int V)
    {
        vel = V;
    }
};



void Plane::operate(double dt)
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

//QUESTION 6
class Pilot
{
private:
    std::string name;

public:
    //Constructor
    Pilot()
    {
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
    Pilot* myPlane;
};


int main()
{
    //Question 5
    std::cout << "############################################### QUESTION 5 #####################################\n";
    int FlightSpeed = 450; //mph...have to convert to miles per second

    Plane PlaneObject("SCE", "PHL"); //object of Plane

    PlaneObject.setVel(FlightSpeed);

    double timeStep = 15;
    int maxIterations = 1000; //How do you know max number of iterations???
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

    //Question 7 (NEED HELP!!!)
    //std::cout << "############################################### QUESTION 7 #####################################\n";
    //Pilot Pilot1;
    //Pilot Pilot2;
    


    
    return 0;

}
