#ifndef GCODE_HPP
#define GCODE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "toolCalc.hpp"

class gCode {
    public:
        // vars
        struct code {
            std::string gmfst;
            std::string opNum;
            std::string x;
            std::string y;
            std::string z;
            std::string i;
            std::string j;
            std::string k;
            std::string rpm;
            std::string feedRate;
        };

        // fixed functions
        std::vector<code> setup(std::string units, bool rapid, float rpm, float feedRate, float safe);
        std::vector<code> dig(float partAndToolRadius, float h);
        std::vector<code> release(float partAndToolRadius, float safe);
        std::vector<code> end();

        // util functions
        code resetLine(code line);
        code fullArc(float arcRadius, float z);
        code quarterArc(float arcRadius, float z, int quarter);
        std::vector<std::string> toString(std::vector<code> input);
    
    private:
        std::vector<code> outputCode;
        code currentLine;
};

#endif