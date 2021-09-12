#ifndef H_UI_INCLUDED
#define  H_UI_INCLUDED

/**
 * Define menu item for main menu.
**/
typedef struct struct_MenuItem {
	const char *label;
	struct struct_MenuItem *nextItem;
} MenuItem;

void ui_dispose();

void addMenuItem(const char *);
void showMenu();

#endif