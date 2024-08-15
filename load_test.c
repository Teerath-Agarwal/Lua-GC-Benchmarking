#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <script.lua>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Create a new Lua state
    lua_State *L = luaL_newstate();

    // Load standard libraries into the Lua state
    luaL_openlibs(L);

    luaL_loadfile(L, argv[1]);
    // Load and execute the Lua script
    //if (luaL_loadfile(L, argv[1]) || lua_pcall(L, 0, 0, 0)) {
      //  fprintf(stderr, "Error: %s\n", lua_tostring(L, -1));
        //lua_close(L);
        //return EXIT_FAILURE;
    //}

    // Close the Lua state
    lua_close(L);

    return EXIT_SUCCESS;
}

