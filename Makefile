# Compiler
CXX = g++
# Compiler flags
# -Isrc adds the src directory to the include path
CXXFLAGS = -std=c++17 -Wall -Isrc

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Test source files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/test_%.o, $(TEST_SOURCES))

# Test executable
TEST_EXEC = $(BUILD_DIR)/run_tests

.PHONY: all test clean

all:
	@echo "Use 'make test' to build and run tests."

# Target to run tests
test: $(TEST_EXEC)
	@./$(TEST_EXEC)

# Target to build the test executable
$(TEST_EXEC): $(OBJECTS) $(TEST_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile test files into object files
$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	@echo "Cleaning up build files..."
	@rm -rf $(BUILD_DIR)
