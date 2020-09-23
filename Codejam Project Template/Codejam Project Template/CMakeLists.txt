cmake_minimum_required(VERSION 3.15.5)

project(CodejamProject)

if(WIN32)
  add_definitions(-g)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-Wall)
#  target_link_libraries(main.exe kernel32 user32 advapi32)
endif(WIN32)

add_executable(main main.cpp)
