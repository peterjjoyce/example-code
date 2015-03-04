/*
###############################################################################
# @author Peter J. Joyce IV
# @author Sean Themar
# Project 1 Exercise B/C/D
# CSCE 444 Spring 2015
# 3.4.2015
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

/* This function prints to the screen a formatted version of the system uptime
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
   int uptimeInSeconds = getIntFromFile("/proc/uptime", "rb");

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

   // lineLength will be altered by the function getLineFromFile()
   int lineLength = 0;

   /* /proc/stat is the file containing the CPU times and is not a text file so
      we use the rb mode rather than the r mode. "cpu0" is the first word of the
      line we are looking for and that has 4 characters.
   */
   char * lineFromFile = getLineFromFile("/proc/stat", "rb", "cpu0", 4, 
      &lineLength);
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
      if(lineFromFile[k] == ' '){
         wordNumber++;
         k++;
         /* We want to print the second, fourth, and fifth words */
         if(wordNumber == 2 || wordNumber == 4 || wordNumber == 5)
            printf("\t\t");
      }
      if(wordNumber == 2 || wordNumber == 4 || wordNumber == 5)
         printf("%c", lineFromFile[k]);
      k++;
   }
   return 0; // we should never get here
}

/* This function prints to the screen the number of disk read/writes.
*/
int printDiskRW(){
   printf("\n\n-- Number of disk read and writes:\n\t\t");
   int lineLength = 0;
   char * lineFromFile = getLineFromFile("/proc/diskstats", "rb", " ", 1, 
      &lineLength);
   int flag = 0;
   int k = 0;
   int wordNumber = 1;
   while(k<lineLength) {
      if(lineFromFile[k] == ' '){
         wordNumber++;
         k++;
      }
      /* The if statement checks to see if we are 9 spaces from the delimiting
         character and prints the "Disk Reads: " and number of reads provided by
         the line that lineFromFile received from /proc/diskstats.
      */
      if(wordNumber == 9){
         /* The if statement checks if flag is 0, if flag is 0, we print Disk
            Reads: and set flag to 1.
         */
         if(flag == 0){
            printf("Disk Reads:  ");
            flag = 1;
         }
         printf("%c", lineFromFile[k]);
      }
      /* The if statement checks to see if we are 13 spaces from the delimiting
         character and prints the "Disk Writes: " and number of writes provided
         by the line that lineFromFile received from /proc/diskstats.
      */
      if(wordNumber == 13){
         /* The if statement checks if flag is 1, if flag is 1, we print Disk 
            Writes: and set flag to 2
         */
         if(flag == 1){
            printf("\n\t\tDisk Writes: ");
            flag = 2;
         }
         printf("%c", lineFromFile[k]);     
      }
      k++;
   }
   return 0;
}

/* This function prints to the screen the number of context switches.
*/
int printNumContextSwitches(){
   /* This function uses a similar methodology as printCPUtime(). See that
      function for more detailed comments. */
   printf("\n\n-- Number of context switches:\n\t\t");

   int lineLength = 0;
   char * lineFromFile = getLineFromFile("/proc/stat", "rb", "ctxt", 4, 
      &lineLength);

   int k = 0;
   int wordNumber = 1;
   while(k<lineLength) {
      if(lineFromFile[k] == ' '){
         wordNumber++;
         k++;
      }
      if(wordNumber == 2)
         printf("%c", lineFromFile[k]);
      k++;
   }
   return 0;
}

/* This function prints to the screen the time when the system was last booted.
*/
int printTimeOfLastBoot(){
   /* This function uses a similar methodology as printCPUtime(). See that
      function for more detailed comments. */
   printf("\n-- Time of last boot:\n\t\t");

   int lineLength = 0;
   char * lineFromFile = getLineFromFile("/proc/stat", "rb", "btime", 5, 
      &lineLength);

   time_t secSinceEpochAtBoot = 0; // we make this a time_t type for formatting
   int k = 0;
   int wordNumber = 1;
   while(k<lineLength) {
      if(lineFromFile[k] == ' '){
         wordNumber++;
         k++;
      }
      if(wordNumber == 2){
         if(lineFromFile[k]>47 && lineFromFile[k]<58)// if its a digit
            secSinceEpochAtBoot = 10 * secSinceEpochAtBoot + 
            (lineFromFile[k] - 48);
         else
            k = lineLength; // if we start reading non-digits we're done
      }
      k++;
   }
   /* Now we have to format the seconds since the Unix Epoch at boot into
      a readable format displaying local time. We can use ctime().
   */
   printf("%s", ctime(&secSinceEpochAtBoot));
   
   return 0;
}

/* This function prints to the screen the number of processes created.
*/
int printNumProcCreated(){
   /* This function uses a similar methodology as printCPUtime(). See that
      function for more detailed comments. */
   printf("\n-- Number of processes created:\n\t\t");

   int lineLength = 0;
   char * lineFromFile = getLineFromFile("/proc/stat", "rb", "proce", 5, 
      &lineLength);

   int k = 0;
   int wordNumber = 1;
   while(k<lineLength) {
      if(lineFromFile[k] == ' '){
         wordNumber++;
         k++;
      }
      if(wordNumber == 2)
         printf("%c", lineFromFile[k]);
      k++;
   }
   return 0;
}

/* This function prints to the screen the amount of memory.
*/
int printMemoryTotal(){
   /* This function uses a similar methodology as printCPUtime(). See that
      function for more detailed comments. */
   printf("\n-- Total usable memory:\n\t\t");

   int lineLength = 0;
   char * lineFromFile = getLineFromFile("/proc/meminfo", "rb", "MemTotal", 8, 
      &lineLength);

   int k = 0;
   int wordNumber = 1;
   while(k<lineLength) {
      if(lineFromFile[k] == ' '){
         wordNumber++;
         k++;
      }
      if(wordNumber > 1 && lineFromFile[k] != 32)
         printf("%c", lineFromFile[k]);
      k++;
   }
   return 0;
}

/* This function prints to the screen the amount of memory available.
*/
int printMemoryAvailable(){
   /* This function uses a similar methodology as printCPUtime(). See that
      function for more detailed comments. */
   printf("\n-- Total usable memory:\n\t\t");

   int lineLength = 0;
   char * lineFromFile = getLineFromFile("/proc/meminfo", "rb", "MemFree", 7, 
      &lineLength);

   int k = 0;
   int wordNumber = 1;
   while(k<lineLength) {
      if(lineFromFile[k] == ' '){
         wordNumber++;
         k++;
      }
      if(wordNumber > 1 && lineFromFile[k] != 32)
         printf("%c", lineFromFile[k]);
      k++;
   }
   return 0;
}

/* This function prints to the screen a list of load averages with each averaged
   over the last minute.
*/
int printLoadAverages(){
   printf("\n-- Load averages:\n\t\t1 min\t\t5 min\t\t15 min\n\t\t");
   /* For this function we don't know the first word of the line and the numbers
      are best stored as doubles for safety.  We will use fscanf again to read
      the file, which is only one line.
   */
   FILE * loadavgFile;
   double oneMinAvg, fiveMinAvg, fifteenMinAvg;
   char numTasks[32];
   int lastProcessPID;
   
   loadavgFile = fopen("/proc/loadavg", "rb");
   fscanf(loadavgFile, "%lf%lf%lf%s%d", 
      &oneMinAvg, &fiveMinAvg, &fifteenMinAvg, numTasks, &lastProcessPID);

   printf("%.2f\t\t%.2f\t\t%.2f", oneMinAvg, fiveMinAvg, fifteenMinAvg);

   fclose(loadavgFile);

   return 0;
}


