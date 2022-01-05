## This is a CMake file, part of Unidata's netcdf-cxx package.
###
# Set up headers and sources
###

file(GLOB CXX_HEADERS *.h)
file(GLOB CXX_SOURCES nc*.cpp)


include_directories(netcdf-cxx4 SYSTEM PUBLIC 
    "${HDF5_INCLUDE_DIRS}"
    ${NETCDF_C_INCLUDE_DIR}
    "/usr/lib/x86_64-linux-gnu/openmpi/include"
    ${MPI_CXX_INCLUDE_DIRS}
)


link_directories(netcdf-cxx4
    ${HDF5_LINK_DIR}
)


###
# Set up tests.
###
IF(NCXX_ENABLE_TESTS)

  add_bin_test(cxx4 test_classic)
  add_bin_test(cxx4 test_group)
  add_bin_test(cxx4 test_dim)
  add_bin_test(cxx4 test_att)
  add_bin_test(cxx4 test_var)
  add_bin_test(cxx4 test_var2)
  add_bin_test(cxx4 test_type)
  add_bin_test(cxx4 test_open_close)
  add_bin_test(cxx4 test_ncFile_Flags)
  add_bin_test(cxx4 test_filter)

ENDIF()

MESSAGE(STATUS "HDF_C_LIBRARY_hdf5=${HDF5_C_LIBRARY_hdf5}")

SET(ALL_TLL_LIBS ${HDF5_C_LIBRARY_hdf5})
SET(ALL_TLL_LIBS ${ALL_TLL_LIBS} ${EXTRA_DEPS} PARENT_SCOPE)

ADD_LIBRARY(netcdf-cxx4 ${CXX_SOURCES})
add_library(netCDF::netcdf-cxx4 ALIAS netcdf-cxx4)

TARGET_INCLUDE_DIRECTORIES(netcdf-cxx4 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>

)

TARGET_LINK_LIBRARIES(netcdf-cxx4 PUBLIC 
    netcdf_mpi
)

TARGET_LINK_LIBRARIES(netcdf-cxx4 PUBLIC 
    ${ALL_TLL_LIBS}
    ${HDF5_C_LIBRARIES}
    ${MPI_CXX_LIBRARIES}
)


SET_TARGET_PROPERTIES(netcdf-cxx4 PROPERTIES
  VERSION ${NCXX_LIB_VERSION}
  SOVERSION ${NCXX_SO_VERSION}
  )

INSTALL(
  FILES ${CXX_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )
INSTALL(
  FILES netcdf
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )
INSTALL(
  TARGETS netcdf-cxx4
  EXPORT netcdf-cxx4Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
