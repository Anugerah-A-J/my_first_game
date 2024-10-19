.DEFAULT_GOAL := main
VPATH = D:/c++/allegro_32/include
CPPFLAGS = -I D:/c++/allegro_32/include
CXXFLAGS = -std=gnu++17 -Werror
CXXFLAGS += -g
LDFLAGS = -L D:/c++/allegro_32/lib
LDLIBS = -lallegro -lallegro_primitives

SOURCES = $(main.cpp)

OUTPUT = ./main

clean:
	rm $(subst .cpp,.o,$(SOURCES))
	rm $(subst .cpp,.d,$(SOURCES))
	rm *.exe

run:
	$(OUTPUT)

debug:
	gdb $(OUTPUT)

main: main.cpp
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS) $(CPPFLAGS)