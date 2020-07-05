// C library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Amber Fuzz library
#include "amber/shader.h"

void assembleAmberShader(AmberShader *shader) {
  char *template = "spirv-as %s -o %s.spv --preserve-numeric-ids --target-env spv1.0";
  char *command = malloc(strlen(template) + strlen(shader->file.path) + strlen(shader->name) - 3);
  sprintf(command, template, shader->file.path, shader->name);
  system(command);
  free(command);
}

void fuzzAmberShader(AmberShader *shader) {
  system("touch donors.txt");
  char *template = "spirv-fuzz %s.spv -o %s.spv --donors=donors.txt";
  char *command = malloc(strlen(template) + 2 * strlen(shader->name) - 3);
  sprintf(command, template, shader->name, shader->name);
  system(command);
  free(command);
}

void disassembleAmberShader(AmberShader *shader) {
  char *template = "spirv-dis %s.spv -o %s --raw-id";
  char *command = malloc(strlen(template) + strlen(shader->name) + strlen(shader->file.path) - 3);
  sprintf(command, template, shader->name, shader->file.path);
  system(command);
  free(command);
}

