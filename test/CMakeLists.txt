add_subdirectory(x86)

if(TACHY_TOOLCHAIN_HOME)
  add_subdirectory(tachy)
else()
  #message(WARNING "TACHY_TOOLCHAIN_HOME not defined, do 'cmake -DTACHY_TOOLCHAIN_HOME=your_toolchain/install/set0 ../vecinsn'")
endif()