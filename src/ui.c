#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ncursesw/ncurses.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include "api.h"
#include "main.h"
#include "ui.h"

int longestLabel = 0;
MenuItem *firstItem = NULL;

void dispose_menu(MenuItem *item) {
	if (item != NULL) {
		free((void *)item->label);
		if (item->nextItem != NULL) {
			dispose_menu(item->nextItem);
		}
		free(item);
	}
}

void ui_dispose() {
	//release all memory
	dispose_menu(firstItem);
	firstItem = NULL;
	longestLabel = 0;
}


void addMenuItem(const char *label) {
	int len = strlen(label);
	MenuItem *item = (MenuItem *) malloc(sizeof(MenuItem));

	if (label == NULL) {
		return;
	}

	item->label = (char *) malloc(sizeof(char) * (len + 1));

	if (item->label == NULL) {
		free(item);
		return;
	} else {
		strcpy((char *) item->label, label);
	}

	longestLabel = longestLabel < len ? len : longestLabel;
	if (firstItem == NULL) {
		//so this is first item of the menu
		firstItem = item;
		return;
	} else {
		//find latest menu item
		MenuItem *current = firstItem;
		while (current->nextItem != NULL) {
			current = current->nextItem;
		}

		current->nextItem = item;
	}
}

int countItems() {
	int count = 0;

	for (MenuItem *item = firstItem;item->nextItem != NULL; item = item->nextItem, count++){}

	return count;
}

/**
	show menu to the user lol
**/
void showMenu() {
	
	bkgd(ACS_BOARD | COLOR_PAIR(1));
	erase();
	bkgdset(' ');
	curs_set(0);


	MenuItem **items = (MenuItem **) malloc(sizeof(MenuItem) * countItems());
	MenuItem *item = firstItem;

	for (int index = 0; index < countItems(); index++) {
		items[index] = item;
		item = item->nextItem;
	}


	WINDOW *menu = newwin(countItems() + 2, longestLabel + 2, 2, 2);
	
	int key;
	int selectedItem = 0;
	do {
		switch (key) {
			case KEY_UP: {
				selectedItem--;
				break;
			}
			case KEY_DOWN: {
				selectedItem++;
				break;
			}
		}

		if (selectedItem < 0) {
			selectedItem += countItems();
		} else if (selectedItem >= countItems()) {
			selectedItem -= countItems();
		}

		wclear(menu);
		//werase(menu);
		box(menu, ACS_VLINE, ACS_HLINE);
		for (int index = 0; index < countItems(); index++) {
			if (selectedItem == index) {
				wattron(menu, A_REVERSE);
			}
			mvwaddstr(menu,index + 1, 1, items[index]->label);
			if (selectedItem == index) {
				wattroff(menu, A_REVERSE);
			}
		}
		refresh();
		wrefresh(menu);

	} while ((key = getch()) != KEY_F(10));

	delwin(menu);
	free(items);
}