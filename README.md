# INF584 - MyRayTracer Basic

A example solution to assignment 1 and 2.
Below are instruction on Linux or Windows. We assume CMake to be installed and shell e.g., GIT Shell or the Linux bash, to used. Alternatively, on MS Windows, once CMake is executed, one can open the solution (.sln) file located in the build directory.


## Compiling

```bash
login@computer: mkdir build
login@computer: cd build
login@computer: cmake ..
login@computer: cd ..
login@computer: cmake --build build --config Release
```

## Running 
```bash
login@computer: ./build/Release/MyRayTracer
```

This will output a file named "output.ppm" by default, that can be visualized using InfraView on windows, Feh on linux or GIMP on any platform. You can change the output file name by using the command line argument:

```bash
login@computer: ./MyRayTracer -o myfilename.ppm
```