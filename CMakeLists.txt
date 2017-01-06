cmake_minimum_required(VERSION 3.6)
project(libevent_sample)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(libevent_sample ${SOURCE_FILES})

target_link_libraries(libevent_sample libevent.a libevent_pthreads.a pthread)