/*
###############################################################################
# @author Peter J. Joyce IV
# @author Sean Themar
# Project 1 Exercise B
# CSCE 444 Spring 2015
# 3.4.2015
# Language used: C
# Compiler used: GNU Debian 4.4.5-8 (gcc)
# sources consulted:
#   en.wikipedia.org/wiki/Procfs
#   stackoverflow.com/questions/9629850/how-to-get-cpu-info-in-c-on-linux-such
#      -as-number-of-cores
#   www.open-std.org/jtc1/sc22/wg14/www/standards.html
#   www.asciitable.com
#   www.linuxhowtos.org/System/procstat.htm
# program description:
#   This program produces a report on the following kernel statements:
#      1) CPU type and model
#      2) Kernel version
#      3) Amount of time since the system was booted (dd:hh:mm:ss)
###############################################################################
*/

#include "kernelReport.h"
#include "fileReader.h"

/* This function prints the CPU type and model using the system() function,
   cat, and grep.
*/
int printCPUtype(){
   printf("\n\n-- CPU type and model:\n");
   system("cat /proc/cpuinfo | grep model");
   return 0;
}

/* This function prints the current kernel version using the system() function,
   cat, and grep.
*/
int printKernelVersion(){
   printf("\n\n-- Kernel version:\n");
   system("uname -a");
   return 0;
}

/* This function reads the /proc/uptime system file, stores the system's current
   uptime in seconds, and prints to the screen a formatted version of the uptime
   in the form dd:hh:mm:ss.
*/
int printUptime() {
   printf("\n\n-- Time since boot:\n");
   printf("\t\tdd:hh:mm:ss\n\t\t");
   /* we will use a reference to a system file /proc/uptime, which stores the
      current uptime in seconds and the amount of that time that was spend idle.
      Using that file we can use the function fileToInt() to store the current
      uptime in seconds as an int data type.
   */
   //const char *uptimeFilename = "/proc/uptime";
   const char *uptimeMode = "rb";
   int uptimeInSeconds = getIntFromFile("/proc/uptime", uptimeMode);

   /* Now that we have the uptime in seconds we can use integer division
      to get the days, hours, months, and seconds.
   */
   int timeSegment = 0;
 
  // print days
   timeSegment = uptimeInSeconds/86400;
   uptimeInSeconds = uptimeInSeconds%86400;
   if(timeSegment<10)
      printf("0");
   printf("%d:", timeSegment);

   // print hours
   timeSegment = uptimeInSeconds/3600;
   uptimeInSeconds = uptimeInSeconds%3600; 
   if(timeSegment<10)
      printf("0");
   printf("%i:", timeSegment);

   // print minutes
   timeSegment = uptimeInSeconds/60;
   uptimeInSeconds = uptimeInSeconds%60; 
   if(timeSegment<10)
      printf("0");
   printf("%i:", timeSegment);
 
   // print seconds
   printf("%i", uptimeInSeconds);

   return 0;
} // end printUptime()

/* This function prints to the screen the CPU time in user mode, system mode,
   and idle.
*/
int printCPUtime(){
   printf("\n\n-- CPU time:\n\t\tuser\t\tsystem\t\tidle\n");
   /* First we have to create parameters that will be passed to the function
      getLineFromFile(), which will return a char * pointing to a series of char
      values received from the file line.
   */
   char * testFilename = "/proc/stat"; // file containing CPU times
   char * testMode = "rb"; // stat is a non-text file
   char * testDel = "cpu0"; // the first word of the line we are looking for
   int delLength = 4; // number of characters in testDel
   // lineLength will be altered by the function getLineFromFile()
   int lineLength = 0;

   char * testCharFromFile = getLineFromFile(testFilename, testMode, testDel, delLength, &lineLength);

   /* Now that we have our line as a series of chars we can look for the data
      we are seeking. The linux stat file contains a line beginning with cpu
      that aggregates the time from all the CPUs.  We want time for the user
      mode, system mode, and in idle.  These are the first, third, and fourth
      numerical values respectively just after the word "cpu".  We can disregard
      the second number, which tracks niced processes in user mode.
   */
   int k = 0;
   int wordNumber = 1; // we start on the first word
   while(k<lineLength) {
      if(testCharFromFile[k] == ' '){
         wordNumber++;
         k++;
         /* We want to print the second, fourth, and fifth words */
         if(wordNumber == 2 || wordNumber == 4 || wordNumber == 5)
            printf("\t\t");
      }
      if(wordNumber == 2 || wordNumber == 4 || wordNumber == 5)
         printf("%c", testCharFromFile[k]);
      k++;
   }
   printf("\n");
   return 0;
}

/* This function prints to the screen the number of disk read/writes.
*/
int printDiskRW(){
   
   return 0;
}

/* This function prints to the screen the number of context switches.
*/
int printNumContextSwitches(){
   return 0;
}

/* This function prints to the screen the time when the system was last booted.
*/
int printTimeOfLastBoot(){
   return 0;
}

/* This function prints to the screen the number of processes created.
*/
int printNumProcCreated(){
   return 0;
}

/* This function prints to the screen the amount of memory.
*/
int printMemoryTotal(){
   return 0;
}

/* This function prints to the screen the amount of memory available.
*/
int printMemoryAvailable(){
   return 0;
}

/* This function prints to the screen a list of load averages with each averaged
   over the last minute.
*/
int printLoadAverages(){
   return 0;
}


