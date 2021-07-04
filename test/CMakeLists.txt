add_subdirectory(x86)

# cmake -DTACHY_TOOLCHAIN_HOME=your_toolchain/install/set0 ../vecinsn'
if(TACHY_TOOLCHAIN_HOME)
  add_subdirectory(tachy)
endif()