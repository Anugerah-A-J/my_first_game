# What is it

This is my first attempt at creating a desktop game, developed using C++ for the logic and the [Allegro5](https://liballeg.org/) library for rendering and processing input. The game is similar to pool but involves only two balls. Players take turns moving their respective balls, each starting with three lives. A player loses a life whenever their ball touches the <span style="color: red;">red line</span>. The objective is to deplete your opponent's lives by making their ball hit the <span style="color: red;">red line</span> three times. All elements on the map, including the <span style="color: red;">red line</span>, reflect the ball's movements.

# How to build it

To build the source code, you need:
1. Allegro5 package
2. CMake
3. A build system (e.g., Ninja or Make)
4. A C and C++ compiler

The building process begins by the following command:

	cmake -D CMAKE_C_COMPILER=<c-compiler> -D CMAKE_CXX_COMPILER=<c++-compiler> -G <build-system> -B build

Replace the word inside `< >` with the one you want to use. For example, if you want to use GCC and Ninja, the command would be:

<!-- cmake -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Debug -G Ninja -B build -->
	cmake -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ -G Ninja -B build

After that, run the build system. If you are using Ninja, the command will be `ninja -C build`. If you are using Make, the command will be `make -C build`.

If the build process completes successfully, you can find the executable inside the `build` directory.