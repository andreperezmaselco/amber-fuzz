#ifndef COMMON_ARRAY_H
#define COMMON_ARRAY_H

// C library
#include <stddef.h>

typedef struct Array {
  size_t size;
  void *elements;
} Array;

#endif
