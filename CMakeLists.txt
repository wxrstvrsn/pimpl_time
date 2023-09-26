cmake_minimum_required(VERSION 3.0)

project(pimpl_time)

add_library(TimeMeter STATIC)

add_executable(pimpl_time main.cpp)

if (WIN32)
    target_sources(TimeMeter PRIVATE TimeMeter_win.cpp)
elseif (UNIX)
    target_sources(TimeMeter PRIVATE TimeMeter_lin.cpp)
endif()

target_include_directories(TimeMeter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(pimpl_time PRIVATE TimeMeter)
