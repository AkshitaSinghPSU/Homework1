#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Define a type for the flights map
using FlightsMap = unordered_map<string, unordered_map<string, int>>;

class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    string origin;
    string destination;
    FlightsMap flights;

public:
    // Constructor
    Plane(const string& from, const string& to) {
        pos = 0.0;
        vel = 0.0;
        distance = 0.0;
        at_SCE = true;
        origin = from;
        destination = to;

        // Add flights information
        flights["SCE"]["PHL"] = 160;
        flights["SCE"]["ORD"] = 640;
        flights["SCE"]["EWR"] = 220;
    }

    // Destructor
    ~Plane() {}

    // Function to operate the plane
    void operate(double dt) {
        if (origin == destination) {
            cout << "Plane is already at its destination." << endl;
            return;
        }

        double remaining_distance = flights[origin][destination] - distance;
        if (remaining_distance <= 0) {
            cout << "Plane has reached its destination: " << destination << endl;
            at_SCE = false;
            return;
        }

        double max_distance_covered = dt * vel;
        if (max_distance_covered >= remaining_distance) {
            cout << "Plane has reached its destination: " << destination << endl;
            at_SCE = false;
            distance = flights[origin][destination];
            return;
        }

        distance += max_distance_covered;
        pos += max_distance_covered;
    }

    // Getter for pos
    double getPos() const {
        return pos;
    }

    // Getter and Setter for vel
    double getVel() const {
        return vel;
    }

    void setVel(double velocity) {
        vel = velocity;
    }

    // Getter for origin
    string getOrigin() const {
        return origin;
    }

    // Getter for destination
    string getDestination() const {
        return destination;
    }

    // Getter for at_SCE
    bool isAtSCE() const {
        return at_SCE;
    }
};

int main() {
    // Example usage of the Plane class
    Plane plane("SCE", "PHL");
    plane.setVel(200); // Set velocity to 200 mph

    while (plane.isAtSCE()) {
        plane.operate(1.0); // Operate the plane for 1 hour
        cout << "Plane position: " << plane.getPos() << endl;
    }

    return 0;
}
