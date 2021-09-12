/**
 * error state manager.
 * So program can complaint about anything that is wrong.
 * 
 * This is exist due to ncurses being used and sometimes is not good to use ncurses as frontend.
**/
#include "errorman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** char pointer to pointers of error messages. **/
char **errors = NULL;

/**
 * Add a new error message to the stack.
**/
void addErrorMessage(const char *text) {
	if (errors == NULL) {
		//don't try add items if memory isn't allocated (yet)
		return;
	}

	for (int index = 0; index < ERROR_MANAGER_MAX_MESSAGES; index++) {
		if (errors[index] == NULL) {
			//free place to put message yay
			//copy only ERROR_MANAGER_MAX_MESSAGE_LENGTH (so far 256) without one character
			//that one char is a null char (so we are in array boundary)
			strncpy(errors[index], text, ERROR_MANAGER_MAX_MESSAGE_LENGTH - 1);
			return;
		}
	}

	//no place F
	//TODO: no more memory for error message should be somehow handled
	return;
}

/**
 * Initiate error manager.
 * That mean allocating memory.
**/
int errorManagerInitate() {
	errors = (char **)malloc(sizeof(char *) * ERROR_MANAGER_MAX_MESSAGES);
	if (errors == NULL) {
		return 1;
	}
	for (int index = 0; index < ERROR_MANAGER_MAX_MESSAGES; index++) {
		errors[index] = (char *)malloc(sizeof(char) * ERROR_MANAGER_MAX_MESSAGE_LENGTH);
		if (errors[index] == NULL) {
			//we ran out of memory
			//idk on what device this shit is running, but this program probably can't work fine even by itself.
			do {
				//dealocate already taken memory.
				free(errors[--index]);
			} while (index >= 0);
			free(errors);
			errors = NULL;	//just to be safe
			return 2;
		}
	}
	return 0;
}

/**
 * release all resources used by error manager.
**/
void errorManagerDispose() {
	if (errors == NULL) {
		return;
	}

	for (int index = 0; index < ERROR_MANAGER_MAX_MESSAGES; index++) {
		free(errors[index]);
	}

	free(errors);
	errors = NULL;
}

/**
 * Print all error messages into standart error stream.
 * Should be called when ncurses is not in use, otherwise it will do shit (or idk).
 * Messages should be in chronological order (as they added).
**/
void errorManagerDumpMessages() {
	if (errors == NULL) {
		return;
	}

	for (int index = 0; index < ERROR_MANAGER_MAX_MESSAGES; index++) {
		if (errors[index][0] != '\0') {
			fprintf(stderr, "%i\t%s\n", index, errors[index]);
		}
	}
}
