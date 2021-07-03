set(VX_X86_CXX_FLAGS_W "-Werror -Wall -Wextra")
set(VX_X86_CXX_FLAGS_O "-O2")
set(VX_X86_CXX_FLAGS_A "-march=native")
set(VX_X86_CXX_FLAGS_F "-finline-functions -fcompare-debug-second")

set(VX_X86_CXX_FLAGS
  "${VX_X86_CXX_FLAGS_W} ${VX_X86_CXX_FLAGS_O} ${VX_X86_CXX_FLAGS_A} ${VX_X86_CXX_FLAGS_F}"
)

#TODO if HOST_ARCH == X86
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${VX_X86_CXX_FLAGS}")


#set(VXHDRS
#  vx/vxtypes.hpp
#  vx/vxops.hpp
#  vx/vxadvops.hpp
#  vx/vxarray.hpp
#  vx/vxcomplex.hpp
#)

#add_custom_target(vxamalgam ALL
#  BYPRODUCTS vx.hpp
#  DEPENDS ${VXHDRS}
#  COMMAND cat ${VX_SOURCE_DIR}/vx/vxtypes.hpp > vx.hpp
#  COMMAND cat ${VX_SOURCE_DIR}/vx/vxops.hpp >> vx.hpp
#  COMMAND sed -i 's/^.*include \"vx.*//g' vx.hpp
#)

#install(FILES ${VXHDRS}
#  DESTINATION include/vx
#)

#install(FILES ${VX_BINARY_DIR}/vx.hpp
#  DESTINATION include/vx
#)