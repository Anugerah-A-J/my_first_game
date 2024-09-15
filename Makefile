VPATH = D:/c++/allegro_32/include
CPPFLAGS = -I D:/c++/allegro_32/include
CXXFLAGS = -std=gnu++17 -Werror -g
LDFLAGS = -L D:/c++/allegro_32/lib
LDLIBS = -lallegro -lallegro_primitives

SOURCES = $(wildcard *.cpp)

my_first_game: $(subst .cpp,.o,$(SOURCES))
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

include $(subst .cpp,.d,$(SOURCES))

%.d: %.cpp
	$(CXX) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$