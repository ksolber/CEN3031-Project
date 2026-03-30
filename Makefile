# Compiler
CXX = g++
# Compiler flags
# -Isrc adds the src directory to the include path
CXXFLAGS = -std=c++17 -Wall -Isrc

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Find all source files in the src directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Create a list of object files for the sources, to be placed in the build directory
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Find all test source files in the tests directory
TEST_SOURCES = $(wildcard $(TEST_DIR)/test_*.cpp)
# Create a list of executable file names from the test source files
TEST_EXECS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%, $(TEST_SOURCES))

.PHONY: all test clean

all:
	@echo "Use 'make test' to build and run all tests."
	@echo "Use 'make clean' to remove build artifacts."

# Target to run all tests
# First, it builds all test executables, then it runs them one by one.
test: $(TEST_EXECS)
	@echo "Running tests..."
	@for test_exec in $(TEST_EXECS); do \
		echo "--- Running $$test_exec ---"; \
		./$$test_exec; \
	done
	@echo "All tests finished."

# Generic rule to build a test executable from its source file
# Example: builds 'build/test_pantry_status' from 'tests/test_pantry_status.cpp' and the object files from src
$(BUILD_DIR)/test_%: $(TEST_DIR)/test_%.cpp $(OBJECTS)
	@echo "Building test executable: $@"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile main source files into object files
# This runs only when a source file has changed
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling: $<"
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	@echo "Cleaning up build files..."
	@rm -rf $(BUILD_DIR)
