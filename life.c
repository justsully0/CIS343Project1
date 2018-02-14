#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "file_utilities.h"

/* **********************************************************************************
// Name   	: MakeBoard
// About  	: Creates a game board to the user specifications with all 0's.
// Params 	: r - The rows for the board
//			: c - The columns for the board
// Returns	: board - The game board with all 0's
//******************************************************************************** */
char** makeBoard(int r, int c){

	int i, j, k = 0;

	//Allocate the memory for the game.
	char **board = (char**)malloc(r * sizeof(char*));
	
	//creating the memory for the rows of the board
	for (k = 0; k < r; k++){
		board[k] = (char *)malloc(c * sizeof(char)); 
	}

	//Initilazing the board with 0's
	for(i = 0; i < r; i++){
		for(j = 0; j < c; j++){
			board[i][j] = '0';
		}
	}
	return board;
}

/* **********************************************************************************
// Name   	: displayBoard
// About  	: prints the given board to the screen.
// Params 	: r - The rows of the given board.
//			: c - The columns of the given board
//			: board - The game board to display
// Returns	: Void
//******************************************************************************** */
void displayBoard(int r, int c, char **board){

	int i, j = 0;
	//print the board
	printf("=============================\n");
	for(i = 0; i < r; i++){
		for(j = 0; j < c; j++){
			printf("%c",board[i][j]);
		}
		printf("\n");
	}
	printf("=============================\n");

	return;
}

/* **********************************************************************************
// Name   	: runMenu
// About  	: Runs the menu and accepts the input, which is passed on to the main 
//			: class to handle
// Params 	: None
// Returns	: retVal - the user inputed value that determines the next move.
//******************************************************************************** */
int runMenu(){
	printf("====== Menu =================\n");
	printf("0 -- Start with random board\n");
	printf("1 -- Save\n");
	printf("2 -- load\n");
	printf("3 -- Contiue 1 step\n");
	printf("4 -- Contiue X step(s)\n");
	printf("5 -- Quit\n");
	printf("=============================\n");
	int retVal=0;
	printf("Input: ");
	scanf("%d",&retVal);
	return retVal;
}

/* **********************************************************************************
// Name   	: save
// About  	: Saves the game to a text file. 
// Params 	: r - The rows for the board
//			: c - The columns for the board
//			: board - The game board to save.
// Returns	: Void
//******************************************************************************** */
void save(int r, int c, char **board){

	//User input
	char *fileName = (char*)malloc(100 * sizeof(char));
	printf("100 characters, extension will be added.\n");
	printf("Please give your save file a name: ");
	scanf("%s",fileName);

	//adding .txt and the location of the file
	//There may be a better way to do this but I dont have time.
	char filepath[100];
	char fileExt[10];
	strcpy (fileExt, ".txt"); 
	strcpy(filepath, "SavedTextFiles/");
	strcat(filepath,fileName);
	strcat(filepath,fileExt);

	int i, retVal = 0;

	//Print the board into the text file.
	//using file_utilities
	for (i =0; i<r; i++){
		char *buffer = board[i];
		int size = sizeof(char*);
		retVal = write_file(filepath, buffer, c);			
		if(retVal == -1){
			printf("There was an error saving the board, please try agian.\n");
			return;
		}
	}

	return;
}

/* **********************************************************************************
// Name   	: load
// About  	: Loads a game board from a given text file.
// Params 	: board - The game board to load a given board into.
// Returns	: rowXcol - An array that contains the rows and columns of the game board
//			: this will return -1 if there is an error.
//******************************************************************************** */
int* load(char ***board){

	//User input
	char *fileName = (char*)malloc(100 * sizeof(char));
	printf("100 characters, extension will be added.\n");
	printf("Please enter the name of the file you wish to load: ");
	scanf("%s",fileName);
	
	//adding .txt and the location of the file
	//There may be a better way to do this but not a requirement.
	char filepath[100];
	char fileExt[10];
	strcpy (fileExt, ".txt"); 
	strcpy(filepath, "SavedTextFiles/");
	strcat(filepath,fileName);
	strcat(filepath,fileExt);

	//using file_utilities
	char *buffer;
	int retVal = read_file(filepath, &buffer);
	int *rowXcol[2];

	//If there is an error
	if (retVal == -1){
		rowXcol[0] = &retVal;
		rowXcol[1] = &retVal;
		return *rowXcol;
	}
	//Find rows and cols based on the new line character
	char *tmp = buffer;
	int rows = 0;
	while(tmp = strstr(tmp, "\n")){
		rows++;
		tmp++;
	}

	free(tmp);
	int size = (int)strlen(buffer); 
	int cols = (size - rows) / rows; 
	rowXcol[0] = &rows; 
	rowXcol[1] = &cols; 


	//make a temp board
	char** retBoard = makeBoard(cols,rows); 
	int *preventWarning = realloc(*board, sizeof(retBoard)); 

	//read buffer int the temp board
	int tempItr=0;
	for(tempItr = 0; tempItr<(rows*(cols + 1)); tempItr++){
		if(buffer[tempItr] == '\n')
			continue;
		else
			retBoard[ tempItr/(cols+1) ][ tempItr % (cols+1) ] = buffer[tempItr];
		
	}

	//make sure the right info is sent back & free memory
	*board = retBoard;
	free(buffer);

	return *rowXcol;
}

