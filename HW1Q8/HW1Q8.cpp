#include <iostream>
#include <string>
#include <map>
#include <algorithm>

class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    std::string origin;
    std::string destination;
    static std::map<std::string, std::map<std::string, int>> flightDistances;

public:
    // Constructor
    Plane(const std::string& from, const std::string& to) {
        origin = from;
        destination = to;
        distance = flightDistances[origin][destination];

        pos = 0;
        vel = 0;
        at_SCE = false;

        std::cout << "Plane Created at " << this << std::endl;
    }

    // Destructor
    ~Plane() {
        std::cout << "Plane Destroyed" << std::endl;
    }

    // Function to operate the plane
    void operate(double dt) {
        pos = std::min(pos + vel * dt, distance);
        at_SCE = (pos >= distance);

        switch (at_SCE) {
            case true:
                if (destination == "SCE") {
                    at_SCE = true;
                    std::swap(origin, destination);
                    pos = 0.0;
                    distance = flightDistances[origin][destination];
                } else {
                    std::cout << "Plane at " << this << " has landed at SCE." << std::endl;
                    std::swap(origin, destination);
                    pos = 0.0;
                    distance = flightDistances[origin][destination];
                }
                break;
            case false:
                break;
        }
    }

    // Getter functions
    double getPos() const {
        return pos;
    }

    double getVel() const {
        return vel;
    }

    double getDistance() const {
        return distance;
    }

    bool getAtSCE() const {
        return at_SCE;
    }

    std::string getOrigin() const {
        return origin;
    }

    std::string getDestination() const {
        return destination;
    }

    // Setter function for velocity
    void setVel(double newVel) {
        vel = newVel;
    }
};

std::map<std::string, std::map<std::string, int>> Plane::flightDistances = {
    {"SCE", {{"PHL", 160}, {"ORD", 640}, {"EWR", 220}}},
    {"PHL", {{"SCE", 160}, {"ORD", 670}, {"EWR", 80}}},
    {"ORD", {{"SCE", 640}, {"PHL", 670}, {"EWR", 750}}},
    {"EWR", {{"SCE", 220}, {"PHL", 80}, {"ORD", 750}}}
};

class Pilot {
private:
    std::string name;
    Plane* myPlane;

public:
    // Constructor function
    Pilot(const std::string& pilotName, Plane* planePtr) : name(pilotName), myPlane(planePtr) {
        std::cout << "Pilot " << name << " at " << this << " is at the gate, ready to board the plane." << std::endl;
    }

    // Destructor function
    ~Pilot() {
        std::cout << "Pilot " << name << " is out of the plane." << std::endl;
    }

    // Getter function for name
    std::string getName() const {
        return name;
    }

    // Getter function to access the plane object
    Plane* getPlane() {
        return myPlane;
    }
};

int main() {
    // Instantiate a Plane object
    Plane* plane = new Plane("SCE", "PHL");

    // Set the speed of the airplane using the set function for "velocity"
    double startVelocity = 475.0 / 3600; // Assuming a speed between 400-500 mph
    plane->setVel(startVelocity);

    // Set timestep to 75 seconds
    double timestep = 75.0;

    // Choose the maximum number of iterations between [1000, 2000]
    int maxIterations = 1200;

    // Instantiate Pilot objects for Pilot-in-Command and Co-Pilot
    Pilot* pilot1 = new Pilot("Captain John", plane);
    Pilot* pilot2 = new Pilot("Co-Pilot Dave", plane);

    // Variable to track which pilot is currently controlling the plane
    Pilot* currentPilot = pilot1;

    int i = 0;
    while (i < maxIterations) {
        // Print out the current pilot's name, memory address, and the plane's memory address
        std::cout << "Iteration " << i+1 << ": " << currentPilot->getName() << " at " << currentPilot << " is controlling the plane at " << currentPilot->getPlane() << std::endl;

        // Call the "operate" function with timestep as an input
        plane->operate(timestep);

        // Check if the plane has landed at SCE
        if (plane->getAtSCE()) {
            // Print out the memory address of the plane and indicate it is at SCE
            std::cout << "Plane at " << plane << " has landed at SCE." << std::endl;

            // Switch the current pilot
            if (currentPilot == pilot1) {
                currentPilot = pilot2;
            } else {
                currentPilot = pilot1;
            }

            // Print out the name of the new current pilot and the plane's memory address
            std::cout << "Now, " << currentPilot->getName() << " at " << currentPilot << " is controlling the plane at " << currentPilot->getPlane() << std::endl;
        }

        // Increment the iteration
        ++i;
    }

    // Clean up memory
    delete plane;
    delete pilot1;
    delete pilot2;

    return 0;
}
