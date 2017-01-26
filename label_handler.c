/*
 * label_handler.c
 *
 *  Created on: Oct 18, 2016
 *      Author: Marvin
 */
#include "includes/label_handler.h"

typedef struct nodet_t {
	Label label;
	struct nodet_t *next;
} NODE;

static NODE *labels = NULL;

static NODE *head = NULL;

void addLabel(Label label) {

    if(head == NULL)
    {
        labels = malloc(sizeof(NODE));
        labels->label = label;
        labels->next = NULL;

        head = labels;
        return;
    }

	// don't allow duplicate labels!
	NODE *current = head;

	while(current != NULL) {
		if(0 == strcmp(current->label.name, label.name)) {
			printf("Label %s is already added, duplicates are not allowed.\n", label.name);
			return ;
		}
		current = current->next;
	}


	if(labels->label.offset <= 0 && labels->next == NULL) {
		labels->label = label;
	} else {
		NODE *temp = malloc(sizeof(NODE));
		temp->label = label;
		temp->next = NULL;

		labels->next = temp;
		labels = temp;
	}
}

uint32_t getLabelOffset(char *name) {

	NODE *current = NULL;
	current = head;
	while(current != NULL) {
		if(0 == strcmp(current->label.name, name)) {
			return current->label.offset;
		}
		current = current->next;
	}
	printf("Unable to find %s, returning 0.", name);
	return 0;
}

Label getLabelByName(char *name) {
		NODE *current = NULL;
		current = head;
		Label label;

		while(current != NULL) {
			if(0 == strcmp(current->label.name, name)) {
				label.offset = current->label.offset;
				strcpy(label.name, current->label.name);
				return label;
			}
			current = current->next;
		}
		printf("Unable to find label with name: %s", name);
		return label;
}

Label getLabelByOffset(uint32_t offset) {
		NODE *current = NULL;
		current = head;
		Label label;

		while(current != NULL) {
			if(offset == current->label.offset) {
				label.offset = current->label.offset;
				strcpy(label.name, current->label.name);
				return label;
			}
			current = current->next;
		}
		printf("Unable to find label for offset: %i. returned label is null\n", offset);
		return label;
}

/**
 * To be used at instruction compiling.
 * e.g.
 * 		If current line has <label>:
 * 		instruction parsing would skip this line.
 */
bool isLabelPresent(uint16_t offset) {
		NODE *current = NULL;
		current = head;

		while(current != NULL) {
			if(offset == current->label.offset) {
				return true;
			}
			current = current->next;
		}
		return false;
}

/**
 * parse the label in the current line. This basically removes the ':'
 * and saves the actual <label> to *label
 * e.g. *instr = "loop:"
 *
 * result
 * 		*label = "loop"
 *
 */
void parseLabel(char *instr, char *label) {
    printf("%lu finding label at line: %s", strlen(instr), instr);
    int i;
    bool isPresent = false;
    char locChar;
    for(i = 0; i < strlen(instr); i++) {
        locChar = instr[i];
        if(locChar == ':') {
            printf("label found!\n");
            isPresent = true;
            break;
        }
    }
    i = 0;
    if(isPresent) {
        for(i = 0; i < strlen(instr); i++) {
            locChar = instr[i];
            if(locChar == ':'){
                label[i] = '\0';
                return;
            }
            label[i]= locChar/*iterator*/;
        }
    }
    label[i]='\0';
}

void printLabels() {
	NODE *current = NULL;
	current = head;
	while (current != NULL) {
		printf("name: %s\t", current->label.name);
		printf("offset: %i\t\n", current->label.offset);
		current = current->next;
	}
}

void printLabel(char *name) {
	NODE *current = NULL;
		current = head;
		while (current != NULL) {
			if(0 == strcmp(name, current->label.name)) {
				printf("name: %s\t", current->label.name);
				printf("offset: %i\t", current->label.offset);
				return;
			}
			current = current->next;
		}
}
