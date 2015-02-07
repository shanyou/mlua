
####################################################################################
# function definition
####################################################################################
function(WIN32_SOURCE_CONTROL prjname)
#	SET_PROPERTY (TARGET ${prjname} PROPERTY VS_SCC_LOCALPATH "${PROJECT_SOURCE_DIR}")	
#	SET_PROPERTY (TARGET ${prjname} PROPERTY VS_SCC_PROJECTNAME "//depot/main/anchor3")	
#	SET_PROPERTY (TARGET ${prjname} PROPERTY VS_SCC_PROVIDER "MSSCCI:Source Depot")	
endfunction(WIN32_SOURCE_CONTROL)

function(WIN32_Project_Config prjname)
if(WIN32)
	SET_PROPERTY (TARGET ${prjname} PROPERTY STATIC_LIBRARY_FLAGS /NODEFAULTLIB)
	WIN32_SOURCE_CONTROL(${prjname})
endif()
endfunction(WIN32_Project_Config)

function(SET_PROJECT_FOLDER prjname foldername)
	SET_PROPERTY (TARGET ${prjname} PROPERTY FOLDER ${foldername})	
endfunction(SET_PROJECT_FOLDER)

function(WIN32_STANDARD_LIBS prjname)
	SET_PROPERTY (TARGET ${projname} PROPERTY LINK_FLAGS_DEBUG ${WIN32_STANDARD_LIBRARIES_DEBUG})
	SET_PROPERTY (TARGET ${projname} PROPERTY LINK_FLAGS_MINSIZEREL ${WIN32_STANDARD_LIBRARIES_RELEASE})
	SET_PROPERTY (TARGET ${projname} PROPERTY LINK_FLAGS_RELEASE ${WIN32_STANDARD_LIBRARIES_RELEASE})
	SET_PROPERTY (TARGET ${projname} PROPERTY LINK_FLAGS_RELWITHDEBINFO ${WIN32_STANDARD_LIBRARIES_RELEASE})
endfunction(WIN32_STANDARD_LIBS)

function(ADD_FRAMEWORK fwname) 
    find_library(FRAMEWORK_${fwname} 
        NAMES ${fwname} 
        PATHS ${CMAKE_OSX_SYSROOT}/System/Library 
        PATH_SUFFIXES Frameworks 
        NO_DEFAULT_PATH) 
    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND) 
        MESSAGE(ERROR ": Framework ${fwname} not found") 
    else() 
        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}") 
        include_directories("${FRAMEWORK_${fwname}}")
    endif() 
endfunction(ADD_FRAMEWORK) 

function(TEXTFILE2HEX basefile)
    get_filename_component(filename ${basefile} NAME)
    if(${CMAKE_CURRENT_SOURCE_DIR}/${basefile} IS_NEWER_THAN ${CMAKE_CURRENT_SOURCE_DIR}/${basefile})
        message(STATUS "generating ${filename}.i ...")
        unset(luatext)
        unset(spliteluatext)
        
        file(READ ${basefile} luatext HEX)
        STRING(REGEX REPLACE "(..)"  "0x\\1," spliteluatext "${luatext}")
        file(WRITE ${filename}.i "${spliteluatext}" )
    endif()
endfunction(TEXTFILE2HEX)