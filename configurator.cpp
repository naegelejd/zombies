#include "configurator.h"

namespace BAMF {

Configurator::Configurator()
{
    L = luaL_newstate();
    if (L == NULL) {
        fprintf(stderr, "Failed to create Lua state\n");
        // throw exception
    }

    luaL_openlibs(L);
}

Configurator::~Configurator()
{
    lua_close(L);
}

} // namespace BAMF
