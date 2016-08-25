set(SOURCE_FILES
    sam_file_header.cpp
    sam_text_header_codec.cpp
    sam_seqence_record.cpp
    sam_text_reader.cpp
    reader.cpp
)

add_library(easehtslib ${SOURCE_FILES})
target_link_libraries(easehtslib ${HTS_LIB}/libhts.a ${GLOG_ROOT}/lib/libglog.a)

add_executable(main main.cpp)
link_directories(${LIBRARY_OUTPUT_PATH})
target_link_libraries(main easehtslib)

if (test)
    link_libraries(gtest gtest_main)

    add_executable(main_unittest main_unittest.cpp)
    target_link_libraries(main_unittest ${HTS_LIB}/libhts.a)
    create_test(main_unittest)

    add_executable(reader_unittest reader_unittest.cpp)
    create_test(reader_unittest)
endif()
