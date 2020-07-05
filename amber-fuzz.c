// Amber Fuzz library
#include "amber/script.h"

int main(int argc, char **argv) {
  AmberScript script = {{argv[1]}};
  fuzzAmberScript(&script);
  return 0;
}
