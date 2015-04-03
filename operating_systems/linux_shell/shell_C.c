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
#include <fcntl.h>

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

			/* execute the command inside the thread */
			execvp(decapsulated_args[0], decapsulated_args);
		}
}

/* This function parses the command given by the user looking for indicators
   of I/O redirection or a needed background process by looking for the '&',
   '<', and '>' chars. It alters flags that must be created before being
   called, creates a copy of the command given its typically small size coupled
   witht the rationale of easier referencing and stability and returns 0 
   on success */
/* There is currently a bug that creates a segmentation fault when the user
   attempts to use pipes */
int parse_command(int * num_elements, int * create_background_process, 
	int * amp_index, int * use_redirection, int * redirect_index, 
	int * use_pipes, int * pipe_index, char ** args_parse){
	int i = 0;
	while(args_parse[i] != NULL) {
		if(strcmp(args_parse[i], "&") == 0) {
			*amp_index = i;
			*create_background_process = 1;
		}
		if(strcmp(args_parse[i], "<") == 0 || strcmp(args_parse[i], ">") == 0){
			*redirect_index = i;
			*use_redirection = 1;
		}
		if(strcmp(args_parse[i], "|") == 0) {
			*pipe_index = i;
			*use_pipes = 1;
		}
		i++;
	}			
	*num_elements = i;
	printf("background? %d, redirect? %d, pipes? %d\n", *create_background_process, *use_redirection, *use_pipes);
	return 0; //success
} 

int main()
{

	char *line;
	char **args;

	printf("\n exited the BASH SHELL...\nentered the SIMPLE SHELL:");
	printf("\n enter 'exit' to exit and return to bash.\n\n");
	while (1) 
	{
		/* store number of elements in arg */
		int num_elements = 0;
		/* create a flag to determine whether to run the process in
		   the background */
		int create_background_process = 0;
		/* store location of '&' for removal */
		int amp_index = 0;
		/* create a flag to determine whether to use redirection */
		int use_redirection = 0;
		/* store location of '<' or '>' */
		int redirect_index = 0;
		/* create a flag to determine whether to use pipes */
		int use_pipes = 0;
		/* store location of '|' */
		int pipe_index = 0;
		
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
		   wants control over the shell back before the process is complete 
		   and whether I/O redirection will be necessary */
		parse_command(&num_elements, &create_background_process, &amp_index, 
			&use_redirection, &redirect_index, &use_pipes, &pipe_index, args);

		printf("num_elements is %d\n", num_elements);

		int case_ref = 0;
		if(create_background_process == 1) {
			case_ref = 1;
		}
		if(use_pipes == 1) {
			case_ref = 2;
		}

		/* There are currently three different cases available.

		   NOTE: I/O redirection is not yet functioning properly and is embedded
		   inside case 0. Attempts to implement piping will result in a
		   segmentation fault.

				0: standard fork and wait
					(currently attempts I/O redirection if user includes < or >)
				1: creates process in background and gives user control over
				   simple shell before process is completed
				2: creates two separate child processes using piping
		*/
		switch(case_ref){

			/* if the user does not indicate he/she wants to run a process in
			   the background we will defer to a standard fork and wait */
			case 0 :
				/* fork and have the child execute the command */
				if(fork() == 0) {
					/* if I/O redirection is used */
					if(use_redirection == 1){
						printf("redirect index is %d\n", redirect_index);
						char *afile = args[redirect_index +1];

						//get rid of the < or > operator in args
						int c;
						for (c = redirect_index; c < num_elements-1; c++) {
							args[c] = args[c+1];
							printf("%s\n", args[c]);
						}

						//get rid of the last element
						args[c] = NULL; printf("%s\n", args[c]);
						args[c+1]=NULL; printf("%s\n", args[c+1]);

						int k;
						for(k = 0; k <c+2; k++){
							printf("%s\n", args[k]);
						printf("%s\n", afile);
						int fd;
						fd = open(afile, O_WRONLY, O_CREAT);
						close(1);
						dup(fd);
						close(fd);

					}
					execvp(args[0], args);
				}
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
				*(args + amp_index) = NULL;

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

			/* if the user wants to execute two commands using piping */
			case 2 :;
				int l;
				int m ;
				char ** args_one;
				char** args_two;

				/* separate the command into two arguments */
				for(m = 0; m < pipe_index; m++){
					args_one[m] = args[m];
					printf("args_one at index %d is %s", m, args_one[m]);
				}
				m = 0;
				for(l = pipe_index+1; l < num_elements; l++) {
					args_two[m] = args[l];
					printf("args_two at index %d is %s", m, args_two[m]);
					m++;
				}
				
				int pipeID[2]; //indices into File Table
				pid_t pid1;
				pid_t pid2;
				pipe(pipeID);
				//pipeID[0] is file descriptor for writing
				//pipeID[1] is file descriptor for reading
				if((pid1=fork())==0) {
					printf("%d", pid1);
					//read(pipeID[0], TOK_BUFSIZE, num_elements-1);
				} else {
					//write(pipeID[1], TOK_BUFSIZE, num_elements-1);
				}
				break;
		}

		free(line);
		free(args);

	}

	return EXIT_SUCCESS;
}