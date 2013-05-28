#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <map>
#include <iostream>

namespace BAMF {

class Configurator {
    public:
        Configurator();
        ~Configurator();

        void registerFunction(const std::string&, lua_CFunction);
        void readConfig(const std::string& path);

        void loadTable(const char *tbl);

        const std::string& getString(const std::string&);
        const std::map<std::string, std::string>& getTable(const std::string&);

    private:
        Configurator(const Configurator&);
        Configurator& operator=(const Configurator&);

        lua_State *L;

        std::map<std::string, std::string> strings;
        std::map<std::string, std::map<std::string, std::string> > tables;
};

} // namespace BAMF

#endif // CONFIGURATOR_H
