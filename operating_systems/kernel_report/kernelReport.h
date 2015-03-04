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
#include <string.h>

int printCPUtype();

int printKernelVersion();

/* This function prints to the screen a formatted version of the uptime
   in the form dd:hh:mm:ss.
*/
int printUptime();

/* This function prints to the screen the CPU time in user mode, system mode,
   and idle.
*/
int printCPUtime();

/* This function prints to the screen the number of disk read/writes.
*/
int printDiskRW();

/* This function prints to the screen the number of context switches.
*/
int printNumContextSwitches();

/* This function prints to the screen the time when the system was last booted.
*/
int printTimeOfLastBoot();

/* This function prints to the screen the number of processes created.
*/
int printNumProcCreated();

/* This function prints to the screen the amount of memory.
*/
int printMemoryTotal();

/* This function prints to the screen the amount of memory available.
*/
int printMemoryAvailable();

/* This function prints to the screen a list of load averages with each averaged
   over the last minute.
*/
int printLoadAverages();

#endif
