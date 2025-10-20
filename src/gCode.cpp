#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "gCode.hpp"

gCode::code gCode::resetLine(gCode::code line) {
    line.gmfst = "";
    line.opNum = "";
    line.x = "";
    line.y = "";
    line.z = "";
    line.i = "";
    line.j = "";
    line.k = "";
    line.rpm = "";
    line.feedRate = "";

    return line;
}

std::vector<gCode::code> gCode::setup(std::string units, bool rapid, float rpm, float feedRate, float safe) {

    // set units
    if(units == "in") {
        currentLine.gmfst = "G";
        currentLine.opNum = "20";
    }
    else {
        currentLine.gmfst = "G";
        currentLine.opNum = "21";
    }

    outputCode.push_back(currentLine);
    currentLine = resetLine(currentLine);

    // set absolute positioning
    currentLine.gmfst = "G";
    currentLine.opNum = "90";

    outputCode.push_back(currentLine);
    currentLine = resetLine(currentLine);

    // set feed
    currentLine.gmfst = "F";
    currentLine.feedRate = std::to_string(feedRate);

    outputCode.push_back(currentLine);
    currentLine = resetLine(currentLine);

    // set rapid and home
    if(rapid == true) {
        currentLine.gmfst = "G";
        currentLine.opNum = "0";
        currentLine.z = std::to_string(safe);

        outputCode.push_back(currentLine);
        currentLine = resetLine(currentLine);

        currentLine.gmfst = "G";
        currentLine.opNum = "0";
        currentLine.x = "0";
        currentLine.y = "0";
    }
    else {
        currentLine.gmfst = "G";
        currentLine.opNum = "1";
        currentLine.z = std::to_string(safe);

        outputCode.push_back(currentLine);
        currentLine = resetLine(currentLine);

        currentLine.gmfst = "G";
        currentLine.opNum = "1";
        currentLine.x = "0";
        currentLine.y = "0";
    }

    outputCode.push_back(currentLine);
    currentLine = resetLine(currentLine);

    currentLine.gmfst = "S";
    currentLine.rpm = std::to_string(rpm);

    outputCode.push_back(currentLine);
    currentLine = resetLine(currentLine);

    return outputCode;
}

std::vector<gCode::code> gCode::dig(float partAndToolRadius, float h) {
    currentLine = resetLine(currentLine);

    std::vector<gCode::code> digOut;

    currentLine.gmfst = "G";
    currentLine.opNum = "1";
    currentLine.x = std::to_string(partAndToolRadius + (0.1 * partAndToolRadius));
    currentLine.y = "0";

    digOut.push_back(currentLine);
    currentLine = resetLine(currentLine);

    currentLine.gmfst = "G";
    currentLine.opNum = "1";
    currentLine.z = "0";

    digOut.push_back(currentLine);
    currentLine = resetLine(currentLine);

    currentLine.gmfst = "G";
    currentLine.opNum = "1";
    currentLine.x = std::to_string(partAndToolRadius - h);

    digOut.push_back(currentLine);
    currentLine = resetLine(currentLine);

    return digOut;
}

std::vector<gCode::code> gCode::release(float partAndToolRadius, float safe) {
    currentLine = resetLine(currentLine);

    std::vector<gCode::code> releaseOut;

    currentLine.gmfst = "G";
    currentLine.opNum = "1";
    currentLine.x = std::to_string(partAndToolRadius + (0.1 * partAndToolRadius));

    releaseOut.push_back(currentLine);
    currentLine = resetLine(currentLine);

    currentLine.gmfst = "G";
    currentLine.opNum = "1";
    currentLine.z = std::to_string(safe);

    releaseOut.push_back(currentLine);
    currentLine = resetLine(currentLine);

    return releaseOut;
}

std::vector<gCode::code> gCode::end() {
    currentLine = resetLine(currentLine);

    std::vector<gCode::code> endOut;

    currentLine.gmfst = "M";
    currentLine.opNum = "5";

    endOut.push_back(currentLine);
    currentLine = resetLine(currentLine);

    currentLine.gmfst = "M";
    currentLine.opNum = "2";

    endOut.push_back(currentLine);
    currentLine = resetLine(currentLine);

    return(endOut);
}

