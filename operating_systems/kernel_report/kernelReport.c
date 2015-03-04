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
   printf("dd:hh:mm:ss\n");
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
   printf("%i \n\n", uptimeInSeconds);

   return 0;
} // end printUptime()

/* This function prints to the screen the CPU time in user mode, system mode,
   and idle.
*/
int printCPUtime(){
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


