# Compiler and flags
CXX = g++
# Just like in project 3, -O3 is mandatory to push n! brute force limit for optimal solution
CXXFLAGS = -O3 -std=c++17 -Wall -Wextra

# Executable name
TARGET = bin_packer

# Source files based on CamelCase directory structure. I researched and found this is best practice for C++ projects.
SRCS = src/main.cpp \
       src/BinPacker/bin_packer.cpp \
       src/FileHandler/file_handler.cpp \
       src/PermutationGen/permutation_gen.cpp

# Object mapping: .cpp to .o files
OBJS = $(SRCS:.cpp=.o)

# Default target 
all: $(TARGET)

# Link executable: combines object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove build artifacts
clean:
	rm -f $(OBJS) $(TARGET)