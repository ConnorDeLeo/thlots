#include <iostream>
#include <vector>
#include <string>

#include "toolCalc.hpp"

// return vector of threads you can use with given slot cutter
std::vector<toolCalc::thread> toolCalc::getThreads(float thickness, std::string unit) {
    
    // return vector
    std::vector<toolCalc::thread> returnThreads;

    // convert units to mm, yay metric!
    if(unit == "in") {
        thickness = thickness * 25.4;
    }

    for(toolCalc::thread t : threadSet) {
        if(thickness < t.pitch) {
            // add thread to return var
            returnThreads.push_back(t);
        }
    }

    return returnThreads;
}