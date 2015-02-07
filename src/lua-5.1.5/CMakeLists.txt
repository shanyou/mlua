
set(projname lua51)

set(sources 
		src/lapi.c
		src/lapi.h
		src/lauxlib.c
		src/lauxlib.h
		src/lbaselib.c
		src/lcode.c
		src/lcode.h
		src/ldblib.c
		src/ldebug.c
		src/ldebug.h
		src/ldo.c
		src/ldo.h
		src/ldump.c
		src/lfunc.c
		src/lfunc.h
		src/lgc.c
		src/lgc.h
		src/linit.c
		src/liolib.c
		src/llex.c
		src/llex.h
		src/llimits.h
		src/lmathlib.c
		src/lmem.c
		src/lmem.h
		src/loadlib.c
		src/lobject.c
		src/lobject.h
		src/lopcodes.c
		src/lopcodes.h
		src/loslib.c
		src/lparser.c
		src/lparser.h
		src/lstate.c
		src/lstate.h
		src/lstring.c
		src/lstring.h
		src/lstrlib.c
		src/ltable.c
		src/ltable.h
		src/ltablib.c
		src/ltm.c
		src/ltm.h
		src/luaconf.h
		src/lua.h
		src/lualib.h
		src/lundump.c
		src/lundump.h
		src/lvm.c
		src/lvm.h
		src/lzio.c
		src/lzio.h
 )

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE -DLUA_BUILD_AS_DLL -D_LIB)
else()
    add_definitions(-DLUA_USE_LINUX)
endif()
    
add_library(${projname} STATIC ${sources})

if(WIN32)
	WIN32_Project_Config(${projname})
endif()


#lua interperator
set(projname lua)
add_executable(${projname} src/lua.c)
set(linklibs
	lua51
)

if(APPLE)
	set (linklibs readline ${linklibs})
endif()
target_link_libraries(${projname} ${linklibs})
