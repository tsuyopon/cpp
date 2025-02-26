// luaのHelloWorld的なプログラム
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>

int greet(lua_State *);
int add(lua_State *);

int main() {
    int status, result;
    lua_State *L;

    L = luaL_newstate();
    luaL_openlibs(L);         //Lua標準ライブラリの導入（インポート）

    // greetやaddはluaスクリプトからc_greet, c_addとして呼び出せます。
    lua_register(L, "c_greet", greet);
    lua_register(L, "c_add", add);

    // 下記でtest.luaスクリプトをロードします
    status = luaL_dofile(L, "test.lua");
    if(status) {
        fprintf(stderr, "Couldn't load file: %s", lua_tostring(L, -1));
        return 1;
    }

    lua_close(L);

    return 0;
}

int greet(lua_State *L) {
    const char *str = lua_tostring(L, 1);
    printf("Hello!! %s!\n", str);
    return 0;
}

int add(lua_State *L) {
    int x = lua_tointeger(L, 1);
    int y = lua_tointeger(L, 2);
    lua_pushinteger(L, x + y);
    return 1; // returnの値で戻り値が1つ存在することを認識
}
