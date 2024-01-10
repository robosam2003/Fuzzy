cmake_minimum_required(VERSION 3.26)
project(Fuzzy)

set(CMAKE_CXX_STANDARD 17)

add_executable(Fuzzy src/main.cpp
        src/MembershipFunction.cpp
        src/MembershipFunction.h
        src/Rule.cpp
        src/Rule.h
        src/InferenceMechanism.cpp
        src/InferenceMechanism.h

)