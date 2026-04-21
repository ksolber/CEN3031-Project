# Compiler
CXX = g++
# Compiler flags
# -Isrc adds the src directory to the include path
CXXFLAGS = -std=c++17 -Wall -Isrc

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Exclude main.cpp from shared objects used by tests
SOURCES = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Optional app target
APP_SOURCE = $(SRC_DIR)/main.cpp
APP_OBJECT = $(BUILD_DIR)/main.o
APP_EXEC = $(BUILD_DIR)/GatorsKitchenApp

# Find all source files in the src directory
# SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Create a list of object files for the sources, to be placed in the build directory
# OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Find all test source files in the tests directory
TEST_SOURCES = $(wildcard $(TEST_DIR)/test_*.cpp)
# Create a list of executable file names from the test source files
TEST_EXECS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%, $(TEST_SOURCES))

# Files for formatting and linting
FORMAT_FILES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h $(TEST_DIR)/*.cpp)
LINT_FILES = $(wildcard $(SRC_DIR)/*.cpp $(TEST_DIR)/*.cpp)
PYTHON_FILES = $(wildcard $(SRC_DIR)/*.py $(TEST_DIR)/*.py *.py)

.PHONY: all test clean format lint

all:
	@echo "Use 'make test' to build and run all tests."
	@echo "Use 'make clean' to remove build artifacts."
	@echo "Use 'make format' to format code with clang-format."
	@echo "Use 'make lint' to check code with clang-tidy."

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

# Format all C++ and Python files
format:
	@echo "Formatting C++ source files..."
	clang-format -i $(FORMAT_FILES)
	@if [ -n "$(PYTHON_FILES)" ]; then \
		echo "Formatting Python files..."; \
		uv run task format; \
	else \
		echo "Skipping Python formatting (no Python files found)."; \
	fi
	@echo "Successfully formatted all files."

# Run linting on all C++ and Python files
lint:
	@echo "Linting C++ source files..."
	clang-tidy $(LINT_FILES) -- -I$(SRC_DIR)
	@if [ -n "$(PYTHON_FILES)" ]; then \
		echo "Linting Python files..."; \
		uv run task lint; \
	else \
		echo "Skipping Python linting (no Python files found)."; \
	fi
	@echo "Successfully linted all files."
