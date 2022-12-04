DEFAULT_GOAL = release
CXXFLAGS_DEBUG = -g3
CXXFLAGS_RELEASE = -o3
CPP_FILES = character.cpp enemy.cpp player.cpp prompt.cpp main.cpp

# Compile the main executable
release: main.cpp
	g++ $(CXXFLAGS_RELEASE) $(CPP_FILES) -o petRock

debug:
	g++ $(CXXFLAGS_DEBUG) $(CPP_FILES) -o petRock


# Remove automatically generated files
clean :
	rm -rvf *.exe *~ *.out *.dSYM *.stackdump

