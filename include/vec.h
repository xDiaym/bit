#ifndef _VEC_H_
#define _VEC_H_

#include <stdlib.h>
#define INIT_VEC_SZ (256)

typedef struct {
  char* data;
  int cap;
  int size;
} vec;

void vec_new(vec* v);
void vec_del(vec* v);

void vec_push(vec* v, char* data, int len);
void vec_write_addr(vec* v, int addr, int offset);

#endif
