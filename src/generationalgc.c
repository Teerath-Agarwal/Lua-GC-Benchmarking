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
    
    printf("%d: INFO: Running with Generational GC...\n", __LINE__);
    lua_gc(L, LUA_GCGEN, 0, 0);

    if (luaL_dofile(L, TEST_FILE)) {
        printf("%d: ERROR: %s\n", __LINE__, lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_getglobal(L, "test");
    if (!lua_isfunction(L, -1) || lua_pcall(L, 0, 0, 0) != LUA_OK)
        printf("%d: ERROR: Error calling 'test': %s\n", __LINE__, lua_tostring(L, -1));

    lua_gc(L, LUA_GCSTEP);
    lua_close(L);
    return 0;
}
