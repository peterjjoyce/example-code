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

#include <stdio.h>
#include "kernelReport.h"
#include "fileReader.h"

int main() {

   printf("\n\nThis is the system's current state information:\n\t");

   printCPUtype();

   printKernelVersion();

   printUptime();

   printCPUtime();

   

   return 0;
}
