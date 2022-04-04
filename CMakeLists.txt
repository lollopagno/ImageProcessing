# CMake File
cmake_minimum_required(VERSION 3.6)

project(ImageProcessing VERSION 1.0.0 LANGUAGES CXX)

# Env variables
set(CMAKE_CURRENT_SOURCE_DIR src)
set(CMAKE_CURRENT_HEADERS_DIR src/include)
set(CMAKE_PROJECT ImageProcessing)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create directory
file(MAKE_DIRECTORY	${CMAKE_PROJECT}/bin)
file(MAKE_DIRECTORY	${CMAKE_PROJECT}/lib)

# Flag for bin and libs folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_PROJECT}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_PROJECT}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_PROJECT}/lib)

# Flag for QT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Find packages
find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

FILE(GLOB headers ${CMAKE_PROJECT}/${CMAKE_CURRENT_HEADERS_DIR}/*.h)
FILE(GLOB sources ${CMAKE_PROJECT}/${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
FILE(GLOB gui_sources ${CMAKE_PROJECT}/${CMAKE_CURRENT_SOURCE_DIR}/gui/*.cpp)
set(target_sources ${headers} ${sources} ${gui_sources})

add_executable(${PROJECT_NAME} ${target_sources})

# Set startup project
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${OpenCV_LIBS})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_NAME})



