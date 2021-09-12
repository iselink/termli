#include <string.h>
#include <signal.h>

#include <ncursesw/ncurses.h>

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include "api.h"
#include "main.h"
#include "ui.h"

/**
	wait for any key that is pressed.
**/
int api_wait_key(lua_State *state) {
	getch();
	return 0;
}

/**
	redraw entire screen
**/
int api_redraw_scr(lua_State *state) {
	refresh();
	return 0;
}

/**
	print some text into given part of the terminal.
**/
int api_print(lua_State *state) {
	int x = (int) lua_tonumber(state, -3);
	int y = (int) lua_tonumber(state, -2);
	const char *text = lua_tostring(state, -1);

	//mvaddwstr(y,x,text);
	//attron(A_REVERSE);
	mvaddstr(y, x, text);
	//attroff(A_REVERSE);
	//mvprintw(y,x, text);
	return 0;
}

int api_reverse(lua_State *state) {
	int enabled = lua_toboolean(state, -1);
	if (enabled) {
		attron(A_REVERSE);
	} else {
		attroff(A_REVERSE);
	}
	return 0;
}

int api_draw_border(lua_State *state) {
	bkgd(ACS_CKBOARD);
	erase();
	bkgdset(' ');
	box(stdscr, ACS_VLINE, ACS_HLINE);
	return 0;
}

int api_add_menu_item(lua_State *state) {
	const char *text = lua_tostring(state, -1);
	addMenuItem(text);
	return 0;
}


int api_show_menu(lua_State *state) {
	showMenu();
	return 0;
}


void registerLuaFunctions(lua_State *l) {
	lua_pushcfunction(l, api_wait_key);
	lua_setglobal(l, "wait_key");
	
	lua_pushcfunction(l, api_redraw_scr);
	lua_setglobal(l, "redraw");
	
	lua_pushcfunction(l, api_print);
	lua_setglobal(l, "mvprint");

	lua_pushcfunction(l, api_draw_border);
	lua_setglobal(l, "draw_border");

	
	lua_pushcfunction(l, api_reverse);
	lua_setglobal(l, "reverse");	

	lua_pushcfunction(l, api_add_menu_item);
	lua_setglobal(l, "add_menu_item");	

	lua_pushcfunction(l, api_show_menu);
	lua_setglobal(l, "show_menu");	


}