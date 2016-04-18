CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
PROJECT(dram_sal)

ENABLE_TESTING()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Og")

FILE(GLOB snippets RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

FOREACH(sp ${snippets})
    STRING(REGEX REPLACE ".cpp" "" sp "${sp}")
    MESSAGE(STATUS "Found ${sp}")
    ADD_EXECUTABLE(${sp} src/${sp}.cpp)

    FILE(GLOB tests "${CMAKE_CURRENT_SOURCE_DIR}/data/${sp}/*.in")
    FOREACH(inFile ${tests})
        STRING(REGEX REPLACE ".in" ".out" outFile "${inFile}")
        STRING(REGEX REPLACE ".*/" "" testId "${inFile}")
        STRING(REGEX REPLACE ".in" "" testId "${testId}")
        ADD_TEST("${sp}.${testId}" bash "${CMAKE_CURRENT_SOURCE_DIR}/judge.sh" "${sp}" "${inFile}" "${outFile}" "${CMAKE_CURRENT_SOURCE_DIR}/filter.py")
    ENDFOREACH()
ENDFOREACH()
