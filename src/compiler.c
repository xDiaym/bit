#include <compiler.h>

#define STACK_INIT_SZ (256)
typedef struct {
  int size;
  int data[STACK_INIT_SZ];
} stack;

void stack_push(stack* s, int v) { s->data[s->size++] = v; }
int stack_pop(stack* s) { return s->data[--s->size]; }

void vector_write_addr(Vector *v, uint64_t addr, uint64_t offset) {
  *(int*)(v->data + addr) = offset;
}

/**
 * RDA - RETURN
 * r12 - tape
 * r13 - getchar
 * r14 - putchar
 */
void compile(char *code, Vector* v) {
  stack s = {0, {0}};
  char p[] = {
    0x55,
    0x48, 0x89, 0xe5,

    0x57, 0x56, 0x52,

    0x49, 0x89, 0xfc,
    0x49, 0x89, 0xf5,
    0x49, 0x89, 0xd6,
  };
  vector_extend(v, p, 16);
  for (int i = 0; code[i] != '\0'; i++) {
    switch (code[i]) {
    case '>': {
        char p[] = {0x49, 0xff, 0xc4};
        vector_extend(v, p, 3);
        break;
      }
    case '<': {
        char p[] = {0x49, 0xff, 0xcc};
        vector_extend(v, p, 3);
        break;
      }
    case '+': {
        char p[] = {0x41, 0xfe, 0x04, 0x24};
        vector_extend(v, p, 4);
        break;
      }
    case '-': {
        char p[] = {0x41, 0xfe, 0x0c, 0x24};
        vector_extend(v, p, 4);
        break;
    }
    case '.': {
      char p[] = {0x41, 0x0f, 0xb6, 0x3c, 0x24, 0x41, 0xff, 0xd6};
      vector_extend(v, p, 8);
      break;
    }
    case ',': {
      char p[] = {0x41, 0xff, 0xd5, 0x41, 0x88, 0x04, 0x24};
      vector_extend(v, p, 7);
      break;
    }
    case '[': {
      char p[] = {
        0x41, 0x80, 0x3c, 0x24, 0x00,
        0x0f, 0x84, 0x00, 0x00, 0x00, 0x00
      };
      vector_extend(v, p, 11);
      stack_push(&s, v->lenght);
      break;
    }
    case ']': {
      char p[] = {
        0x41, 0x80, 0x3c, 0x24, 0x00,
        0x0f, 0x85, 0x00, 0x00, 0x00, 0x00
      };
      vector_extend(v, p, 11);
      int open = stack_pop(&s);
      int off = v->lenght - open;
      vector_write_addr(v, open - 4, off);
      vector_write_addr(v, v->lenght - 4, -off);
    }
    }
  }
  char f[] = {0x41, 0x5e, 0x41, 0x5d, 0x41, 0x5c, 0x5d, 0xc3};
  vector_extend(v, f, 8);
}
