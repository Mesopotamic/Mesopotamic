# Mesopotamic

Welcome to the worlds worst game engine (In progress). The idea here is to produce a game engine entirely from the ground up, with multiple different components that users can pick and choose from. Combining all of those subprojects into a fully feature complete engine, with editor and all (eventually).

All the major projects come with a GPL3 license to encourage contributions back to the project. (And on a personal level, I'm tired of seeing open source projects not receive the support they should from the large corporations that rely on them)

Minor projects come with an MIT license to encourage adoption. These projects are designed as being drop in components, such as header only libraries 

## Contents

So it's probably a good idea to tell you what this project contains. So this particular repository is mainly just contains all the other submodules. 

## Build 

All Mesopotamic projects use CMake, I think this makes it easiest to build projects, essentially allowing users to just drop it into their pre-existing cmake projects.

There are two ways to build the projects, either all in one go from the Mesopotamic root directory, or from the individual subproject. When you're building from the root, the submodules won't need to be nested so you don't need to pull recursively. However, when you build them individually you'll pull them recursively 

### Build From Mesopotamic Root Dir

The instructions are all performed in the same terminal. 

```bash
# Pull the repository 
git clone https://github.com/Mesopotamic/Mesopotamic.git

# Navigate into the repository
cd Mesopotamic

# Pull the submodules, but NOT recursively
git submodule update --init

# Make the build directory
mkdir build
cd build

# Perform a CMake build
cmake ..
cmake --build --parallel .
```

### Build A Standalone Project

We're going to take Solomon the windowing system as an example as it will use our version of the Vulkan headers

```bash
# Pull the repository
git clone https://github.com/Mesopotamic/Solomon.git

# Navigate into Solomon
cd Solomon

# Pull the submodules RECURSIVELY
git submodule update --init --recursive

# Make the build
mkdir build
cd build

# Perform a CMake build
cmake ..
cmake --build --parallel .
```

*Just as a side note: It won't actually effect anything if you perform a recursive clone when building from the root. It will just take longer to download and take up more disk space.*

