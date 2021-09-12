#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <ncursesw/ncurses.h>
#include <error.h>

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include "main.h"
#include "errorman.h"
#include "api.h"
#include "ui.h"


//16M allocated for lua script must be suffecient
#define SCRIPT_MEM_SIZE 1024*1024*16

lua_State *lua_stat = NULL;
char *script_content = NULL;
long script_content_size = 0L;

WINDOW *termwin = NULL;

/**
 * release all resources that has been used by program.
 * maybe it could kill all threads as well...
 * doesn't exit.
**/
void dispose() {
	//deinitate ncurses
	if (termwin != NULL) {
		endwin();

	}
	
	if (lua_stat != NULL)  {
		lua_close(lua_stat);
		lua_stat = NULL;
	}

	if (script_content != NULL) {
		free(script_content);
		script_content = NULL;
	}

	ui_dispose();

	//dump all error messages and then release memory
	errorManagerDumpMessages(); 
	errorManagerDispose();
}

/**
 * handle termination of the program by reacting
 * on interrupt/terminate signal.
**/
void sig(int signal) {
	dispose();
	exit(0);
}


int main(int argc, char **argv) {
	signal(SIGINT, sig);
	signal(SIGTERM, sig);

	setlocale(LC_ALL, "");

	if (argc != 2) {
		help();
		return 1;
	}

	for (int index = 1; index < argc; index++) {
		if (strcmp("--help", argv[index]) == 0) {
			//just print help
			help();
			return 0;
		}
	}

	///////////////////
	if (errorManagerInitate()) {
		fprintf(stderr, "Unable to allocate memory for error messages.\n");
		fprintf(stderr, "I don't know on what device are you running this, but this program (probably) will not work.\n");
		return 1;
	}

	//load content of the script
	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		fprintf(stderr, "Unable to open file %s, program terminating itself...\n", argv[1]);
		return 1;
	}


	script_content = (char *) malloc(sizeof(char) * SCRIPT_MEM_SIZE);
	if (script_content == NULL) {
		//TODO: program didn't get memory = complaint about that too.
		fclose(file);
		return 3;
	} else {
		memset(script_content, 0, sizeof(char) * SCRIPT_MEM_SIZE);
	}

	for (int index = 0;; index++) {
		char c = fgetc(file);
		if (c == EOF) {
			script_content[index] = '\0';
			break;
		}
		script_content[index] = c;
		
	}

	fclose(file);

	//initiate ncurses
	termwin = initscr();
	//TODO: check if terminal has colors
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_CYAN);

	noecho();
	keypad(stdscr, TRUE);


	lua_stat = luaL_newstate();
	luaL_openlibs(lua_stat);

	//register all functions for everything
	registerLuaFunctions(lua_stat);

	if (luaL_loadstring(lua_stat, script_content) == LUA_OK) {
		if (lua_pcall(lua_stat, 0, 0, 0) == LUA_OK) {
			lua_pop(lua_stat, lua_gettop(lua_stat));
		} else {
			//print error
			//TODO: (a little) better error handling?
			addErrorMessage(lua_tostring(lua_stat, -1));
		}
	}

	dispose();
	return 0;
}

/**
 * print help message to the standart output.
**/
void help() {
	printf("Termli %s\n\n", VERSION_STRING);
	printf("Usage: termli <script>\n\n");
	printf("Available flags:\n--help - print this help (with version).\n");
	printf("\nIf necesary, program's repo is here: github.com/iselink/termli\n");
}