/* **********************************************************************************
// Name   	: contOne
// About  	: Continues one iteration of the game, based on give rules.
// Params 	: r - The rows for the board.
//			: c - The columns for the board.
//			: board - The game board to update.
// Returns	: board - The updated game board
//******************************************************************************** */
char **contOne(int r,int c, char **board){

	char **retBoard = makeBoard(r,c);
	int i, j = 0;

	int aliveNeighbor=0;
	int deadNeighbor = 0;
	
	//This is the loop to check through the current board
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{

			aliveNeighbor = 0;
			deadNeighbor = 0;

			//Place the bounds of the current cells neighbors
			int rBot = i - 1;
			int rTop = i + 1;
			int cBot = j - 1;
			int cTop = j + 1;

			//Check if the current cell is on the boarder
			if(i == 0)
				rBot = 0;
			else if (i == r-1)
				rTop = r-1;
			if(j == 0)
				cBot = 0;
			else if (j == c-1)
				cTop = c-1;

			//check the cells neighbors and count alive or dead
			int tempRctr = rBot;
			int tempCctr = cBot;

			for (tempRctr; tempRctr <= rTop; tempRctr++)
			{
				for (tempCctr; tempCctr <= cTop; tempCctr++)
				{	
					if(tempRctr == r && tempCctr == c)
						continue;
					else if(board[tempRctr][tempCctr] == '1')
						aliveNeighbor++;
					else
						deadNeighbor++;
				}
				tempCctr = cBot;
			}

			//Check our rules.
			if(aliveNeighbor == 3)
				retBoard[i][j] = '1';
			else if (aliveNeighbor == 2 && board[i][j] == '1')
				retBoard[i][j] = '1';
			else
				retBoard[i][j] = '0';
		}
	}

	//free memory and return correct data
	int tempItr=0;
	for(tempItr=0; tempItr<r;tempItr++)
		free(board[tempItr]);
	free(board);
	board = retBoard;
 	
	return board;
}

/* **********************************************************************************
// Name   	: cont
// About  	: Coninues the game as many times as the user specifies.
// Params 	: r - The rows for the board.
//			: c - The columns for the board.
//			: board - The game board to save.
//			: steps - The number of times to continue the game.
// Returns	:
//******************************************************************************** */
char **cont(int r, int c, char **board, int steps){
	int temp = 0;

	//loops through the steps as many times as the user wants.
	for (temp; temp < steps; temp++)
		board = contOne(r,c,board);
	return board;
}

/* **********************************************************************************
// Name   	: randomBoard
// About  	: Creates a random game board, based on the users specifications.
// 			: Note: not actually random, because there is no built in random function
//			: that is actually perfect. This is not a requirment of the assignment.
// Params 	: r - The rows for the board.
//			: c - The columns for the board.
//			: board - The game board to save.
// Returns	: Void
//******************************************************************************** */
void randomBoard(int r, int c, char **board){
	int total = r * c;

	//User input
	printf("Enter number of alive cells to start. If your value \nis invalid the number of alive cells will default"  
		 "\nto 20 percent of %d: ",total);

	int numAlive = 1;
	scanf("%d",&numAlive);

	//Validation.
	if(numAlive > total || numAlive < 1){
		numAlive = total * .2;
	}

	int i = 0;

	//Not actually random... but close enough for the time alloted and purpose of the game.
	//select the random position of an alive cell.
	for(i; i < numAlive; i++){
		int rx = rand() % r;
		int ry = rand() % c;
		if(board[rx][ry] == '1'){
			i--;
		}else{
			board[rx][ry] = '1';
		}
	}
	
	return;
}