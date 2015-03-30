This is a series of three simple shell programs.  

Part A: Write a C program that acts as a simple shell
	creates a child and executes while the parent waits
Part B: Allows the &
Part C: Allows redirection and pipes

Parts A and B are largely complete, save some error
	checking implementation.

Part C remains incomplete.

	Redirection is at a 40% solution.
	There is an issue getting a file to write.
	Implmentation of reading a file to the screen
	is not yet started.

	Piping is at a 20% solution.
	There is currently a segmentation fault that occurs
	when trying to parse the command for the | indicator.
	Much of the body of the code remains incomplete.

###########################################################

COMPILATION INSTRUCTIONS

using the standard GNU c compiler (gcc) run:

	for Part A
		$ gcc -o shellA shell_A.c
		to compile
		$ ./shellA
		to execute

	for Part B
		$ gcc -pthread -o shellB shell_B.c
		to compile
		$ ./shellB
		to execute

	for Part C
		$ gcc -pthread -o shellC shell_C.c
		to compile
		$ ./shellC
		to execute

###########################################################