#include <string.h>
#include <vec.h>

void vec_new(vec* v) {
  v->data = malloc(INIT_VEC_SZ);
  v->cap = INIT_VEC_SZ;
  v->size = 0;
}

void vec_del(vec* v) { free(v->data); }

void vec_push(vec* v, char* data, int len) {
  if (v->size + len >= v->cap) {
    v->cap *= 2;
    v->data = realloc(v->data, v->cap);
  }
  memcpy(v->data + v->size, data, len);
  v->size += len;
}
void vec_write_addr(vec* v, int addr, int offset) {
  *(int*)(v->data + addr) = offset;
}
