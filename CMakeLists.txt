cmake_minimum_required(VERSION 4.0)
project(laba_10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(laba_10
        src/main.cpp
        src/domain/Time.h
        src/domain/Time.cpp
        src/repository/ITimeRepo.h
        src/repository/InMemoryTimeRepo.h
        src/repository/InMemoryTimeRepo.cpp
        src/service/TimeService.h
        src/service/TimeService.cpp
        src/controller/TimeController.h
        src/controller/TimeController.cpp)
