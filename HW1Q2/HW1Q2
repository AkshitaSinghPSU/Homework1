// HW1Q2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Define a type for the flights map
using FlightsMap = unordered_map<string, unordered_map<string, int>>;

// Function to print the flights map
void printFlights(const FlightsMap& flights) {
    for (const auto& entry : flights) {
        cout << "From " << entry.first << ":" << endl;
        for (const auto& dest : entry.second) {
            cout << "  To " << dest.first << ": " << dest.second << " miles" << endl;
        }
        cout << endl;
    }
}

int main() {
    // Define the flights map
    FlightsMap flights;

    // Add flights information
    flights["SCE"]["PHL"] = 160;
    flights["SCE"]["ORD"] = 640;
    flights["SCE"]["EWR"] = 220;

    // Print flights information
    printFlights(flights);

    return 0;
}
