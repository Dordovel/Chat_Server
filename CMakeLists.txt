cmake_minimum_required(VERSION 3.12)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

IF(WIN32)

    link_libraries(ws2_32 wsock32)

ENDIF()

add_executable(untitled1 main.cpp N/WinServer.cpp N/UnixServer.cpp N/Server.h Interface/IView.h Interface/IServer.h V/View.cpp V/View.h C/Controller.cpp C/Controller.h)