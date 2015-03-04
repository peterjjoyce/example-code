/*
###############################################################################
# @author Peter J. Joyce IV
# @author Sean Themar
# Project 1 Exercise B/C/D
# CSCE 444 Spring 2015
# 3.4.2015
###############################################################################
*/

#ifndef _KERNELREPORT_H
#define _KERNELREPORT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
