#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



/* **********************************************************************************
// Name   	: read_file 
// About  	: will read input from a text file, and save it to a passed buffer.
// Params 	: filename - The name of a file to read
//			: buffer - The data that will be read in from a file.
// Returns	: size - The size of a file.
// Citation	: I used the following teo links, to help create this function
//			: https://stackoverflow.com/questions/8236
//			: 	/how-do-you-determine-the-size-of-a-file-in-c?noredirect=1&lq=1
//			: http://www.cplusplus.com/reference/cstdio/fseek/
//******************************************************************************** */
int read_file( char* filename, char **buffer ){

	//Create the file pointer
	FILE *fp = fopen( filename, "r" );

	//Determine if the file exsists
	if(fp == NULL)
		return -1;

	//get the file size
	int size = 0;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	//Point to the start of the file
	fseek(fp, 0L, SEEK_SET);

	//If the file is empty
	if (size == 0)
		return -1;
	
	//Allocate the memory for the input and read the file
	*buffer = (char *)malloc(size * sizeof(char));
	fread(*buffer, sizeof(char), size ,fp);

	//Close the file pointer
	fclose(fp);

	//return the size of the file
	return size;
}


/* **********************************************************************************
// Name   	: write_file 
// About  	: Will write(append) data to a text file. 
// Params 	: filename - The name of a file to write to.
//			: buffer - The data that will be saved to the file.
// 			: size - The size of the data to be saved.
// Returns	: an integer value if there is an error it will return -1.
//******************************************************************************** */

//Citation: My old projects from CIS241
int write_file( char* filename, char *buffer, int size){

	//create a pointer to the file.
	FILE *fp;
	fp = fopen( filename, "a" );

	//write to the file
	int checkSize = fwrite(buffer, sizeof(char), size ,fp);
	fwrite("\n", sizeof(char), 1, fp);

	//close the file
	fclose(fp);

	//make sure it all ran alright.
	if(checkSize == size)
		return 0;
	else
		return -1;
}