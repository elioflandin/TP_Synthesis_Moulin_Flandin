#include "main.h"

long calcul_time(struct timespec start, struct timespec end){
   long seconds = end.tv_sec - start.tv_sec;
   long nanoseconds = end.tv_nsec - start.tv_nsec;
   if (nanoseconds < 0) {
       seconds--;
       nanoseconds += 1000000000;  // Correction if the nanoseconds are negative
   }
   return seconds * 1000 + nanoseconds / 1000000; // Convert to milliseconds
}

