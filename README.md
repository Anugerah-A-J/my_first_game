# What is it

This is my first attempt at making a desktop game. Here are some brief descriptions of it:
* It is made using C++ and the [Allegro5](https://liballeg.org/) library.
* It is a 2D turn-based board game.
* It currently doesn't have assets (everything is drawn as 2D primitives).
* It currently only supports two-player mode and has only one map.
* It primarily uses the mouse for input.

Here are some GIFs to give an overview of the game mechanics.
* A pawn is produced by the king or a preexisting pawn.
* A pawn kills its enemy by touching it. A pawn has only one life, but the king has three lives.
* The red line stops the pawn and kills it.
* The wall and the tree block the pawn's movement.
* The blue line kills the pawn at the end of its movement.

# How to build it

To build the source code, you need:
1. CMake
2. A build system (e.g., Ninja or Make)
3. A C and C++ compiler

Make sure all of them are installed and available in your platform's path (`%PATH` on Windows, `$PATH` on Linux and macOS) before proceeding.

The building process begins by **turning on your internet connection** because CMake requires an active connection to download the Allegro5 source code. After that, run the following command:
```
cmake -B build
```

If you don’t want to use the previously selected compiler and build system settings, use the following command instead.
```
cmake -D CMAKE_C_COMPILER=<c-compiler> -D CMAKE_CXX_COMPILER=<c++-compiler> -G <build-system> -B build
```

Replace the word inside `< >` with the one you want to use. For example, if you want to use GCC and Ninja, the command would be:
```
cmake -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ -G Ninja -B build
```

After that, run the build system. If you are using Ninja, the command will be `ninja -C build`. If you are using Make, the command will be `make -C build`.

If the build process completes successfully, you can find the executable inside the `build` directory.