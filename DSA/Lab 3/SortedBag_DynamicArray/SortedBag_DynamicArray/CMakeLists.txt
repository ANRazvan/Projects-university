cmake_minimum_required(VERSION 3.27)
project(SortedBag_DynamicArray)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SortedBag_DynamicArray
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedBag.cpp
        SortedBag.h
        SortedBagIterator.cpp
        SortedBagIterator.h)
