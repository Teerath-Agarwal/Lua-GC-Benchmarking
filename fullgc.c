#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>

#define TEST_FILE "testbench.lua"

int main() {
    lua_State *L = luaL_newstate();
    if (L == NULL) {
        printf("%d: ERROR: Unabe to create Lua state.\n", __LINE__);
        return 1;
    }

    luaL_openlibs(L);

    printf("%d: INFO: Running with Full GC...\n", __LINE__);
    lua_gc(L, LUA_GCSTOP);
    printf("%d: INFO: Stopping the default GC\n", __LINE__);
    int mem = 0;
    mem = lua_gc(L, LUA_GCCOUNT);
    mem *= 1024;
    mem += lua_gc(L, LUA_GCCOUNTB);
    printf("%d: INFO: Memory usage before testbench execution - %d\n", __LINE__, mem);

    if (luaL_dofile(L, TEST_FILE)) {
        printf("%d: ERROR: %s\n", __LINE__, lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_getglobal(L, "test");
    if (!lua_isfunction(L, -1) || lua_pcall(L, 0, 0, 0) != LUA_OK)
        printf("%d: ERROR: Error calling 'test': %s\n", __LINE__, lua_tostring(L, -1));

    mem = lua_gc(L, LUA_GCCOUNT);
    mem *= 1024;
    mem += lua_gc(L, LUA_GCCOUNTB);
    printf("%d: INFO: Memory usage after testbench execution - %d\n", __LINE__, mem);
    printf("%d: INFO: Executing full GC...\n", __LINE__);
    lua_gc(L, LUA_GCCOLLECT);
    mem = lua_gc(L, LUA_GCCOUNT);
    mem *= 1024;
    mem += lua_gc(L, LUA_GCCOUNTB);
    printf("%d: INFO: Memory usage after garbage collection - %d\n", __LINE__, mem);

    lua_close(L);
    return 0;
}
