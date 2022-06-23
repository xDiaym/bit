#ifndef _VEC_H_
#define _VEC_H_
#include <stdint.h>

#define INITIAL_VECTOR_CAPACITY (16)


typedef struct _Vector Vector;

struct _Vector {
  void *data;
  uint64_t lenght;
};

Vector* vector_new(uint64_t element_size);
void vector_free(Vector *v);

uint64_t vector_extend(Vector *v, void *elems, uint64_t count);
uint64_t vector_append(Vector *v, void *elem);

#endif
