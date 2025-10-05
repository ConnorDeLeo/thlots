#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "toolCalc.hpp"
#include "gCode.hpp"
#include "utils.hpp"

toolCalc tc;
utils u;

// available thread sizes
std::vector<toolCalc::thread> threads;
std::vector<int> availableNums;
int threadNumSel;

// tool specs
float thickness;
float toolDiameter;

// machine specs
int maxRPM;

// process settings
float tolerance;
bool feedBackoff;
bool rapid;
int percentDepth;
int cuttingEdges;
float threadLength;
float safe;
std::string material;

// unit checks
std::string units;

int main() {
    std::cout << "Please input slot mill thickness: ";
    std::cin >> thickness;
    std::cout << "Please input slot mill diameter: ";
    std::cin >> toolDiameter;

    std::cout << "Please input wanted tolerance on each side of the slot mill: ";
    std::cin >> tolerance;

    std::cout << "Please input the units used (mm/in): ";
    std::cin >> units;

    threads = tc.getThreads(thickness - 2*tolerance, units);

    for(int t = 0; t < threads.size(); t++) {
        // output a list of each threadtype
        std::cout << threads[t].num << ") " << threads[t].type << ": " << threads[t].nominal << std::endl;
        availableNums.push_back(threads[t].num);
    }

    std::cout << std::endl << "Please select thread size by number: ";
    std::cin >> threadNumSel;

    int threadIndex = u.findVectorIndex(availableNums, threadNumSel);
    
    if(threadIndex != -1) {
        std::cout << "Selected thread size: " << availableNums[threadIndex] << std::endl;
    }
    else {
        std::cout << "The thread size you have selected is not in the set, please attempt again!" << std::endl;
        return -1;
    }

    std::cout << "Maximum spindle speed of your machine (rpm): ";
    std::cin >> maxRPM;

    std::cout << "Backoff on feed? (true/false): ";
    std::cin >> std::boolalpha >> feedBackoff;

    std::cout << "Use rapid? (true/false): ";
    std::cin >> std::boolalpha >> rapid;

    std::cout << "Safe distance above part for home: ";
    std::cin >> safe;

    std::cout << "Percentage of depth to go into thread (0-100): ";
    std::cin >> percentDepth;

    std::cout << "Length of threads: ";
    std::cin >> threadLength;

    std::cout << "Part material (aluminum, mild steel, stainless, plastic): ";
    std::cin >> material;

    std::cout << "Cutting edges of slot cutter (use 0 for grind wheels): ";
    std::cin >> cuttingEdges;

    std::vector<std::string> outputString = tc.createPath(threads[threadNumSel], thickness, tolerance, toolDiameter, maxRPM, feedBackoff, percentDepth, threadLength, units, material, cuttingEdges, safe, rapid);

    std::ofstream outFile("THREAD.gcode");

    if(!outFile) {
        std::cerr << "Could not open file!";
        return 1;
    }
    
    for(int s = 0; s < outputString.size(); s++) {
        outFile << outputString[s] << std::endl;
    }

    return 0;
}