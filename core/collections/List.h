#ifndef ListElement
#error "Type parameter 'ListElement' is not defined."
#endif

#include <core/Core.h>
#include <core/Generic.h>
#include <stdlib.h>

#ifndef DISABLE_Array_ListElement
#define ArrayElement ListElement
#include <core/collections/Array.h>
#endif

#ifndef List
#define List(ListElement) GENERIC(List, ListElement)
#define ListDefault(ListElement) GENERIC(ListDefault, ListElement)
#define ListCreate(ListElement) GENERIC(ListCreate, ListElement)
#define ListCount(ListElement) GENERIC(ListCount, ListElement)
#define ListCapacity(ListElement) GENERIC(ListCapacity, ListElement)
#define ListAt(ListElement) GENERIC(ListAt, ListElement)
#define ListSetAt(ListElement) GENERIC(ListSetAt, ListElement)
#define ListAppend(ListElement) GENERIC(ListAppend, ListElement)
#define ListDestroy(ListElement) GENERIC(ListDestroy, ListElement)

#define ListCursor(ListElement) GENERIC(ListCursor, ListElement)
#define ListCursorCreate(ListElement) GENERIC(ListCursorCreate, ListElement)
#define ListCursorNext(ListElement) GENERIC(ListCursorNext, ListElement)
#define ListCursorAsCursor(ListElement) GENERIC(ListCursorAsCursor, ListElement)
#endif

typedef struct {
  Array(ListElement) elements;
  UInt count;
} List(ListElement);

static List(ListElement) ListDefault(ListElement)() {
  return (List(ListElement)){
    .elements = ArrayDefault(ListElement)(),
    .count = 0,
  };
}

static List(ListElement) ListCreate(ListElement)(UInt capacity) {
  return (List(ListElement)){
    .elements = ArrayCreateWithCapacity(ListElement)(capacity),
    .count = 0,
  };
}

static UInt ListCount(ListElement)(List(ListElement) const* list) {
  return list->count;
}

static UInt ListCapacity(ListElement)(List(ListElement) const* list) {
  return ArrayCapacity(ListElement)(&list->elements);
}

static ListElement ListAt(ListElement)(List(ListElement) const* list, UInt index) {
  return ArrayAt(ListElement)(&list->elements, index);
}

static void ListSetAt(ListElement)(List(ListElement) * list, UInt index, ListElement value) {
  ArraySetAt(ListElement)(&list->elements, index, value);
}

static void ListAppend(ListElement)(List(ListElement) * list, ListElement value) {
  if (list->count == list->elements.capacity) {
    list->elements.capacity = list->elements.capacity * 2 + 8;

    Array(ListElement) newElements = ArrayCreateWithCapacity(ListElement)(list->elements.capacity);

    for (UInt i = 0; i < list->count; i++) {
      ArraySetAt(ListElement)(&newElements, i, ArrayAt(ListElement)(&list->elements, i));
    }

    ArrayDestroy(ListElement)(list->elements);

    list->elements = newElements;
  }

  ArraySetAt(ListElement)(&list->elements, list->count, value);
  list->count++;
}

static void ListDestroy(ListElement)(List(ListElement) list) {
  ArrayDestroy(ListElement)(list.elements);
  list.count = 0;
}

#undef ListElement

#undef DISABLE_Array_ListElement
