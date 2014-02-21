CC = g++
INCLUDE = -I./include -I/Users/agallant/Packages/boost_1_55_0/include
CFLAGS = -O2 -Wall -std=gnu++0x
LIBS = -lfftw3 -lm -lgsl -lgslcblas /Users/agallant/Packages/boost_1_55_0/lib/libboost_system.a /Users/agallant/Packages/boost_1_55_0/lib/libboost_program_options.a 
SOURCES := $(wildcard src/*.cpp) main.cpp
OBJ_DIR = obj/
OBJ_FILES = $(addprefix $(OBJ_DIR),$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE = swift

$(EXECUTABLE): $(OBJ_FILES)
	g++ $(CFLAGS) $(INCLUDE) $(LIBS) -o $@ $^

all: $(EXECUTABLE)

# Compile all of the files in the src dir
obj/%.o: src/%.cpp
	g++ $(CFLAGS) $(INCLUDE) -c -o $@ $<

# Compile any files not in the src dir
obj/%.o: %.cpp
	g++ $(CFLAGS) $(INCLUDE) -c -o $@ $<

install:
	cp $(EXECUTABLE) ~/local/bin/$(EXECUTABLE)

uninstall:
	rm -rf ~/local/bin/$(EXECUTABLE)

# Clean up the object files
clean:
	rm -rf obj/*.o 

# Clean up everything
distclean: clean
	rm -rf $(EXECUTABLE)

# clean objs and recompile executable
rebuild: clean $(EXECUTABLE)
