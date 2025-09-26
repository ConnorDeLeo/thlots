#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "toolCalc.hpp"

toolCalc tc;

std::vector<toolCalc::thread> threads;

int main() {
    float thickness;
    std::string units;

    std::cout << "Please input slot mill thickness: ";
    std::cin >> thickness;
    std::cout << "Please input the units used (mm/in): ";
    std::cin >> units;

    threads = tc.getThreads(thickness, units);

    for(int t = 0; t < threads.size(); t++) {
        //
        std::cout << threads[t].type << ": " << threads[t].nominal << std::endl;
    }

    std::cin.get();

    return 0;
}