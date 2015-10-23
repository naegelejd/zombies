set(LUA_VERSION 5.3.1)
set(LUA_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lua-${LUA_VERSION}/src")
set(LUA_INCLUDE_DIR ${LUA_SOURCE_DIR} CACHE PATH "Lua source directory")

function(PREPEND var prefix)
    set(listVar "")
    foreach(f ${ARGN})
        list(APPEND listVar "${prefix}/${f}")
    endforeach(f)
    set(${var} "${listVar}" PARENT_SCOPE)
endfunction(PREPEND)

PREPEND(LUA_CORE_SOURCES ${LUA_SOURCE_DIR}
    lapi.c
    lcode.c
    lctype.c
    ldebug.c
    ldo.c
    ldump.c
    lfunc.c
    lgc.c
    llex.c
    lmem.c
    lobject.c
    lopcodes.c
    lparser.c
    lstate.c
    lstring.c
    ltable.c
    ltm.c
    lundump.c
    lvm.c
    lzio.c)

PREPEND(LUA_LIB_SOURCES ${LUA_SOURCE_DIR}
    lauxlib.c
    lbaselib.c
    lbitlib.c
    lcorolib.c
    ldblib.c
    liolib.c
    lmathlib.c
    loslib.c
    lstrlib.c
    ltablib.c
    lutf8lib.c
    loadlib.c
    linit.c)

if(WIN32)
    add_definitions(-DLUA_BUILD_AS_DLL)
elseif(APPLE)
    add_definitions(-DLUA_USE_MACOSX)
else()
    add_definitions(-DLUA_USE_LINUX)
endif()

add_library(lua ${LUA_CORE_SOURCES} ${LUA_LIB_SOURCES})
