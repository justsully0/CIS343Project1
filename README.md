THE GAME OF LIFE

Author: Patrick McMahon

Contents:
1. README
2. lifeScript.sh
3. makefile
4. header.h
5. life.c
6. main.c
7. file_utilities.h
8. file_utilities.c

Instructions:
1. Run ./lifeScript with -h for help on how to use it.

Instructions running without the script:
1. gcc( or clang) life.c main.c file_utilities.c
2. ./a.out rows columns

makefile contents:
make - creates an a.out file executable file.
make clean - removes .o files and executable files

Known errors:
The game of life functionality is not perfect. The loading and saving are correct, but the actually "game play" is flawed.
Script will not allow you to enter just a (y)columns value.
