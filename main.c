#include "header.h"
#include "file_utilities.h"

//**********************************************************************************
// Name   	: Main
// About	: Runs the Game of Life program. Runs a loop and uses boolean logic to 
//			: determine the next action to take.
// Params 	: argc - Integer value, number of elements in argsv.
//			: argsv - In this case the values of of our game board.
// Returns	: an int value
//**********************************************************************************
int main(int argc, char* argsv[]){

	if(isdigit(*argsv[1]) && isdigit(*argsv[2])){

		int rows = atoi(argsv[1]);
		int cols = atoi(argsv[2]);
		int uInput = 0;
		
		//Create the game board
		char **board = NULL;

		//Loop that basically runs the game.
		do{

			uInput = runMenu();

			//Make random board
			if(uInput == 0){

				//If the board hasn't been created
				if(!board){
					board = makeBoard(rows,cols);
					randomBoard(rows, cols, board);
					displayBoard(rows, cols, board);
				}

				//If the board has already been created, make a new board.
				else{
					int tempItr=0;
					for(tempItr=0; tempItr<rows;tempItr++)
						free(board[tempItr]);
					free(board);
					board = makeBoard(rows,cols);
					randomBoard(rows, cols, board);
					displayBoard(rows, cols, board);
				}
				
			}

			//save
			if(uInput==1){
				if(!board){
					printf("Please create a board first.\n");
					continue;
				}else{
					save(rows, cols, board);
				}
			}

			//load
			else if(uInput==2){

				//If the board hasn't been created
				if(board == NULL){
					//load the new board
					int* rowXcol = load(&board);

					//If ther was an error loading
					if(rowXcol[0] < 0){
						printf("File not found, or the file was empty. Please try again.\n");
						board = NULL;
					}else{
						rows = rowXcol[0];
						cols = rowXcol[1];

						displayBoard(rows, cols, board);
					}
				}

				//If the board has already been created, make a new board.
				else{
					//Make the new board
					int tempItr=0;
					for(tempItr=0; tempItr<rows;tempItr++)
						free(board[tempItr]);
					free(board);
					board = NULL;

					//load the new board
					int* rowXcol = load(&board);
					
					//If ther was an error loading
					if(rowXcol[0] < 0){
						printf("File not found, or the file was empty. Please try again.\n");
						board = NULL;
					}else{
						rows = rowXcol[0];
						cols = rowXcol[1];
						displayBoard(rows, cols, board);
					}
				}
			}

			//Continue One
			else if(uInput==3){
				if(!board){
					printf("Please create a board first.\n");
					continue;
				}else{
					board = contOne(rows,cols,board); 
					displayBoard(rows, cols, board);
				}
			}

			//Contunue x: Asks for user input of interations and calls the cont function
			else if(uInput==4){
				if(!board){
					printf("Please create a board first.\n");
					continue;
				}else{
					int steps=0;
					printf("How many iterations?: ");
					scanf("%d",&steps);
					board = cont(rows,cols,board,steps);
					displayBoard(rows, cols, board);
				}
			}
			else if(uInput == 5){
				break;
			}

		} while (uInput != 5 );
	}
	return 0;
}