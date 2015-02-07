cmake_minimum_required (VERSION 2.8)

# platform pre setting
include(cmake/func.cmake)
if (APPLE)
	include(cmake/platform_mac.cmake)
endif()

######################################################################
project(mlua)

#liblua
add_subdirectory(src/lua-5.1.5 builds/project/lua-5.1.5)
