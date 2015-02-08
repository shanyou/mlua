set(projname libmlua)

file(GLOB lua_script "libs/*.lua")

foreach(script ${lua_script})
	message("begin compile ${script}")
	TEXTFILE2HEX(${script})
endforeach(script)

set(sources
	${lua_script}
	MLuaRefCount.cpp
    MLuaEngine.cpp
)

add_library(${projname} STATIC ${sources})
