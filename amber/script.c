// C library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Amber Fuzz library
#include "amber/script.h"
#include "amber/shader.h"
#include "common/array.h"

void fuzzAmberScript(AmberScript *script) {
  if (script == NULL || script->file.path == NULL) {
    return;
  }

  // Get a stream for the input script file.
  script->file.stream = fopen(script->file.path, "r");
  if (script->file.stream == NULL) {
    return;
  }

  // A temporary file to write the output script.
  File temporaryFile;
  temporaryFile.stream = tmpfile();

  // Read the Amber script, fuzz its shaders
  // and write the fuzzed shaders to the temporary file.
  Array line = {0, NULL};
  while (getline((char **)&line.elements, &line.size, script->file.stream) != -1) {
    fputs((char *)line.elements, temporaryFile.stream);

    // The first token of the line must be SHADER.
    char *token = strtok((char *)line.elements, " ");
    if (strcmp(token, "SHADER") != 0) {
      continue;
    }

    // Get shader information.
    AmberShader shader;
    shader.type = strdup(strtok(NULL, " "));
    shader.name = strdup(strtok(NULL, " "));
    shader.format = strdup(strtok(NULL, " \n"));

    // The shader format must be SPIRV-ASM.
    if (strcmp(shader.format, "SPIRV-ASM") != 0) {
      continue;
    }

    // Set the shader file path.
    shader.file.path = malloc(strlen(shader.name) + strlen(".spv.asm") + 1);
    sprintf(shader.file.path, "%s.spv.asm", shader.name);

    // Writes the shader to a file.
    shader.file.stream = fopen(shader.file.path, "w");
    while (getline((char **)&line.elements, &line.size, script->file.stream) != -1 &&
           strcmp("END\n", line.elements) != 0) {
      fputs((char *)line.elements, shader.file.stream);
    }
    fclose(shader.file.stream);

    // Assemble, fuzz and disassemble the shader.
    assembleAmberShader(&shader);
    fuzzAmberShader(&shader);
    disassembleAmberShader(&shader);

    // Write the fuzzed shader to the temporary file.
    shader.file.stream = fopen(shader.file.path, "r");
    while (getline((char **)&line.elements, &line.size, shader.file.stream) != -1) {
      fputs((char *)line.elements, temporaryFile.stream);
    }
    fputs("END\n", temporaryFile.stream);
    fclose(shader.file.stream);
    free(shader.file.path);
    free(shader.type);
    free(shader.name);
    free(shader.format);
  }
  fclose(script->file.stream);

  // Copy the temporary file content to the output file.
  File fuzzedAmberScriptFile;
  fuzzedAmberScriptFile.stream = fopen("fuzzed.amber", "w");
  rewind(temporaryFile.stream);
  while (getline((char **)&line.elements, &line.size, temporaryFile.stream) != -1) {
    fputs((char *)line.elements, fuzzedAmberScriptFile.stream);
  }
  fclose(fuzzedAmberScriptFile.stream);
  fclose(temporaryFile.stream);
  free(line.elements);
}

