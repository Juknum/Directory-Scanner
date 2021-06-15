cmake_minimum_required(VERSION 3.0.0)
project(LP25_project VERSION 0.1.0)

include(CTest)
enable_testing()

set(EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})

file(

    GLOB_RECURSE
    source_files
    src/*
)

add_executable(LP25_project ${source_files})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION}) 
include(CPack) 
