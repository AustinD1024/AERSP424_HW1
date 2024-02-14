//NOTE QUESTION 6 through 7 .cpp file did old style pointer, this code does modern pointer


#include <iostream>
#include <map>          //for map container
#include <string>
#include <algorithm>    // std::swap
#include <memory>       //for modern pointer style



//Plane Class
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




//*******************************QUESTION 6 (Pilot Class) ***************************************//
class Pilot
{
private:
    std::string name;

public:
    //Constructor
    Pilot(std::string PilotName)
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
    std::unique_ptr<Plane> myPlane{};     //HOW TO DO MODERN POINTER std::unique_ptr<Plane> myPlane; ????

};
//***************************End QUESTION 6 (Pilot Class)*************************************//



int main()
{

    int FlightSpeed = 450; //mph...have to convert to miles per second



    double timeStep = 15;
    int maxIterations = 1000;

    Pilot Pilot2("Bravo");
    Pilot Pilot1("Alpha");
    Pilot1.myPlane = std::make_unique<Plane>("SCE", "PHL");


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
        if ( i != 0 && int(Pilot1.myPlane.get()) == 0) 
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