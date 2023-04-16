cmake_minimum_required(VERSION 3.0)

project(SpacedTest)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Set the source files for the project
set(SOURCES
    src/GUI.cc
    src/Algorithm.cc
    src/Integration.cc
    src/main.cc
)

# Add the executable target for the project
add_executable(${PROJECT_NAME} ${SOURCES})

# Include the header files in the include path
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link the required libraries
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})

# Add the Integration library
add_library(Integration src/Integration.cc)

# Link the Integration library with the main target
target_link_libraries(${PROJECT_NAME} Integration)
