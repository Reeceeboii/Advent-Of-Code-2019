cmake_minimum_required(VERSION 3.14)
project(Advent_Of_Code_2019)

set(CMAKE_CXX_STANDARD 14)

add_executable(Advent_Of_Code_2019
        src/Day1/day1.cpp
        src/Day1/day1.h
        main.cpp src/Day2/day2.cpp src/Day2/day2.h src/Day3/day3.cpp src/Day3/day3.h)
