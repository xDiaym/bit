#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <vec.h>
#include <compiler.h>

void fail(const char* messsage) {
  fprintf(stderr, "%s", messsage);
  exit(-1);
}

char* read_file(const char *fname) {
  FILE* fp = fopen(fname, "r");
  if (fp == NULL) fail("Failed to read file");
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);
  char* text = malloc(size);
  fread(text, 1, size, fp);
  fclose(fp);
  return text;
}

void run(char* text) {
  Vector *v = vector_new(sizeof(char));
  compile(text, v);
  char tape[30000] = {0};

  void(*fn)(char*, int(*)(), int(*)(int)) = mmap(NULL, v->lenght, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
  memcpy(fn, v->data, v->lenght);
  vector_free(v);

  fn(tape, getchar, putchar);
  munmap(fn, v->lenght);
}

int main(int c, char **argv) {
  if (c < 2) fail("Usage:\nbit <file>");
  char* text = read_file(argv[1]);
  run(text);
  free(text);
  return 0;
}
