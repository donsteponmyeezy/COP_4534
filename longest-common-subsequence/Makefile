# Compiler and flags
CXX = g++
# Just like the bin packing project, -O3 keeps part 1 and the all-pairs part 2 work from running unnecessarily slow
CXXFLAGS = -O3 -std=c++17 -Wall -Wextra -I src

# Executable name (matches submission folder naming)
TARGET = hughesc

# Source files based on CamelCase directory structure. I researched and found this is best practice for C++ projects.
SRCS = src/main.cpp \
       src/FileHandler/file_handler.cpp \
       src/LCSEvaluator/lcs_evaluator.cpp

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

.PHONY: all clean run-part1 run-part2

run-part1: $(TARGET)
	./$(TARGET) part1 twoStrings.txt

run-part2: $(TARGET)
	./$(TARGET) part2 multiStrings.txt
