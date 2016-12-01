#include "bst2.h"

/*
	Binary Search Tree program for assignment 1 of COMP20003
	By Russell Long commenced 19/8/2014

	This is the basis of the projects data structure for the storage
	of surnames, initials and phone numbers for a "phonebook"

	This second version adds a 3rd pointer to the nodes for keys that are the same.
	This allows no more key comparisons when finding nodes with the same Surname and initial.

*/


book_node*
bstAddData(char *surname, char initial, char *number, book_node *rootptr){

	bstCreateKey(surname, initial);

	if(rootptr == NULL){

		rootptr = bstCreateNode(surname, initial, number, key);
		return rootptr;


	}
	else{

		bstInsertNode(surname, initial, number, key, rootptr);

	}

	return rootptr;



}
//created the key based on surname and initial given for the nodes
void
bstCreateKey(char *surname, char initial){

	int keypos = 0;

	while(surname[keypos] != '\0'){
		key[keypos] = surname[keypos];
		keypos += 1;
	}
	key[keypos] = initial;
	key[keypos+1] = '\0';

}

//creates the nodes based on given information
book_node *
bstCreateNode(char *surname, char initial, char *number, char *key){

	int i=0;


	book_node *node = NULL;

	node = (book_node*)malloc(sizeof(book_node));

	while(surname[i] != '\0'){
		node->surname[i] = surname[i];
		i++;
	}

	i=0;

	while(number[i] != '\0'){
		node->number[i] = number[i];
		i++;
	}

	i=0;

	while(key[i] != '\0'){
		node->key[i] = key[i];
		i++;
	}

	node->initial = initial;

	return node;

}

//finds the node that the data needs to be placed in, and calls bstCreateNode
void
bstInsertNode(char *surname, char initial, char *number, char *key, book_node *rootptr){

	book_node *currentNode = rootptr;
	book_node *nextNode = rootptr;

	while(currentNode != NULL){
		if(strcmp(key, currentNode->key) == 0){
			nextNode = currentNode->mid;
			if(nextNode == NULL){
				currentNode->mid = bstCreateNode(surname, initial, number, key);
				break;
			}
			else{
				currentNode = nextNode;
			}
		}
		else if(strcmp(key, currentNode->key) > 0){
			nextNode = currentNode->right;
			if(nextNode == NULL){
				currentNode->right = bstCreateNode(surname, initial, number, key);
				break;
			}
			else{
				currentNode = nextNode;
			}
		}
		else{
			nextNode = currentNode->left;
			if(nextNode == NULL){
				currentNode->left = bstCreateNode(surname, initial, number, key);
				break;
			}
			else{
				currentNode = nextNode;
			}
		}

	}

}

//test function for traversing the tree
void
traverse(book_node *node){
	
	if(node == NULL){
		return;
	}

	traverse(node->left);

	printf("node key: %s\n", node->key);

	traverse(node->right);



}

//searches the tree for information based on surname and initial.
//prints to stdout the number of comparisons and writes to a file the surname, initial and all numbers
//associated with that name
int
bstSearch(char *surname, char initial, book_node *rootptr, FILE *fp){

	book_node *node = rootptr;
	int comparisons = 0;
	int found = 0;
	bstCreateKey(surname, initial);

	fprintf(fp, "%s %c", surname, initial);


	while(node != NULL){

		comparisons++;
		
		if(strcmp(key,node->key)==0){
			fprintf(fp, " %s\n", node->number);

			found = 1;
			node = node->mid;
			while(node != NULL){
				fprintf(fp, " %s\n", node->number);
				node = node->mid;
			}
		}

		else if(strcmp(key, node->key) > 0){
			node = node->right;
		}

		else{
			node = node->left;
		}


	}

	if(found == 0){
		fprintf(fp, " NOTFOUND\n");
	}

	return comparisons;

}