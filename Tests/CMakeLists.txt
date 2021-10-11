add_subdirectory(gtests)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(Tests LinkedListTest.cpp DynamicArrayTest.cpp ListSequenceTest.cpp ArraySequenceTest.cpp SetTests.cpp TreeTest.cpp)
target_link_libraries(Tests gtest gtest_main)