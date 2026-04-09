# 1. Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.15)


# 2. Define the project name and the language used (C++)
project(GatorsKitchen LANGUAGES CXX)

# Use C++17 standard for the application target
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()


# 3. Integrate clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find all C++ source and header files for formatting/linting
file(GLOB_RECURSE ALL_CXX_SOURCE_FILES CONFIGURE_DEPENDS "src/*.[ch]pp" "src/*.[ch]" "tests/*.[ch]pp" "tests/*.[ch]")

# Find core library files
file(GLOB_RECURSE CORE_CXX_SOURCES CONFIGURE_DEPENDS "src/*.[ch]pp" "src/*.[ch]")
list(FILTER CORE_CXX_SOURCES EXCLUDE REGEX "main\\.cpp$")


# 4. Formatting and Linting C++ and Python
# Target for formatting C++ and Python at the same time
add_custom_target(
    format

    # C++ formatting
    COMMAND clang-format -i -style=file ${ALL_CXX_SOURCE_FILES}

    # Python formatting
    COMMAND cmake -E chdir ${CMAKE_SOURCE_DIR} uv run task format

    # Success message
    COMMAND cmake -E echo "Successfully formatted C++ and Python code!"

    COMMENT "Formatting C++ and Python code..."
)

# Target for linting Python
add_custom_target(
    lint

    # Python linting
    COMMAND cmake -E chdir ${CMAKE_SOURCE_DIR} uv run task lint

    # C++ linting
    COMMAND clang-tidy --quiet -p ${CMAKE_BINARY_DIR} ${ALL_CXX_SOURCE_FILES} -checks='bugprone-*,performance-*,-bugprone-easily-swappable-parameters,-performance-avoid-endl'

    # Success message
    COMMAND cmake -E echo "Successfully linted C++ and Python code!"
    
    COMMENT "Linting C++ and Python code..."
)


# 5. Build Targets

# Core library containing all business logic
add_library(gators_core STATIC ${CORE_CXX_SOURCES})
target_include_directories(gators_core PUBLIC src)
target_compile_features(gators_core PUBLIC cxx_std_17)

# Main executable
add_executable(MyProject src/main.cpp)
target_link_libraries(MyProject PRIVATE gators_core)

# Test executable
add_executable(MyTest tests/test_pantry_status.cpp)
target_link_libraries(MyTest PRIVATE gators_core)

# Register the test
add_test(NAME PantryStatusTest COMMAND MyTest)


# 6. Sync Python dependencies with uv after the C++ build finishes
add_custom_command(
    TARGET MyProject POST_BUILD
    COMMAND cmake -E chdir ${CMAKE_SOURCE_DIR} uv sync
    COMMENT "Syncing Python dependencies with uv..."
)

# 7. Target to run the main application from the project root directory
add_custom_target(
    run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target MyProject
    COMMAND cmake -E chdir ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}/MyProject
    COMMENT "Running the MyProject application..."
    DEPENDS MyProject
)
