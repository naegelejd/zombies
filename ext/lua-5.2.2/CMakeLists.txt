set(LUA_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE PATH "Lua source directory")

set(LUA_CORE_SOURCES
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

set(LUA_LIB_SOURCES
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
