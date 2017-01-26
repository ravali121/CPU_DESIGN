/*
 * util.c
 *
 *  Created on: Oct 25, 2016
 *      Author: 212554696
 */

#include "includes/util.h"

/**
 * @deprecated
 * Use removeInvalidChars() instead.
 */
char* removeWhiteSpace(char *source) {

	char *temp = malloc(sizeof(source));
	int token = 0;
	for(int i = 0; i < strlen(source); i++) {
		if(source[i] != ' ' && source[i] != '\0') {
			temp[token] = source[i];
			token++;
		} else if (source[i] == '\0') {
			temp[token] = source[i];
			break;
		}
	}
	return temp;
}

/**
 * @deprecated
 * Use removeInvalidChars() instead.
 *
 * This method only removes the '\n' at the end of the string (before '\0')
 */
char* removeEndLine(char *source) {
	char *temp = malloc(sizeof(source) - 1);
	for(int i = 0; i < strlen(source)-1; i++) {
		if(source[i] == '\n') {
			temp[i] = '\0';
			break;
		}
		temp[i] = source[i];
	}
	return temp;
}

/**
 * Removes: [ .,:\n\t\v\r\f]
 */
char* removeInvalidChars(char *source) {
	char *temp = malloc(sizeof(source));
	int token = 0;
	for(int i = 0; i < strlen(source); i++) {
		if(source[i] != ' ' && source[i] != '\0'
			&& source[i] != ',' && source[i] != ':'
			&& source[i] != '.' && source[i] != '\n'
			&& source[i] != '\t' && source[i] != '\v'
			&& source[i] != '\r' && source[i] != '\f') {

			temp[token] = source[i];
			token++;
		} else if (source[i] == '\0') {
			temp[token] = source[i];
			break;
		}
	}
	return temp;
}
