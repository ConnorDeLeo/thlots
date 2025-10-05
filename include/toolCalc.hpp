#ifndef TOOLCALC_HPP
#define TOOLCALC_HPP

#include <string>
#include <vector>
#include <cmath>

class toolCalc {
    public:

        // vars
        struct thread {
            int num;
            std::string type;
            std::string nominal; // nominal inches
            float tpi; // threads per inch
            float majorDia;  // inches
            float tap; // mm
            float pitch; // mm
        };
        
        struct feedsAndSpeeds {
            float F; // feedrate
            float N; // rpm
        };

        thread threadSet[81] = {
            // Unified Coarse Threads
            {0, "Unified Coarse Threads", "#1", 64, 0.073, 1.50, 0.397},
            {1, "Unified Coarse Threads", "#2", 56, 0.086, 1.90, 0.453},
            {2, "Unified Coarse Threads", "#3", 48, 0.099, 2.10, 0.529},
            {3, "Unified Coarse Threads", "#4", 40, 0.112, 2.35, 0.635},
            {4, "Unified Coarse Threads", "#5", 40, 0.125, 2.65, 0.635},
            {5, "Unified Coarse Threads", "#6", 32, 0.138, 2.85, 0.794},
            {6, "Unified Coarse Threads", "#8", 32, 0.164, 3.50, 0.794},
            {7, "Unified Coarse Threads", "#10", 24, 0.190, 4.00, 1.058},
            {8, "Unified Coarse Threads", "#12", 24, 0.216, 4.65, 1.058},
            {9, "Unified Coarse Threads", "1/4", 20, 0.250, 5.35, 1.270},
            {10, "Unified Coarse Threads", "5/16", 18, 0.313, 6.80, 1.411},
            {11, "Unified Coarse Threads", "3/8", 16, 0.375, 8.25, 1.587},
            {12, "Unified Coarse Threads", "7/16", 14, 0.438, 9.65, 1.814},
            {13, "Unified Coarse Threads", "1/2", 13, 0.500, 11.15, 1.954},
            {14, "Unified Coarse Threads", "9/16", 12, 0.563, 12.60, 2.117},
            {15, "Unified Coarse Threads", "5/8", 11, 0.625, 14.05, 2.309},
            {16, "Unified Coarse Threads", "3/4", 10, 0.750, 17.00, 2.540},
            {17, "Unified Coarse Threads", "7/8", 9, 0.875, 20.00, 2.822},
            {18, "Unified Coarse Threads", "1", 8, 1.000, 22.85, 3.175},
            {19, "Unified Coarse Threads", "1 1/8", 7, 1.125, 25.65, 3.628},
            {20, "Unified Coarse Threads", "1 1/4", 7, 1.250, 28.85, 3.628},
            {21, "Unified Coarse Threads", "1 3/8", 6, 1.375, 31.55, 4.233},
            {22, "Unified Coarse Threads", "1 1/2", 6, 1.500, 34.70, 4.233},
            {23, "Unified Coarse Threads", "1 3/4", 5, 1.750, 40.40, 5.080},
            {24, "Unified Coarse Threads", "2", 4.5, 2.000, 46.30, 5.644},
            {25, "Unified Coarse Threads", "2 1/4", 4.5, 2.250, 52.65, 5.644},
            {26, "Unified Coarse Threads", "2 1/2", 4, 2.500, 58.50, 6.350},
            {27, "Unified Coarse Threads", "2 3/4", 4, 2.750, 64.75, 6.350},
            {28, "Unified Coarse Threads", "3", 4, 3.000, 71.10, 6.350},
            {29, "Unified Coarse Threads", "3 1/4", 4, 3.250, 77.45, 6.350},
            {30, "Unified Coarse Threads", "3 1/2", 4, 3.500, 83.80, 6.350},
            {31, "Unified Coarse Threads", "3 3/4", 4, 3.750, 90.15, 6.350},
            {32, "Unified Coarse Threads", "4", 4, 4.000, 96.50, 6.350},

            // Unified Fine Threads
            {33, "Unified Fine Threads", "#0", 80, 0.060, 1.25, 0.317},
            {34, "Unified Fine Threads", "#1", 72, 0.073, 1.55, 0.353},
            {35, "Unified Fine Threads", "#2", 64, 0.086, 1.90, 0.397},
            {36, "Unified Fine Threads", "#3", 56, 0.099, 2.15, 0.453},
            {37, "Unified Fine Threads", "#4", 48, 0.112, 2.40, 0.529},
            {38, "Unified Fine Threads", "#5", 44, 0.125, 2.70, 0.577},
            {39, "Unified Fine Threads", "#6", 40, 0.138, 2.95, 0.635},
            {40, "Unified Fine Threads", "#8", 36, 0.164, 3.50, 0.705},
            {41, "Unified Fine Threads", "#10", 32, 0.190, 4.10, 0.794},
            {42, "Unified Fine Threads", "#12", 28, 0.216, 4.70, 0.907},
            {43, "Unified Fine Threads", "1/4", 28, 0.250, 5.50, 0.907},
            {44, "Unified Fine Threads", "5/16", 24, 0.313, 6.90, 1.058},
            {45, "Unified Fine Threads", "3/8", 24, 0.375, 8.50, 1.058},
            {46, "Unified Fine Threads", "7/16", 20, 0.438, 9.90, 1.270},
            {47, "Unified Fine Threads", "1/2", 20, 0.500, 11.50, 1.270},
            {48, "Unified Fine Threads", "9/16", 18, 0.563, 12.90, 1.411},
            {49, "Unified Fine Threads", "5/8", 18, 0.625, 14.50, 1.411},
            {50, "Unified Fine Threads", "3/4", 16, 0.750, 17.50, 1.587},
            {51, "Unified Fine Threads", "7/8", 14, 0.875, 20.40, 1.814},
            {52, "Unified Fine Threads", "1", 12, 1.000, 23.25, 2.117},
            {53, "Unified Fine Threads", "1 1/8", 12, 1.125, 26.50, 2.117},
            {54, "Unified Fine Threads", "1 1/4", 12, 1.250, 29.50, 2.117},
            {55, "Unified Fine Threads", "1 3/8", 12, 1.375, 32.75, 2.117},
            {56, "Unified Fine Threads", "1 1/2", 12, 1.500, 36.00, 2.117},

            // Unified Extra Fine Threads
            {57, "Unified Extra Fine Threads", "#12", 32, 0.216, 4.80, 0.794},
            {58, "Unified Extra Fine Threads", "1/4", 32, 0.250, 5.70, 0.794},
            {59, "Unified Extra Fine Threads", "5/16", 32, 0.313, 7.25, 0.794},
            {60, "Unified Extra Fine Threads", "3/8", 32, 0.375, 8.85, 0.794},
            {61, "Unified Extra Fine Threads", "7/16", 28, 0.438, 10.35, 0.907},
            {62, "Unified Extra Fine Threads", "1/2", 28, 0.500, 11.80, 0.907},
            {63, "Unified Extra Fine Threads", "9/16", 24, 0.563, 13.40, 1.058},
            {64, "Unified Extra Fine Threads", "5/8", 24, 0.625, 15.00, 1.058},
            {65, "Unified Extra Fine Threads", "11/16", 24, 0.688, 16.60, 1.058},
            {66, "Unified Extra Fine Threads", "3/4", 20, 0.750, 18.00, 1.270},
            {67, "Unified Extra Fine Threads", "13/16", 20, 0.813, 19.60, 1.270},
            {68, "Unified Extra Fine Threads", "7/8", 20, 0.875, 21.15, 1.270},
            {69, "Unified Extra Fine Threads", "15/16", 20, 0.938, 22.70, 1.270},
            {70, "Unified Extra Fine Threads", "1", 20, 1.000, 24.30, 1.270},
            {71, "Unified Extra Fine Threads", "1 1/16", 18, 1.063, 25.80, 1.411},
            {72, "Unified Extra Fine Threads", "1 1/8", 18, 1.125, 27.35, 1.411},
            {73, "Unified Extra Fine Threads", "1 1/4", 18, 1.250, 30.55, 1.411},
            {74, "Unified Extra Fine Threads", "1 5/16", 18, 1.313, 32.10, 1.411},
            {75, "Unified Extra Fine Threads", "1 3/8", 18, 1.375, 33.70, 1.411},
            {76, "Unified Extra Fine Threads", "1 7/16", 18, 1.438, 35.30, 1.411},
            {77, "Unified Extra Fine Threads", "1 1/2", 18, 1.500, 36.90, 1.411},
            {78, "Unified Extra Fine Threads", "1 9/16", 18, 1.563, 38.55, 1.411},
            {79, "Unified Extra Fine Threads", "1 5/8", 18, 1.625, 40.10, 1.411},
            {80, "Unified Extra Fine Threads", "1 11/16", 18, 1.688, 41.60, 1.411}
        };

        // functions
        std::vector<thread> getThreads(float thickness, std::string unit);
        std::vector<std::string> createPath(thread usedThread, float thickness, float tolerance, float toolDiameter, int maxRPM, bool feedBackoff, int percentDepth, float threadLength, std::string units, std::string material, int cuttingEdges, float safe, bool rapid);

    private:
        feedsAndSpeeds calcFeeds(std::string material, float rpm, int cuttingEdges);
};

#endif