file(GLOB SRC_FILES "./ast/*.cpp")
add_library(ast ${SRC_FILES})
target_include_directories(ast PUBLIC ${INCLUDE_DIR})
target_link_libraries(ast GL::Grammar)

add_executable(MAIN main.cpp)
target_link_libraries(MAIN ast)