gCode::code gCode::fullArc(float arcRadius, float z) {
    currentLine = resetLine(currentLine);

    currentLine.gmfst = "G";
    currentLine.opNum = "2";
    currentLine.x = std::to_string(arcRadius);
    currentLine.y = "0";
    currentLine.z = std::to_string(z);
    currentLine.i = std::to_string(-1*arcRadius);
    currentLine.j = "0";

    std::cout << currentLine.opNum << ": " << z << std::endl;
    return currentLine;
}

gCode::code gCode::quarterArc(float arcRadius, float z, int quarter, bool down) {
    currentLine = resetLine(currentLine);

    currentLine.gmfst = "G";
    
    if(down == true) {
        currentLine.opNum = "2";

        switch(quarter) {
            case 1:
                currentLine.x = "0";
                currentLine.y = std::to_string(-1*arcRadius);
                currentLine.i = std::to_string(-1*arcRadius);
                currentLine.j = "0";
                break;

            case 2:
                currentLine.x = std::to_string(-1*arcRadius);
                currentLine.y = "0";
                currentLine.i = "0";
                currentLine.j = std::to_string(arcRadius);
                break;
            
            case 3:
                currentLine.x = "0";
                currentLine.y = std::to_string(arcRadius);
                currentLine.i = std::to_string(arcRadius);
                currentLine.j = "0";
                break;

            case 4:
                currentLine.x = std::to_string(arcRadius);
                currentLine.y = "0";
                currentLine.i = "0";
                currentLine.j = std::to_string(-1*arcRadius);
                break;
            
            default:
                break;
        }
    }
    else {
        currentLine.opNum = "3";

        switch(quarter) {
            case 1:
                currentLine.x = std::to_string(arcRadius);
                currentLine.y = "0";
                currentLine.i = "0";
                currentLine.j = std::to_string(arcRadius);
                break;

            case 2:
                currentLine.x = "0";
                currentLine.y = std::to_string(-1*arcRadius);
                currentLine.i = std::to_string(arcRadius);
                currentLine.j = "0";
                break;
            
            case 3:
                currentLine.x = std::to_string(-1*arcRadius);
                currentLine.y = "0";
                currentLine.i = "0";
                currentLine.j = std::to_string(-1*arcRadius);
                break;

            case 4:
                currentLine.x = "0";
                currentLine.y = std::to_string(arcRadius);
                currentLine.i = std::to_string(-1*arcRadius);
                currentLine.j = "0";
                break;
            
            default:
                break;
        }
    }

    currentLine.z = std::to_string(z);

    std::cout << currentLine.opNum << ") Z: " << z << ", J:" << currentLine.j << std::endl;
    return currentLine;
}

std::vector<std::string> gCode::toString(std::vector<gCode::code> input) {
    std::string currentString;
    std::vector<std::string> currentOut;

    for(int s = 0; s < input.size(); s++) {
        currentString = input[s].gmfst;
        
        if(input[s].opNum != "") {
            currentString = currentString + input[s].opNum;
        }
        if(input[s].x != "") {
            currentString = currentString + " X" + input[s].x;
        }
        if(input[s].y != "") {
            currentString = currentString + " Y" + input[s].y;
        }
        if(input[s].z != "") {
            currentString = currentString + " Z" + input[s].z;
        }
        if(input[s].i != "") {
            currentString = currentString + " I" + input[s].i;
        }
        if(input[s].j != "") {
            currentString = currentString + " J" + input[s].j;
        }
        if(input[s].k != "") {
            currentString = currentString + " K" + input[s].k;
        }
        if(input[s].rpm != "") {
            currentString = currentString + input[s].rpm;
        }
        if(input[s].feedRate != "") {
            currentString = currentString + input[s].feedRate;
        }

        currentOut.push_back(currentString);
        currentString = "";
    }

    return currentOut;
}