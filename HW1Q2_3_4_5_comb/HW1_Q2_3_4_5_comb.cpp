#include <iostream>
#include <string>
#include <map>

using namespace std;

class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    string origin;
    string destination;
    map<string, map<string, int>> flightDistances;

public:
    // Constructor
    Plane(const string& from, const string& to)
    {
        flightDistances["SCE"]["PHL"] = 160;
        flightDistances["SCE"]["ORD"] = 640;
        flightDistances["SCE"]["EWR"] = 220;

        origin = from;
        destination = to;
        distance = flightDistances[origin][destination];

        pos = 0;
        vel = 0;
        at_SCE = false;

        cout << "Plane Created at " << this << endl;
    }

    // Destructor
    ~Plane()
    {
        cout << "Plane Destroyed" << endl;
    }

    // Member function to operate the plane
    void operate(double dt)
    {
        switch (pos >= distance) {
            case false:
                pos += vel * dt;
                if (pos < 0) pos = 0;
                at_SCE = false;
                break;

            case true:
                if (destination == "SCE")
                {
                    at_SCE = true;
                    swap(origin, destination);
                    pos = 0.0;
                    distance = flightDistances[origin][destination];
                }
                else
                {
                    swap(origin, destination);
                    pos = 0.0;
                    distance = flightDistances[origin][destination];
                }
                break;
        }
    }

    // Getter functions
    double getPos() const
    {
        return pos;
    }

    double getVel() const
    {
        return vel;
    }

    double getDistance() const
    {
        return distance;
    }

    bool getAt_SCE() const
    {
        return at_SCE;
    }

    string getOrigin() const
    {
        return origin;
    }

    string getDestination() const
    {
        return destination;
    }

    // Setter function for velocity
    void setVel(double newVel)
    {
        vel = newVel;
    }
};


class Pilot {
private:
    std::string name;
    Plane* myPlane; // Pointer to Plane object

public:
    // Constructor
    Pilot(const std::string& pilotName, Plane* planePtr) : name(pilotName), myPlane(planePtr) {
        std::cout << "Pilot " << name << " at memory address " << this << " is at the gate, ready to board the plane." << std::endl;
    }

    // Destructor
    ~Pilot() {
        std::cout << "Pilot " << name << " is out of the plane." << std::endl;
    }

    // Getter function for name
    std::string getName() const {
        return name;
    }
};


int main()
{
    Plane myPlane("SCE", "PHL");

    double flightSpeed = 475.0 / 3600;
    myPlane.setVel(flightSpeed);

    double timestep = 75.0;

    int maxIterations = 1200;
    int i = 0;

    while (i < maxIterations) {
        myPlane.operate(timestep);
        cout << "Time " << timestep * (i + 1) << ", Position: " << myPlane.getPos() << " miles" << endl;
        i++;
    }

    return 0;
}
