#ifndef ListElement
#error Type parameter 'ListElement' is not defined.
#endif

#include <core/Core.h>
#include <core/Generic.h>
#include <stdlib.h>

#ifndef DISABLE_Array_ListElement
#define ArrayElement ListElement
#include <core/collections/Array.h>
#endif
#undef DISABLE_Array_ListElement

#ifndef DISABLE_Cursor_ListElement
#define CursorElement ListElement
#include <core/collections/Cursor.h>
#endif
#undef DISABLE_Cursor_ListElement

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
#define ListCursor_as_Cursor(ListElement) GENERIC(ListCursor_as_Cursor, ListElement)
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
    ArrayResize(ListElement)(&list->elements, list->elements.capacity);
  }

  ArraySetAt(ListElement)(&list->elements, list->count, value);
  ++list->count;
}

static void ListDestroy(ListElement)(List(ListElement) list) {
  ArrayDestroy(ListElement)(list.elements);
  list.count = 0;
}

typedef struct {
  List(ListElement) * list;
  UInt index;
} ListCursor(ListElement);

static ListCursor(ListElement) ListCursorCreate(ListElement)(List(ListElement) * list) {
  return (ListCursor(ListElement)){
    .list = list,
    .index = 0,
  };
}

static Option(ListElement) ListCursorNext(ListElement)(ListCursor(ListElement) * listCursor) {
  if (listCursor->index < ListCount(ListElement)(listCursor->list)) {
    return OptionSome(ListElement)(ListAt(ListElement)(listCursor->list, listCursor->index++));
  }

  return OptionNone(ListElement)();
}

static Cursor(ListElement) ListCursor_as_Cursor(ListElement)(ListCursor(ListElement) * listCursor) {
  static typeof(*(Cursor(ListElement)){}.interface) interface = {
    .Next = (void*)ListCursorNext(ListElement),
  };

  return (Cursor(ListElement)){
    .self = listCursor,
    .interface = &interface,
  };
}

#undef ListElement
