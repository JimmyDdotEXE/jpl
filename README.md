# Jimmy's Programming Language

JPL is a source-to-source compiler that translates JPL code to C++.

## Disclaimer

This software is a work in progress and is far from stable.
It is under fairly heavy development and may change drastically between versions.
Projects developed under one version are not guaranteed to work under another.
Sorry about that. Hopefully guaranteed stability will be feasible in the future.

## Wiki

Documention for installation, usage, and language can all be found in the project's [wiki](https://github.com/JimmyDdotEXE/jpl/wiki).

## Installation

1. **Prerequisites**

   1. **Git**

      This project requires [git](https://git-scm.com/downloads) to clone this repository before building.

   2. **C++ Compiler**

      * **Linux**

         [g++](https://gcc.gnu.org) can be installed from your disto's package manager if it is not already installed.

      * **Windows**

         [MinGW](http://www.mingw.org) can be downloaded from [here](https://osdn.net/projects/mingw/releases).

      Other [C++ compilers](https://stroustrup.com/compilers.html) should work, but may require changes to the build process.

2. **Cloning**

   `git clone https://github.com/JimmyDdotEXE/jpl`
   
   This will clone the repository into the current directory.
   You can clone the repository wherever you want, but the home directory would be the most straight forward.

3. **Build & Install**

   * **Linux**

      ```
      cd jpl
      make
      sudo make install
      ```

   * **Windows**

      ```
      cd jpl
      mingw32-make
      ```
      
        **Adding to Windows Path**
      
        To use JPL anywhere on the system, it needs to be added to the path variable.
        This step is easy, but making a mistake could cause some problems.
        Just proceed with a bit of caution and read the instructions carefully.
      
      1. Use Windows Search to search for `environment variables` and click on "Edit the system environment variables". This should open the "System Properties" window.
      2. Click "Environment Variables..." in the bottom right of the window. This should open the "Environment Variables" window.
      3. In the top half of the "Environment Variables" window, under "User variables", double-click the "Path" variable. This should open the "Edit Environment Variables" window.
      4. Click "New" in the top right of the "Edit Environment Variables" window.
      5. In the text box, enter `%USERPROFILE%\jpl`.
      6. Click "OK" in the bottom right of the "Edit Environment Variables" window.
      7. Click "OK" in the bottom right of the "Environment Variables" window.
      8. Click "OK" on the bottom of the "System Properties" window.
      9. Restart any currently open command prompts to reload the path variable.
      
      JPL should now be usable under any directory of your Windows system.

### Other Systems

JPL should compile and work on other operating systems that have a standard C++ compiler such as MacOS, Haiku, and ReactOS to name a few.
Changes to the build and install process would most likely be required on other systems.

## Usage

Assuming no errors in the JPL code of a file `example.jpl`, executing `jpl example.jpl` would result in the file `example.cpp` that could be run through a C++ compiler.

JPL is strict about indentation. Make sure to indent the body of statements and to use tabs for the indentations.

Refer to the [docs](https://github.com/JimmyDdotEXE/jpl/tree/main/docs) for examples of the features available in JPL.

## To-Do List

This is a non-exhaustive list of things to be added to JPL.

- [ ] Error Reporting
- [ ] Functions
- [ ] User Input
- [ ] Storage Classes (arrays, vectors, maybe lists)
