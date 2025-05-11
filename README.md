# Canvas Adventures

A 2D sandbox game inspired by Terraria, built with SFML and CMake.

![Canvas Adventures](resources/character.png)

## Overview

Canvas Adventures is a 2D sandbox game where you can:
- Mine and place blocks
- Craft items and equipment
- Battle enemies
- Explore different biomes
- Build structures

## Building the Game

### Prerequisites

- CMake 3.16 or higher
- A C++17 compatible compiler
- Visual Studio 2019 or higher (on Windows)

### Building on Windows

1. Clone the repository
2. Open the solution in Visual Studio:
   - Navigate to the project folder
   - Open the CMakeLists.txt file in Visual Studio
   - Wait for CMake to configure the project

3. To build the game:
   - Save the CMakeLists.txt file (CTRL+S) to ensure the solution is built
   - Select "CanvasAdventures.exe" from the target dropdown
   - Press CTRL+F5 to build and run (without debugging)
   - Or press F5 to build and run with debugging

### Adding Files

- Add .cpp files in the src/ directory
- Add .h files in the include/ directory
- If CMake asks if you want to add the file to CMakeLists.txt, choose NO (files are automatically added)

### Refreshing Changes

- After adding a file, save the CMakeLists.txt file to refresh the solution
- For a hard refresh: close Visual Studio, delete the out folder, reopen VS, and press CTRL+S on CMakeLists.txt

## Shipping the Game

To create a release build for distribution:
1. In CMakeLists.txt, set the PRODUCTION_BUILD option to ON:
   ```cmake
   option(PRODUCTION_BUILD "Make this a production build!" ON)
   ```
2. Delete the out folder to ensure a clean build
3. Rebuild the project
4. The executable and required resources will be in the output directory

The production build will:
- Set file paths relative to the executable
- Remove the console window
- Optimize for release

## Controls

- WASD: Movement
- Space: Jump
- Left Mouse Button: Break blocks/Attack
- Right Mouse Button: Place blocks
- E: Open inventory
- ESC: Pause menu/Return to main menu

## Game Features

- Different biomes: Fields, Snow, Desert, Cave
- Day/night cycle
- Enemy spawning system
- Crafting recipes
- Item inventory
- Player equipment
- Mining and building

## Credits

Canvas Adventures game integrated with SFML CMake Setup.

Enjoy your adventure!
