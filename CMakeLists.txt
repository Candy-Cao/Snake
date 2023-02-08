if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)
cmake_policy(SET CMP0048 NEW)

PROJECT(Snake VERSION 1.0)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
configure_file(SnakeConfig.h.in SnakeConfig.h)
file(GLOB_RECURSE SRC_LIST ./src/*.cpp)

MESSAGE(STATUS "This is BINARY dir" ${HELLO_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir" ${HELLO_SOURCE_DIR})

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_BINARY_DIR}
                           "./include/")
target_link_libraries(${PROJECT_NAME} PUBLIC
                      pthread
                      ncurses
                      event)

