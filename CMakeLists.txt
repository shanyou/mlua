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

include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/src/lua-5.1.5/src)
add_subdirectory(src/libmlua builds/project/libmlua)


