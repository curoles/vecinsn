cmake_minimum_required(VERSION 3.10)

project(VX)

set(VXHDRS
  vx/vxtypes.hpp vx/vxops.hpp vx/vxadvops.hpp
  vx/vxarray.hpp
  vx/vxcomplex.hpp
)

# Install inside the build directory.
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

install(FILES ${VXHDRS}
  DESTINATION include/vx
)
