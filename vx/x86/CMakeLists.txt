
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