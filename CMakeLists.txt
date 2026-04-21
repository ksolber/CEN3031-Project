# 1. Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed. Please use: cmake -B build -S .")
endif()

# 2. Define the project name and the language used (C++)
project(GatorsKitchen LANGUAGES CXX)

# Set C++17 as the project-wide standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# 3. Export compile_commands.json for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Explicitly list source files
set(CORE_CXX_SOURCES
    src/Filter.cpp
    src/Pantry.cpp
    src/PantryLoader.cpp
)

set(ALL_CXX_SOURCE_FILES
    ${CORE_CXX_SOURCES}
    src/main.cpp
    src/Filter.h
    src/Pantry.h
    src/PantryLoader.h
    tests/test_pantry_status.cpp
    tests/test_filters.cpp
)

# 4. Linting and Formatting C++
add_custom_target(
    format
    COMMAND clang-format -i -style=file ${ALL_CXX_SOURCE_FILES}
    COMMAND ${CMAKE_COMMAND} -E echo "Successfully formatted C++ code."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Formatting C++ code..."
)

add_custom_target(
    lint
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} ${ALL_CXX_SOURCE_FILES}
    COMMAND ${CMAKE_COMMAND} -E echo "Successfully linted C++ code."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Linting C++ code..."
)

# 5. Build Targets

# Core library containing all business logic
add_library(gators_core STATIC ${CORE_CXX_SOURCES})
target_include_directories(gators_core PUBLIC src)

# Add compiler warning options (for GCC/Clang)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(gators_core PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

# Main executable
add_executable(GatorsKitchenApp src/main.cpp)
target_link_libraries(GatorsKitchenApp PRIVATE gators_core)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(GatorsKitchenApp PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

# Test executables
add_executable(GatorsKitchenTest tests/test_pantry_status.cpp)
target_link_libraries(GatorsKitchenTest PRIVATE gators_core)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(GatorsKitchenTest PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

add_executable(GatorsKitchenFilterTest tests/test_filters.cpp)
target_link_libraries(GatorsKitchenFilterTest PRIVATE gators_core)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(GatorsKitchenFilterTest PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

# Register the tests
add_test(NAME PantryStatusTest COMMAND GatorsKitchenTest)
add_test(NAME FilterTest COMMAND GatorsKitchenFilterTest)


# 6. Target to run the main application from the project root directory
add_custom_target(
    run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target GatorsKitchenApp
    COMMAND cmake -E chdir ${CMAKE_SOURCE_DIR} $<TARGET_FILE:GatorsKitchenApp>
    COMMENT "Running the application..."
    DEPENDS GatorsKitchenApp
)
