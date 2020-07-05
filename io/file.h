#ifndef IO_FILE_H
#define IO_FILE_H

// C library
#include <stdio.h>

// Amber Fuzz library
#include "common/array.h"

typedef struct File {
  char *path;
  FILE *stream;
  Array bytes;
} File;

#endif
