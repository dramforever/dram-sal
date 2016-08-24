CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)
PROJECT(dram_sal)

ENABLE_TESTING()

IF ("${OPTIMIZE}")
    SET (EXTRA_FLAGS "-O2")
    MESSAGE (STATUS "Compiling with optimizations")
ELSE ()
    SET (EXTRA_FLAGS "-g -fsanitize=address")
    MESSAGE (STATUS "Compiling with debugging info")
ENDIF ()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ${EXTRA_FLAGS} -DLOCAL")

FILE(GLOB snippets RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")


SET (count 0)
SET (count_test 0)
FOREACH (sp ${snippets})
    MATH (EXPR count "${count} + 1")
    STRING(REGEX REPLACE ".cpp" "" sp "${sp}")
    IF (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/data/${sp}/grader.cpp")
        ADD_EXECUTABLE(${sp} src/${sp}.cpp data/${sp}/grader.cpp)
        SET_SOURCE_FILES_PROPERTIES(src/${sp}.cpp PROPERTIES COMPILE_FLAGS -I${CMAKE_CURRENT_SOURCE_DIR}/data/${sp})
    ELSE ()
        ADD_EXECUTABLE(${sp} src/${sp}.cpp)
    ENDIF ()
    FILE(GLOB tests "${CMAKE_CURRENT_SOURCE_DIR}/data/${sp}/*.in")
    FOREACH (inFile ${tests})
        MATH (EXPR count_test "${count_test} + 1")
        STRING(REPLACE ".in" ".out" outFile "${inFile}")
        IF (EXISTS ${outFile})
        ELSE ()
            STRING(REPLACE ".out" ".ans" outFile "${outFile}")
        ENDIF ()
        STRING(REGEX REPLACE ".*/" "" testId "${inFile}")
        STRING(REPLACE ".in" "" testId "${testId}")
        ADD_TEST("${sp}.${testId}" bash "${CMAKE_CURRENT_SOURCE_DIR}/judge.sh" "${sp}" "${inFile}" "${outFile}" "${CMAKE_CURRENT_SOURCE_DIR}/filter_stream.py")
    ENDFOREACH ()
ENDFOREACH ()

MESSAGE (STATUS "Found ${count} programs")
MESSAGE (STATUS "Found ${count_test} tests")

