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

#ifndef _KERNELREPORT_H
#define _KERNELREPORT_H
#include <stdio.h>
#include <stdlib.h>

/* This function uses the C library function system() to call the unix commands
   cat and grep in order to read and print information from the file 
   /proc/cpuinfo. Specifically it produces a report containing the prespecified
   state information for CPU type/model, Kernel version, and ammount of time
   since the system was booted.
*/
int produceReport();

/* This function reads the /proc/uptime system file, stores the system's current
   uptime in seconds, and prints to the screen a formatted version of the uptime
   in the form dd:hh:mm:ss.
*/
int formatUptime();

#endif
