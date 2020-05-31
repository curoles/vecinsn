cmake_minimum_required(VERSION 3.10)

project(VX)

set(VXHDRS
  vx/vxtypes.hpp vx/vxops.hpp vx/vxadvops.hpp
  vx/vxarray.hpp
  vx/vxcomplex.hpp
)

add_custom_target(vxamalgam ALL
  BYPRODUCTS vx.hpp
  DEPENDS ${VXHDRS}
  COMMAND cat ${VX_SOURCE_DIR}/vx/vxtypes.hpp > vx.hpp
  COMMAND cat ${VX_SOURCE_DIR}/vx/vxops.hpp >> vx.hpp
  COMMAND sed -i 's/^.*include \"vx.*//g' vx.hpp
)

# Install inside the build directory.
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

install(FILES ${VXHDRS}
  DESTINATION include/vx
)

install(FILES ${VX_BINARY_DIR}/vx.hpp
  DESTINATION include/vx
)

# Requires C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler options.
set(VX_CXX_FLAGS "-finline-functions -fcompare-debug-second -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 ${VX_CXX_FLAGS} -Werror -Wall -Wextra -I${VX_SOURCE_DIR}")

add_executable (test_basic test/test_basic.cpp)

# After enablig testing we can do `make test`
enable_testing()

add_test(NAME basic
    COMMAND test_basic
)

