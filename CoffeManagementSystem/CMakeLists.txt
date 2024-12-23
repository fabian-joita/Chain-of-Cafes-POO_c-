cmake_minimum_required(VERSION 3.10)

project(CoffeeManagementSystem CXX)

#setarea limbajului de compilare c++11
set(CMAKE_CXX_STANDARD 11)

#definirea directorului sursa relativ
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# gasirea toturor fisierelor sursa
file(GLOB SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/cafe_chain.cpp
    ${SRC_DIR}/Employee.cpp
    ${SRC_DIR}/CSVHandler.cpp
    ${SRC_DIR}/optiunea6.cpp
    ${SRC_DIR}/optiunea7.cpp
    ${SRC_DIR}/ingredient.cpp
)

#crearea executabilului
add_executable(main ${SOURCES})

#includerea directorului hederelor
target_include_directories(main PRIVATE ${SRC_DIR})
target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/include_headers)

