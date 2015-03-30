/*
###############################################################################
# @author Peter J. Joyce IV
# @author Sean Themar
# Project 2 Part A
# CSCE 444 Spring 2015
# 3.30.2015
# Language used: C
# Compiler used: GNU Debian 4.4.5-8 (gcc)
# sources consulted:
#   http://www.gnu.org/software/libc/manual/html_node/Implementing-a-Shell.html
#		Implementing-a-Shell
#	http://stephen-brennan.com/2015/01/16/write-a-shell-in-c/
#	http://comsci.liu.edu/~murali/unix/PThread.htm
# program description:
#   This program acts as a shimple shell:
#		1) echos the command to stdout
#		2)parses the command into tokens for *argv[]
#		3) finds the executable file argv[0]
#		4) creates a child to exec the program
###############################################################################
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/* This function tokenizes a char array and inserts each delimited word into
   a separate char array, returning a pointer to the first char pointer
*/
char **lineSplitter(char *line) {
	int bufsize = TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token, **tokens_backup;

	if(!tokens) {
		fprintf(stderr, "Allocation Error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOK_DELIM);
	while(token!=NULL) {
		tokens[position] = token;
		position++;

		 if (position >= bufsize) {
			bufsize += TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				free(tokens_backup);
				fprintf(stderr, "Allocation Error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

/* This function is used to read a line from a stream and return a type
   char *, rather than a char ** as getline() does by default.
*/
char *readLine(void)
{
  char *line = NULL;
  ssize_t bufsize = 0;
  getline(&line, &bufsize, stdin);
  return line;
}

/* This structure is used to encapsulate a pointer to a char pointer (char **)
   so that the data can be copied and utilized inside functions requiring
   void types, e.g., pthread_create().
*/
typedef struct args_param{
	char **encapsulated_args;
} args_param;

void *runner(void *param) {
		if(fork() == 0) {
			/* use param to create a copy of the struct containing out
			   encapsulated args */
			args_param *args_param_copy = (args_param *)param;
			/* now create a new char ** by decapsulating args from the struct
			   to be used in execvp() */
			char ** decapsulated_args;
			decapsulated_args = args_param_copy->encapsulated_args;

			execvp(decapsulated_args[0], decapsulated_args);
		}
}

int main()
{

	char *line;
	char **args;

	printf("\n exited the BASH SHELL...\nentered the SIMPLE SHELL:");
	printf("\n enter 'exit' to exit.\n\n");
	while (1) 
	{
		/* create a flag to determine whether to run the process in
		   the background */
		int create_background_process = 0;
		/* Print prompt */
		printf("$$imple$hell$  ");
		/* flush all open output streams */
		fflush(NULL);

		/* get typed command */
		line = readLine();
		/* parse the command */
		args = lineSplitter(line);


		/* if the user typed "exit" exit the shell program */
		if (strcmp(args[0], "exit") == 0){
			printf("you will be returned to the standard bash shell...\n\n");
			sleep(1);
			exit(0);
		}

		/* check to see if the user typed an "&" indicating he/she
		   wants control over the shell back before the process is complete */
		int i = 0;
		while(args[i] != NULL) {
			if(strcmp(args[i], "&") == 0) {
				create_background_process = 1;
				/* we'll use a goto statement so we stop searching once we've
				   found the '&' as well as to preserve its location in our
				   int value, i. */
				goto End_while;
			}
			i++;
		} End_while:

		switch(create_background_process){

			/* if the user does not indicate he/she wants to run a process in
			   the background we will defer to a standard fork and wait */
			case 0 :
				/* fork and have the child execute the command */
				if(fork() == 0) {
					execvp(args[0], args);
				/* have the parent wait */
				} else {
					int status;
					wait(&status);
				}
				break;

			/* if the user wants to put a process in the background we will
			   use a separate thread */
			case 1 :
				/* remove the '&'' from args */
				*(args + i) = NULL;

				/* create a struct to pass arguments to pthread_create() */
				struct args_param *command;
				command = (args_param *) malloc(sizeof(args_param));
				/* copy args to the struct */
				command->encapsulated_args = args;

				/* create a new thread */
				pthread_t tid;

				/* if pthread_create returned an error code alert the user*/
        		if (pthread_create(&(tid), NULL, &runner, (void *) command)) {
            		printf("\ncan't create thread.\nexiting...\n");
            		sleep(4);
            		return EXIT_FAILURE;
        		}

        		/* once runner is complete it can rejoin the parent shell */
        		pthread_join(tid, NULL);
				break;
		}

		free(line);
		free(args);

	}

	return EXIT_SUCCESS;
}