add_executable(test_x86_type_maker
  ${CMAKE_CURRENT_SOURCE_DIR}/test_type_maker.cpp
)
add_test(NAME x86-type-maker COMMAND test_x86_type_maker)

#add_executable (test_basic test/test_basic.cpp)
#add_executable (test_matrix test/test_matrix.cpp)


#add_test(NAME basic COMMAND test_basic)
#add_test(NAME matrix COMMAND test_matrix)