#include "fileReader.h"

/* This function reads a file and loops through each line looking for the word
   passed as a parameter.  When it finds that word it returns the line as a char
   array.
*/
char* getLineFromFile(const char *filename, const char *mode, const char* del, int i, int * lineLength){
   FILE *this_file = fopen(filename, mode);
   char *arg = 0;
   size_t size = 0;
   int sizeOfDel = i;

   int flag = 1; // will be set to -1 if the delimeter doesn't match the line
   while(*lineLength != -1) {//while there is a line
      i = 0;
      flag = 1;
      *lineLength = getline(&arg, &size, this_file);
      while(i<sizeOfDel) { //check each line for a match to the delimiting char array
         if(arg[i]!=del[i]) {
            /* when the character of the line doesn't match the delimiter
               setting i to -1 means we won't check the rest of the characters.
            */            
            i = sizeOfDel; // skip to the end of the del array
            flag = -1; // this line is not the right one
         }
         i++;
      }
      if(flag!=-1){ // this must be the right line
         return arg; // so return it
      }
   }
   free(arg);
   fclose(this_file);
   *lineLength = -1; //getline() will make this -1 if there is an error as well
   char *delNotFoundIndicator = "error";
   return delNotFoundIndicator;
}



/* This function assumes it is being passed the name of a file that contains
   an integer as the first item.  It reads the file and returns an integer that 
   is read from the file.
*/
int getIntFromFile(const char *filename, const char *mode) {
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

