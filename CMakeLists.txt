cmake_minimum_required(VERSION 2.6)
project(easehtslib)

#set(CMAKE_CXX_COMPILER g++)

set(CXX_FLAGS
        -g
        # -DVALGRIND
        # -DMUDUO_STD_STRING
        -DCHECK_PTHREAD_RETURN_VALUE
        -D_FILE_OFFSET_BITS=64
        -Wall
        -Wextra
        -Werror
        -Wno-unused-parameter
        -Woverloaded-virtual
        -Wpointer-arith
        -Wwrite-strings
        -march=native
        # -MMD
        -std=c++0x
        #-std=c++11
        -rdynamic
        )
# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#set(BOOST_ROOT "/home/zp/tools/boost/")
#find_package(Boost REQUIRED)
find_package(ZLIB)

set(HTS_LIB "/home/zp/work/rnaSeq/htslib/")
set(GLOG_ROOT "/home/zp/tools/glog/install/")
set(GFLAGS_ROOT "/home/zp/tools/gflags/install/")

#include_directories(${Boost_INCLUDE_DIRS})
include_directories(${HTS_LIB})
include_directories(${GLOG_ROOT}/include/)
include_directories(${GFLAGS_ROOT}/include/)

link_directories(
        ${GLOG_ROOT}/lib/
        ${GFLAGS_ROOT}/lib/
)

link_libraries(
        #${Boost_LIBRARIES}
        pthread
        z
        unwind
)

if (test)
    macro (create_test target)
        add_test (NAME ${target} COMMAND $<TARGET_FILE:${target}>)
    endmacro (create_test)

    enable_testing()

    set(GTEST_ROOT "/home/zp/tools/googletest/install/")
    #find_package(GTest REQUIRED)

    include_directories(${Gtest_INCLUDE_DIRS})

    link_libraries(
            ${Gtest_LIBRARIES}
    )
endif()

add_subdirectory(src)
