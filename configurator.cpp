#include <stdexcept>

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

void Configurator::registerFunction(const std::string& name, lua_CFunction fn)
{
    lua_register(L, name.c_str(), fn);
}

void Configurator::readConfig(const std::string& path)
{
    const char* p = path.c_str();

    if (luaL_dofile(L, p) != 0) {
        std::cerr << "Failed to load/run file " << path << std::endl;
    }

    lua_getglobal(L, "resources");
    const char *resources = lua_tostring(L, -1);
    if (!resources) {
        std::cerr << "Failed to read var resources" << std::endl;
    }
    strings["resources"] = std::string(resources);

    lua_getglobal(L, "title");
    const char *title = lua_tostring(L, -1);
    if (!title) {
        std::cerr << "Failed to read var title" << std::endl;
    }
    strings["title"] = std::string(title);
    lua_pop(L, 1);

    loadTable("fonts");
    loadTable("textures");
    loadTable("sounds");
}

void Configurator::loadTable(const char *tbl)
{
    lua_getglobal(L, tbl);
    if (lua_isnil(L, -1)) {
        std::cerr << "Invalid table name: " << tbl << std::endl;
        return;
    }

    lua_pushnil(L);

    //std::cout << lua_typename(L, lua_type(L, -1)) << std::endl;
    //std::cout << lua_typename(L, lua_type(L, -2)) << std::endl;

    while (lua_next(L, -2)) {
        //printf("%s - %s\n", lua_typename(L, lua_type(L, -2)), lua_typename(L, lua_type(L, -1)));

        if (lua_type(L, -1) != LUA_TSTRING) {
            lua_pop(L, 1);
            continue;
        } else if (lua_type(L, -2) != LUA_TSTRING) {
            lua_pop(L, 1);
            continue;
        }

        lua_pushvalue(L, -2);   // copy key so it doesn't get mangled
        std::string key(lua_tostring(L, -1));
        std::string val(lua_tostring(L, -2));
        lua_pop(L, 2);  // pop copied key and val

        //std::cout << "key: " << key << " val: " << val << std::endl;
        tables[tbl][key] = val;
    }
    lua_pop(L, 1);
}

// throws std::out_of_range
const std::map<std::string, std::string>& Configurator::getTable(const std::string& name)
{
    return tables.at(name);
}

// throws std::out_of_range
const std::string& Configurator::getString(const std::string& key)
{
    return strings.at(key);
}

Configurator::~Configurator()
{
    if (L) {
        lua_close(L);
        L = NULL;
    }
}

} // namespace BAMF
