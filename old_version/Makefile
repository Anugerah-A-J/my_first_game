.DEFAULT_GOAL := my_first_game
VPATH = D:/c++/allegro_32/include
CPPFLAGS = -I D:/c++/allegro_32/include
CXXFLAGS = -std=gnu++17 -Werror
CXXFLAGS += -g
LDFLAGS = -L D:/c++/allegro_32/lib
LDLIBS = -lallegro -lallegro_primitives

# SOURCES = $(wildcard *.cpp \
# Game_objects/*.cpp \
# Math/*.cpp \
# Shape/*.cpp)

SOURCES = $(main.cpp)

clean:
	rm $(subst .cpp,.o,$(SOURCES))
	rm $(subst .cpp,.d,$(SOURCES))
	rm *.exe

run:
	./my_first_game

debug:
	gdb ./my_first_game

my_first_game: $(subst .cpp,.o,$(SOURCES))
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

include $(subst .cpp,.d,$(SOURCES))

%.d: %.cpp
	$(CXX) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$