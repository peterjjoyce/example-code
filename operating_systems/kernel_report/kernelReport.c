/*
###############################################################################
# @author Peter J. Joyce IV
# @author Sean Themar
# Project 1 Exercise B
# CSCE 444 Spring 2015
# 2.25.2015
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

/* This function uses the C library function system() to call the unix commands
   cat and grep in order to read and print information from the file 
   /proc/cpuinfo. Specifically it produces a report containing the prespecified
   state information for CPU type/model, Kernel version, and ammount of time
   since the system was booted.
*/
int produceReport() {

   printf("\n\nThis is the state information for:\n\t");
   printf("1. CPU type and model\n\t");
   printf("2. Kernel version\n\t");
   printf("3. Amount of time since the system was booted\n");
   printf("\tformatted as dd:hh:mm:ss\n");

   printf("\n1.\n");
   system("cat /proc/cpuinfo | grep model");

   printf("\n2.\n");
   system("uname -a");
   
   printf("\n3.\n");
   printf("dd:hh:mm:ss\n");
   printUptime();

   //test new function
   char * testFilename = "/proc/stat";
   char * testMode = "rb";
   char * testDel = "cpu";
   char * testCharFromFile = getLineFromFile(testFilename, testMode, testDel);
   int k;
   for(k = 0; k<12; k++) {
      printf("%c", testCharFromFile[k]);
   }
   printf("\n");
}

/* This function reads the /proc/uptime system file, stores the system's current
   uptime in seconds, and prints to the screen a formatted version of the uptime
   in the form dd:hh:mm:ss.
*/
int printUptime() {
   /* we will use a reference to a system file /proc/uptime, which stores the
      current uptime in seconds and the amount of that time that was spend idle.
      Using that file we can use the function fileToInt() to store the current
      uptime in seconds as an int data type.
   */
   const char *uptimeFilename = "/proc/uptime";
   const char *uptimeMode = "rb";
   int uptimeInSeconds = fileToInt(uptimeFilename, uptimeMode);

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

int fileToInt(const char *filename, const char *mode) {
   /* store as a file a pointer to /proc/uptime. Since this is not a simple
      text file we use "rb" instead of "r". */
   FILE *uptime = fopen(filename, mode);
   /* the getdelim() function requires the first argument to be passed be a
      valid pointer capable of being passed to the free() function later to
      deallocate memory. It is usually 0 indicating the first block of malloc
      will be used (when it is not already in use).
   */
   char *arg = 0;
   /* the second argument for getdelim() indicates the size of the block being
      pointed to by the first argument.  Since we have not used memory yet it
      will be zero and automatically resized. It must be of type size_t.
   */
   size_t size = 0;

   /* we will need a numerical data type variable to store the formatted version
      in. Because we are only concerned with seconds as the smallest quantity of
      time we can use integers.  This will also allow us to do integer division
      to acheive proper dd:hh:mm:ss formtting without ugly casts.
   */
   int digit = 0;
   int integerFromFile = 0;

   while(getdelim(&arg, &size, 0, uptime) != -1) {
      /* we will change the char pointer value to a float value using
         simple ascii arithmetic.  The smallest value we are concerned with
         is seconds so we can discard any numbers after the decimal point.
         After the arithmetic the decimal point will be stored as -2 so we can
         loop through each digit until we get a negative digit.
      */
      int i;  
      for(i = 0; (digit >=0) && (digit <=9); i++) {
         digit = arg[i] - '0';
         if(digit>=0) {// in other words, if digit is an actual digit
            // add the digit onto the variable for uptime (in seconds)
            integerFromFile = (integerFromFile * 10) + digit;
         }
      }
   }
   free(arg); // deallocates memory used by getdelim()
   fclose(uptime); // closes the file
   return integerFromFile;
} // end fileToInt()

char* getLineFromFile(const char *filename, const char *mode, const char* del){
   FILE *this_file = fopen(filename, mode);
   char *arg = 0;
   size_t size = 0;
   int i = sizeof(del); // store the length of del (delimeter) char array
   i = i/4; // sizeof() returns byte size so we divide by 4 to get n elements
   int flag = 1; // will be set to -1 if the delimeter doesn't match the line
   while(getline(&arg, &size, this_file) != -1) {//while there is a line
      while(i>=0) { //check each line for a match to the delimiting char array
         if(arg[i]!=del[i]) {
            /* when the character of the line doesn't match the delimiter
               setting i to -1 means we won't check the rest of the characters.
            */            
            i = -1; // skip to the end of the del array
            flag = -1; // this line is not the right one
         }
         i--;
      }
      if(flag!=-1)
         return arg;
   }
   char *delNotFoundIndicator = "error";
   return delNotFoundIndicator;
}
