#include <iostream>
#include <map>
#include <string>
#include <algorithm>    // std::swap




//**************************QUESTION 3/4 (Plane Class)*********************************//
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






//**************************QUESTION 4 (operate function/flowchart)*******************//
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
//**********************End of QUESTION 4 flowchart*******************************//






//*******************************QUESTION 6 (Pilot Class) ***************************************//
class Pilot
{
private:
    std::string name;

public:
    //Constructor
    Pilot(std::string PilotName, Plane* plane):myPlane(plane)
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





//**********************************Main Function**********************************//
int main()
{


    //******************************QUESTION 5 (input parameters)*************************//

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

    //***************************End QUESTION 5******************************************//





    //***************************QUESTION 7**********************************************//
    std::cout << "\n\n\n\n\n############################################### QUESTION 7 #####################################\n";

    Pilot Pilot1("Alpha", &PlaneObject);
    Pilot Pilot2("Bravo", {});



    std::cout << "Plane created with a tail number " << Pilot1.myPlane << std::endl;


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
    //*********************************End QUESTION 7**************************************//

 
    
    return 0;

}