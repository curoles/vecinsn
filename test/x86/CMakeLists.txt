#message(STATUS "CMAKE_CXX_FLAGS:" ${CMAKE_CXX_FLAGS})

add_executable(test_x86_type_maker
  ${CMAKE_CURRENT_SOURCE_DIR}/../generic/test_type_maker.cpp
)
add_test(NAME x86-type-maker COMMAND test_x86_type_maker)

add_executable(test_x86_nrelem
  ${CMAKE_CURRENT_SOURCE_DIR}/../generic/test_nrelem.cpp
)
add_test(NAME x86-nrelem COMMAND test_x86_nrelem)

add_executable(test_x86_all_zero
  ${CMAKE_CURRENT_SOURCE_DIR}/../generic/test_all_zero.cpp
)
add_test(NAME x86-all-zero COMMAND test_x86_all_zero)

add_executable(test_x86_fill
  ${CMAKE_CURRENT_SOURCE_DIR}/../generic/test_fill.cpp
)
add_test(NAME x86-fill COMMAND test_x86_fill)

#add_executable (test_basic test/test_basic.cpp)
#add_executable (test_matrix test/test_matrix.cpp)


#add_test(NAME basic COMMAND test_basic)
#add_test(NAME matrix COMMAND test_matrix)