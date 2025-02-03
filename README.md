# PurpleHole

## Project Dependencies

This project requires the following libraries to be built and run successfully:

* **SDL3** (v3.2.1)- Simple DirectMedia Layer 3, a multimedia development library.
* **SDL_image** (v3.2.0)- Image loading extension for SDL.
* **nlohmann_json** (v3.11.3)- A single-header JSON library for modern C++.

### Further Information

You can find more information about each of the dependecies on:

- **SDL3:** https://github.com/libsdl-org/SDL
- **SDL_image:** https://github.com/libsdl-org/SDL_image
- **nlohmann_json:** https://github.com/nlohmann/json

## Building the Project

This section outlines the steps to build your project successfully. Make sure you have the required dependencies installed as described in the [Project Dependencies](#project-dependencies) section.

We support building PurpleHole using CMake (v.13.3.0)

### **Compile commands:**

**Generate build** 
```bash
cmake -B build
```
This command will generate all the build files needed to in fact build the project in the "build" folder.

**Build and generate executable** 
```bash
cmake --build build
```
This command will generate the executable of the project, inside the folder "build/bin"


## Running the Project

Once you've successfully built the project following the instructions in the [Building the Project](#building-the-project) section, you can run it by following these steps:

**1. Navigate to the executable:**

Locate the bin directory, where your project's executable is placed.
```bash
cd build/bin
```

**2. Run the program:**

**Windows:**

```bash
PurpleHole.exe
```

**Linux:**
```bash
./PurpleHole.out
```

