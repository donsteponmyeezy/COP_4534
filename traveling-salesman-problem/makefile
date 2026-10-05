# Compiler and flags
CXX = g++
# -O3 is mandatory to push the n! brute force limit. More on this in the User Manual.
CXXFLAGS = -O3 -std=c++17 -Wall -Wextra -Isrc -Isrc/BruteForce -Isrc/GeneticAlgorithm -Isrc/TSPGraph

# Name of executable
TARGET = tsp_solver

# Source files based on your directory structure
SRCS = src/main.cpp \
       src/BruteForce/brute_force.cpp \
       src/GeneticAlgorithm/genetic_algorithm.cpp \
       src/TSPGraph/tsp_graph.cpp

# Map .cpp to .o for object files
OBJS = $(SRCS:.cpp=.o)

# Default target for build
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove build artifacts
clean:
	rm -f $(OBJS) $(TARGET)