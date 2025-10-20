#define _USE_MATH_DEFINES

#include <vector>
#include <string>
#include <cmath>

#include "toolCalc.hpp"
#include "gCode.hpp"

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

toolCalc::feedsAndSpeeds calcFeedsAndSpeeds(float toolDiameter, int maxRPM, std::string material, int cuttingEdges) {

    int surfaceFeed;
    float chipLoad;
    float N;
    float F;

    if(material == "aluminum") {
        surfaceFeed = 400;
    }
    else if(material == "mild steel") {
        surfaceFeed = 300;
    }
    else if(material == "stainless") {
        surfaceFeed = 200;
    }
    else if(material == "plastic") {
        surfaceFeed = 400;
    }
    else {
        surfaceFeed = 50;
    }

    if(toolDiameter <= 0.125f) {
        chipLoad = 0.0015f;
    }
    else if(toolDiameter > 0.125f && toolDiameter <= 0.25f) {
        chipLoad = 0.0025f;
    }
    else if(toolDiameter > 0.25f && toolDiameter <= 0.5f) {
        chipLoad = 0.004f;
    }
    else {
        chipLoad = 0.007f;
    }

    N = (surfaceFeed * 12) / (M_PI * toolDiameter);

    if(N > maxRPM) {
        N = maxRPM;
        chipLoad = chipLoad / 2;
    }

    if(cuttingEdges != 0) {
        // slot cutter
        F = N * chipLoad * cuttingEdges;
    }
    else {
        // grind wheel
        F = N * toolDiameter * M_PI;
    }

    toolCalc::feedsAndSpeeds returnFeedAndSpeed;

    returnFeedAndSpeed.F = F;
    returnFeedAndSpeed.N = N;

    return returnFeedAndSpeed;
}

std::vector<std::string> toolCalc::createPath(toolCalc::thread usedThread, float thickness, float tolerance, float toolDiameter, int maxRPM, bool feedBackoff, int percentDepth, float threadLength, std::string units, std::string material, int cuttingEdges, float safe, bool rapid) {
    
    // intialize gCode obj
    gCode gc;

    // convert to inches (feed and speed calculations are standardized in inches)
    if(units == "mm") {
        thickness = thickness / 25.4;
        tolerance = tolerance / 25.4;
        toolDiameter = toolDiameter / 25.4;
        threadLength = threadLength / 25.4;
        safe = safe / 25.4;
    }
    
    float threadRad = usedThread.majorDia / 2;
    float toolRad = toolDiameter / 2;

    bool multiPass = false;
    float backoffRate = threadRad / 2;
    float currentZ = 0.0f;
    float deltaZ = 0.0f;
    float feedRate = 0.0f;
    float rpm = 0.0f;

    toolCalc::feedsAndSpeeds feedAndSpeed = calcFeedsAndSpeeds(toolDiameter, maxRPM, material, cuttingEdges);
    feedRate = feedAndSpeed.F;
    rpm = feedAndSpeed.N;

    std::vector<gCode::code> outputCode;

    outputCode = gc.setup(units, rapid, rpm, feedRate, safe);

    // depth of thread
    float h = (sqrt(3) / 2) * (usedThread.pitch);

    // arc radius using cut in
    float arcRadius = (threadRad + toolRad) - ((percentDepth / 100) * h);

    // home to the right side and dig into part by thread height (h)
    std::vector<gCode::code> digOut = gc.dig(threadRad + toolRad, (percentDepth / 100) * h);
    outputCode.insert(outputCode.end(), digOut.begin(), digOut.end());

    if(feedBackoff) {
        deltaZ = -1*(usedThread.pitch / 4);

        while((currentZ + (4 * deltaZ)) > (-1*threadLength)) {
            for (int q = 1; q <= 4; q++) {
                // in
                currentZ += deltaZ;
                outputCode.push_back(gc.quarterArc(arcRadius, currentZ, q, true));

                // out
                currentZ -= deltaZ;
                outputCode.push_back(gc.quarterArc(arcRadius, currentZ, q, false));

                // go back in
                currentZ += deltaZ;
                outputCode.push_back(gc.quarterArc(arcRadius, currentZ, q, true));
            }
        }
    }
    else {
        deltaZ = -1*usedThread.pitch;

        while(currentZ > (-1*threadLength)) {
            currentZ = currentZ + deltaZ;
            outputCode.push_back(gc.fullArc(arcRadius, currentZ));
        }
    }

    std::vector<gCode::code> releaseOut = gc.release(threadRad + toolRad, safe);
    outputCode.insert(outputCode.end(), releaseOut.begin(), releaseOut.end());

    std::vector<gCode::code> endOut = gc.end();
    outputCode.insert(outputCode.end(), endOut.begin(), endOut.end());

    std::vector<std::string> outputString = gc.toString(outputCode);
    return outputString;
}