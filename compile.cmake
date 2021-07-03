set(VX_X86_CXX_FLAGS_W "-Werror -Wall -Wextra")
set(VX_X86_CXX_FLAGS_O "-O2")
set(VX_X86_CXX_FLAGS_A "-march=native")
set(VX_X86_CXX_FLAGS_F "-finline-functions -fcompare-debug-second")

set(VX_X86_CXX_FLAGS
  "${VX_X86_CXX_FLAGS_W} ${VX_X86_CXX_FLAGS_O} ${VX_X86_CXX_FLAGS_A} ${VX_X86_CXX_FLAGS_F}"
)

set(VX_TACHY_CXX_FLAGS_W -Werror -Wall -Wextra)
set(VX_TACHY_CXX_FLAGS_O -O2)
set(VX_TACHY_CXX_FLAGS_A -I${CMAKE_SOURCE_DIR})
set(VX_TACHY_CXX_FLAGS_F -finline-functions -fcompare-debug-second)

set(VX_TACHY_CXX_FLAGS
  ${VX_TACHY_CXX_FLAGS_W} ${VX_TACHY_CXX_FLAGS_O} ${VX_TACHY_CXX_FLAGS_A} ${VX_TACHY_CXX_FLAGS_F}
)

#TODO if HOST_ARCH == X86
set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} ${VX_X86_CXX_FLAGS}"
)

#message(STATUS "CMAKE_CXX_FLAGS:" ${CMAKE_CXX_FLAGS})