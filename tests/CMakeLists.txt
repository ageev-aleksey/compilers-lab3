
file(GLOB SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_executable(TestsLexer ${SRC_FILES})
target_include_directories(TestsLexer PUBLIC ${INCLUDE_DIR})
target_link_libraries(TestsLexer GL::AST gtest gtest_main)