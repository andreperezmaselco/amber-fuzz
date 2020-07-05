#ifndef AMBER_SCRIPT_H
#define AMBER_SCRIPT_H

// Amber Fuzz library
#include "common/array.h"
#include "io/file.h"

typedef struct AmberScript {
  File file;
  Array shaders;
} AmberScript;

void fuzzAmberScript(AmberScript *script);

#endif
