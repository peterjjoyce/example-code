/*
###############################################################################
# @author Peter J. Joyce IV
# @author Sean Themar
# Project 1 Exercise B/C/D
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
#   en.wikipedia.org/wiki/Unix_time
# program description:
#   This program produces a report on the following kernel statements:
#      1)  CPU type and model
#      2)  Kernel version
#      3)  Amount of time since the system was booted (dd:hh:mm:ss)
#      4)  CPU time in user mode, system mode, and idle
#      5)  Number of disk reads/writes
#      6)  Number of context switches
#      7)  Time when the system was last booted
#      8)  Number of processes created
#      9)  Amount of memory
#      10) Amount of memory currently available
#      11) List of load averages
###############################################################################
*/

#include <stdio.h>
#include "kernelReport.h"
#include "fileReader.h"

int main() {

   printf("\n\n##########################################################\n");
   printf("This is the system's current state information:\n\t");

   printCPUtype();

   printKernelVersion();

   printUptime();

   printCPUtime();

   printDiskRW();

   printNumContextSwitches();

   printTimeOfLastBoot();

   printNumProcCreated();

   printMemoryTotal();

   printMemoryAvailable();

   printLoadAverages();

   printf("\n\n##########################################################\n\n");

   return 0;
}
