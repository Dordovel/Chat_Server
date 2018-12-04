cmake_minimum_required(VERSION 3.12)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

IF(WIN32)

    link_libraries(ws2_32 wsock32)

ENDIF()

IF(UNIX)

    find_package(X11 REQUIRED)

    message(STATUS "X11_FOUND = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

    include_directories(${X11_INCLUDE_DIR})

    link_directories(${X11_LIBRARIES})

ENDIF()

add_executable(untitled1 main.cpp N/WinServer.cpp N/UnixServer.cpp N/Server.h Interface/IView.h Interface/IServer.h V/View.cpp V/View.h C/Controller.cpp C/Controller.h)

IF(UNIX)
    target_link_libraries(${CMAKE_PROJECT_NAME} ${X11_LIBRARIES})
ENDIF()