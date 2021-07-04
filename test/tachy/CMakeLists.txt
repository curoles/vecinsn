set(TC_BIN ${TACHY_TOOLCHAIN_HOME}/bin)
set(TCXX ${TC_BIN}/tachy-g++)
set(TSIM ${TC_BIN}/tachy-run)

add_custom_target(test_tachy_type_maker ALL
  COMMAND ${TCXX} ${VX_TACHY_CXX_FLAGS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../generic/test_type_maker.cpp
    -o test_tachy_type_maker.out
)
add_test(NAME tachy-type-maker
  COMMAND ${TSIM} test_tachy_type_maker.out
)

add_custom_target(test_tachy_nrelem ALL
  COMMAND ${TCXX} ${VX_TACHY_CXX_FLAGS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../generic/test_nrelem.cpp
    -o test_tachy_nrelem.out
)
add_test(NAME tachy-nrelem
  COMMAND ${TSIM} test_tachy_nrelem.out
)