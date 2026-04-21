BUILD_DIR := build

.PHONY: configure build test run format lint clean

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

build: configure
	cmake --build $(BUILD_DIR)

test: build
	cd $(BUILD_DIR) && ctest --output-on-failure

run: configure
	cmake --build $(BUILD_DIR) --target run

format: configure
	cmake --build $(BUILD_DIR) --target format
	uv run task format
	@echo "Successfully formatted Python code."

lint: configure
	cmake --build $(BUILD_DIR) --target lint
	uv run task lint
	@echo "Successfully linted Python code."

clean:
	rm -rf $(BUILD_DIR)
