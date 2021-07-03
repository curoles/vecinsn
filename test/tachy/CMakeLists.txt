set(TC_BIN ${TACHY_TOOLCHAIN_HOME}/bin)
set(TCXX ${TC_BIN}/tachy-g++)

add_custom_target(test_tachy_type_maker ALL
  COMMAND ${TCXX} ${VX_TACHY_CXX_FLAGS} ${CMAKE_CURRENT_SOURCE_DIR}/../x86/test_type_maker.cpp -o test_tachy_type_maker.out
)