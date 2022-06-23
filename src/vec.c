#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vec.h>

typedef struct _VectorImpl VectorImpl;

struct _VectorImpl {
  void* data;
  uint64_t length;
  uint64_t capacity;
  uint64_t item_size;
};


Vector* vector_new(uint64_t item_size) {
  VectorImpl *v = malloc(sizeof(VectorImpl));
  v->capacity = INITIAL_VECTOR_CAPACITY * item_size;
  v->data = malloc(v->capacity);
  v->item_size = item_size;
  v->length = 0;
  return (Vector*)v;
}

void vector_free(Vector *v) {
  free(v->data);
  free(v);
}

static void vector_extend_if_needed(VectorImpl *v, uint64_t count) {
  uint64_t new_capacity = v->capacity;
  while (v->length + count * v->item_size > new_capacity)
    new_capacity *= 2;
  if (new_capacity != v->capacity) {
    v->capacity = new_capacity;
    v->data = realloc(v->data, v->capacity);
  }
}

uint64_t vector_extend(Vector *u, void *elems, uint64_t count) {
  VectorImpl *v = (VectorImpl*)u;
  vector_extend_if_needed(v, count);
  memcpy(v->data + v->length * v->item_size, elems, v->item_size * count);
  v->length += count;
  return count;
}

uint64_t vector_append(Vector *v, void *elem) {
  return vector_extend(v, elem, 1);
}
