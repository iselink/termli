#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#ifndef H_API_INCLUDED
#define  H_API_INCLUDED

/**
	register all lua functions.
	lol.
**/
void registerLuaFunctions(lua_State *state);

int api_wait_key(lua_State *state);
int api_redraw_scr(lua_State *state);
int api_print(lua_State *state);
int api_draw_border(lua_State *state);

#endif // H_API_INCLUDED

