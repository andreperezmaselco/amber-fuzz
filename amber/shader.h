#ifndef AMBER_SHADER_H
#define AMBER_SHADER_H

// Amber Fuzz library
#include "io/file.h"

typedef struct AmberShader {
  char *type;
  char *name;
  char *format;
  File file;
} AmberShader;

void assembleAmberShader(AmberShader *shader);

void fuzzAmberShader(AmberShader *shader);

void disassembleAmberShader(AmberShader *shader);

#endif
