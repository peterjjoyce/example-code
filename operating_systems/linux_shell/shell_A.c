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
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

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
char *readLine(void)
{
  char *line = NULL;
  ssize_t bufsize = 0;
  getline(&line, &bufsize, stdin);
  return line;
}
int main()
{

	char *line;
	char **args;
	int status;

	printf("\n exited the BASH SHELL...\nentered the SIMPLE SHELL:");
	printf("\n enter 'exit' to exit and return to bash.\n\n");
	while (1) 
	{
		/* Print prompt */
		printf("$$imple$hell$  ");
		/* flush all open output streams */
		fflush(NULL);
		//getline(&line, 0, stdin);
		line = readLine();
		args = lineSplitter(line);

		/* if the user typed "exit" exit the shell program */
		if (strcmp(args[0], "exit") == 0){
			printf("you will be returned to the standard bash shell...\n\n");
			sleep(1);
			exit(0);
		}

		/* fork and have the child execute the command */
		if(fork() == 0) {
			execvp(args[0], args);
		/* have the parent wait */
		} else {
			wait(&status);
		}

		free(line);
		free(args);

	}

	return 0;
}