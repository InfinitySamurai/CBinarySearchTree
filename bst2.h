#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFIELDLEN  81
#define PHONELEN 8
#define DEBUG 0

//Required for reference in both dict1.c and bst1.c
typedef struct book_node{
	char key[MAXFIELDLEN+1];
	char surname[MAXFIELDLEN];
	char initial;
	char number[PHONELEN];
	struct book_node *left;
	struct book_node *mid;
	struct book_node *right;
}book_node;

char key[MAXFIELDLEN+1];

book_node *bstAddData(char *surname, char initial, char *number, book_node *rootptr);
void bstCreateKey(char *surname, char initial);
book_node *bstCreateNode(char *surname, char initial, char *number, char *key);
void bstInsertNode(char *surname, char initial, char *number, char *key, book_node *rootptr);
void traverse(book_node *rootptr);
int bstSearch(char *surname, char initial, book_node *rootptr, FILE *fp);
