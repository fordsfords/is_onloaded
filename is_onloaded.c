/* is_onloaded.c - function to test if the process is running under Onload. */
/*
# This code and its documentation is Copyright 2022-2023 Steven Ford
# and licensed "public domain" style under Creative Commons "CC0":
#   http://creativecommons.org/publicdomain/zero/1.0/
# To the extent possible under law, the contributors to this project have
# waived all copyright and related or neighboring rights to this work.
# In other words, you can use this code for any purpose without any
# restrictions.  This work is published from: United States.  The project home
# is https://github.com/fordsfords/is_onloaded
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_onloaded() {
  int onload_found = 0;
  char iline[1024];
  FILE *maps_fp = fopen("/proc/self/maps", "r");
  if (maps_fp == NULL) { fprintf(stderr, "fopen /proc/self/maps failed\n"); exit(1); }

  while (fgets(iline, sizeof(iline)-1, maps_fp) != NULL) {
    if (strstr(iline, "libonload.so") != NULL) {
      onload_found = 1;
      break;
    }
  }

  fclose(maps_fp);
  return onload_found;
}  /* is_onloaded */

int main(int argc, char **argv)
{
  if (is_onloaded()) {
    printf("YES Onload\n");
  } else {
    printf("NO Onload\n");
  }
}  /* main */
