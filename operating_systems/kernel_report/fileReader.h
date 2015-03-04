/*
###############################################################################
# @author Peter J. Joyce IV
# @author Sean Themar
# Project 1 Exercise B/C/D
# CSCE 444 Spring 2015
# 3.4.2015
###############################################################################
*/

#ifndef _FILEREADER_H
#define _FILEREADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This function reads a file and loops through each line looking for the word
   passed as a parameter.  When it finds that word it returns the line as a char
   array.
*/
char * getLineFromFile(const char *, const char *, const char *, int, int *);

/* This function assumes it is being passed the name of a file that contains
   an integer as the first item.  It reads the file and returns an integer that 
   is read from the file.
*/
int getIntFromFile(const char *, const char *);

#endif
