# Docs
## Compiling from Source
### Dependencies
`git`: For cloning the repository
`gcc` / `g++`: For compiling c++ code

### CLI
1. Clone the repository with `git clone https://github.com/ConnorDeLeo/thlots.git`
2. Navigate into the repo with `cd thlots/`
3. Run `g++` in order to compile, the exact command I use is `g++ src/*.cpp -I"include/" -o thlots.exe`

## Usage
### Program Usage
Run the program with `./thlots.exe`*

Once the program runs, you can choose from a couple variables.
- `thickness`: The thickness of your slot cutter or grindwheel
- `toolDiameter`: The diameter of your slot cutter or grindwheel, if you don't know this you can easily measure it with calipers pinched parallel to the sides (perpendicular is signficantly less accurate due to ease of user error)
- `tolerance`: If you want space on each side of your tool, add it now. Useful for if you expect to run a pass with a die or expect the part to wear quickly
- `units`: Millimeters or inches? the program calculates everything in inches because of the encoding on mills and unified threads
- `threadNumSel`: After inputting your tool specs, the program will print out a list of avaiable thread sizes, they each have an integer assigned to them, so type the one you'd like to use
- `maxRPM`: Input the maximum RPM your machine can run at, if the calculated spindle speed is above this, it will use the max and lower the feed rate
- `feedBackoff`: If you want to move the tool back on the thread spirals to clear chips or allow coolant to flow through the threads, type true, if not then type false
- `rapid`: If you want homing movements to use max machine feedrates, type true, if not then type false
- `safe`: The distance above the part you want the tool to lift at, at least 0.5 inches is recommended
- `percentDepth`: If you don't want to dig all the way into your part, then type the percentage as an integer 0-100. Useful for scratching where threads are going to go, if you are going to run a die as a second pass, or if you expect the part to wear quickly
- `threadLength`: The length you want to create threads down your part, if this does not match a ratio of pitch, then the program will stop the threads at 1 rotation before the max length
- `material`: The material of your part, necessary for the program to calculate feedrates and spindle speeds. There are only 4 presets of common materials to cut threads in
- `cuttingEdges`: The teeth on your slot cutter, if you have a grind wheel you need to select 0, the program handles the difference between teeth and a grindwheel (see lines 74 through 81 in `toolCalc.cpp` for logic)

* if you want to use dev variables, change the variable `useDevVars` on line 12 of `main.cpp` to `true`

### Stock Setup
1. Mill / lathe a cylinder of the "Major Diameter" of your selected thread
2. In your CNC Mill, set your tool offsets to the top of the part*
3. Set the *center* of your tool to the exact center of your part, thats your zero position / home
4. **Lift the tool to a safe distance away from the part**
5. Load the `THREAD.nc` file into your machine, turn on coolant, press start, and keep your hand on the stop button

* some grind wheels / slot cutters have a small bolt in the center, make sure to set your tool offsets to the base of the actual cutting edges