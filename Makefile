.DEFAULT_GOAL := main
VPATH = D:/c++/allegro_32/include
CPPFLAGS = -I D:/c++/allegro_32/include
CXXFLAGS = -std=gnu++17 -Werror
CXXFLAGS += -g
LDFLAGS = -L D:/c++/allegro_32/lib
LDFLAGS += -Wl,-allow-multiple-definition
LDLIBS = -lallegro -lallegro_primitives

SOURCES = $(wildcard *.cpp)

OUTPUT = ./main.exe

clean:
	rm $(subst .cpp,.o,$(SOURCES))
	rm $(subst .cpp,.d,$(SOURCES))
	rm *.exe

run:
	$(OUTPUT)

debug:
	gdb $(OUTPUT)

# main: $(OUTPUT)
# 	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS) $(CPPFLAGS)

main: $(subst .cpp,.o,$(SOURCES))
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

include $(subst .cpp,.d,$(SOURCES))

%.d: %.cpp
	$(CXX) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$