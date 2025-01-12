# Two Balls Three Lives

## What is it

This is my first attempt at making a desktop game. It is made using C++ and the [Allegro5](https://liballeg.org/) library. The game is similar with pool, but only using two balls. Each player is assigned to move a ball alternately. Each player has three lives that decreased everytime the ball hit the <font color="red">red line</font>. The objective is to empty enemy's lives by making the enemy's ball touch the <font color="red">red line</font> three times. Everything in the map reflect the ball including the <font color="red">red line</font>.
<!-- * It is a 2D turn-based board game. -->
<!-- * It currently doesn't have assets (everything is drawn as 2D primitives). -->
<!-- * It currently only supports two-player mode and has only one map. -->
<!-- * It primarily uses the mouse for input. -->

## How to build it

To build the source code, you need:
1. Allegro5 package
2. CMake
3. A build system (e.g., Ninja or Make)
4. A C and C++ compiler

<!-- Make sure all of them are installed and available in your platform's path (`%PATH` on Windows, `$PATH` on Linux and macOS) before proceeding. -->

The building process begins by **turning on your internet connection** because CMake requires an active connection to download the Allegro5 source code. After that, run the following command:

	cmake -B build

If you don’t want to use the previously selected compiler and build system settings, use the following command instead.

	cmake -D CMAKE_C_COMPILER=<c-compiler> -D CMAKE_CXX_COMPILER=<c++-compiler> -G <build-system> -B build

Replace the word inside `< >` with the one you want to use. For example, if you want to use GCC and Ninja, the command would be:

<!-- cmake -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Debug -G Ninja -B build -->
	cmake -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ -G Ninja -B build

After that, run the build system. If you are using Ninja, the command will be `ninja -C build`. If you are using Make, the command will be `make -C build`.

If the build process completes successfully, you can find the executable inside the `build` directory.
