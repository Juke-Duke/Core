#ifndef ArrayElement
#error Type parameter 'ArrayElement' is not defined.
#endif

#include <core/Core.h>
#include <core/Generic.h>
#include <stdlib.h>
#include <string.h>

#ifndef Array
#define Array(ArrayElement) GENERIC(Array, ArrayElement)
#define ArrayDefault(ArrayElement) GENERIC(ArrayDefault, ArrayElement)
#define ArrayCreate(ArrayElement) GENERIC(ArrayCreate, ArrayElement)
#define ArrayCreateWithCapacity(ArrayElement) GENERIC(ArrayCreateWithCapacity, ArrayElement)
#define ArrayCapacity(ArrayElement) GENERIC(ArrayCapacity, ArrayElement)
#define ArrayResize(ArrayElement) GENERIC(ArrayResize, ArrayElement)
#define ArrayAt(ArrayElement) GENERIC(ArrayAt, ArrayElement)
#define ArraySetAt(ArrayElement) GENERIC(ArraySetAt, ArrayElement)
#define ArrayDestroy(ArrayElement) GENERIC(ArrayDestroy, ArrayElement)
#endif

typedef struct {
  ArrayElement* elements;
  UInt capacity;
} Array(ArrayElement);

static Array(ArrayElement) ArrayDefault(ArrayElement)() {
  return (Array(ArrayElement)){
    .elements = null,
    .capacity = 0,
  };
}

static Array(ArrayElement) ArrayCreate(ArrayElement)(ArrayElement* elements, UInt count) {
  return (Array(ArrayElement)){
    .elements = (ArrayElement*)memcpy(malloc(sizeof(ArrayElement) * count), elements, sizeof(ArrayElement) * count),
    .capacity = count,
  };
}

static Array(ArrayElement) ArrayCreateWithCapacity(ArrayElement)(UInt capacity) {
  return (Array(ArrayElement)){
    .elements = (ArrayElement*)calloc(capacity, sizeof(ArrayElement)),
    .capacity = capacity,
  };
}

static UInt ArrayCapacity(ArrayElement)(Array(ArrayElement) const* array) {
  return array->capacity;
}

static void ArrayResize(ArrayElement)(Array(ArrayElement) * array, UInt capacity) {
  array->elements = (ArrayElement*)realloc(array->elements, sizeof(ArrayElement) * capacity);
  array->capacity = capacity;
}

static ArrayElement ArrayAt(ArrayElement)(Array(ArrayElement) const* array, UInt index) {
  return array->elements[index];
}

static void ArraySetAt(ArrayElement)(Array(ArrayElement) * array, UInt index, ArrayElement value) {
  array->elements[index] = value;
}

static void ArrayDestroy(ArrayElement)(Array(ArrayElement) array) {
  free(array.elements);
  array.elements = null;
  array.capacity = 0;
}

#undef ArrayElement
