#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace BAMF {

class Configurator {
    public:
        Configurator();
        ~Configurator();

    //private:
        lua_State *L;
};

} // namespace BAMF

#endif // CONFIGURATOR_H
