#include "dict.h"


/*

	Program written by Russell Long for COMP20003 Design of Algorithms project 1 2014 Sem 2.

	This is the driver program for the creation of a binary search tree through bst2.c along with
	the seperation of input from an input file for input to the tree and the ability to allow
	user input for people to find in the tree.

	Running the program: dict1 <inputfile> <outputfile>

	Input: command line argument containing a file with text formmated as <surname> <initial> <phonenumber>
	After this, user may input lines for people to search for e.g. <surname> <initial>

	output: Will out to stdout the number of comparisons it took in the tree to find the surname and initial
	you searched for.
	Will also output a file named by the second command line argument which contains the surname and initial
	of the person you searched for, and the phone number for that person, and any others whos name is the same
	e.g. <surname> <initial> <number1>
	<number2>
	<number3>


*/



int
main(int argc, char **argv){
	printf("\nProgram started\n\n");


	char line[MAXLINELEN];
	FILE *fp1;
	FILE *fp2;
	char surname[MAXFIELDLEN], initial, phonenum[PHONELEN];
	book_node *rootptr = NULL;

	//Check if there are enough arugments for the program
	if(argc != 3){
		printf("Usage: dict1 x y, where x is the name of the phonebook file and y is the name of the output file.\n");
		exit(ARGERROR);
	}
	
	//check that the file can be opened
	if( (fp1=fopen(argv[1], "r")) == NULL){
		printf("Error opening file in\n");
		exit(FILEERROR);
	}


	fp2=fopen(argv[2], "w");


	//read in all the lines from the input file and pass them into the create tree function
	while(fgets(line, sizeof(line), fp1))
	{

		sscanf(line,"%s %c %s", surname, &initial, phonenum);
		rootptr = bstAddData(surname, initial, phonenum, rootptr);

	}

	//read in from stdin and search for the given names in the tree through the search function
	while((fgets(line,MAXLINELEN,stdin)) != NULL){
		
		int comparisons; 

		sscanf(line, "%s %c", surname, &initial);
		comparisons = bstSearch(surname, initial, rootptr, fp2);
		printf(" %d\n", comparisons);

	}
	return 0;
}
