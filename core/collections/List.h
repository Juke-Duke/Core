#ifndef ListElement
#error Type parameter 'ListElement' is not defined
#endif

#ifndef ListElementDefault
#define ListElementDefault() ((ListElement){})
#endif

#ifndef ListElementClone
#define ListElementClone(element) (*(element))
#endif

#ifndef ListElementDestroy
#define ListElementDestroy(element) ((void)(element))
#endif

#ifndef List
#include <core/Core.h>

#define List(ListElement) GENERIC(List, ListElement)
#define ListDefault(ListElement) CONCAT(List(ListElement), Default)
#define ListCreate(ListElement) CONCAT(List(ListElement), Create)
#define ListCreateFill(ListElement) CONCAT(List(ListElement), CreateFill)
#define ListCreateWithCapacity(ListElement) CONCAT(List(ListElement), CreateWithCapacity)
#define ListCount(ListElement) CONCAT(List(ListElement), Count)
#define ListCapacity(ListElement) CONCAT(List(ListElement), Capacity)
#define ListAt(ListElement) CONCAT(List(ListElement), At)
#define ListAtMut(ListElement) CONCAT(List(ListElement), AtMut)
#define ListAppend(ListElement) CONCAT(List(ListElement), Append)
#define ListClone(ListElement) CONCAT(List(ListElement), Clone)
#define ListDestroy(ListElement) CONCAT(List(ListElement), Destroy)

#define ListCursor(ListElement) GENERIC(ListCursor, ListElement)
#define ListCursorCreate(ListElement) CONCAT(ListCursor(ListElement), Create)
#define ListCursorNext(ListElement) CONCAT(ListCursor(ListElement), Next)
#define ListCursorClone(ListElement) CONCAT(ListCursor(ListElement), Clone)
#define ListCursorDestroy(ListElement) CONCAT(ListCursor(ListElement), Destroy)
#define ListCursorAsCursor(ListElement) CONCAT(ListCursor(ListElement), As, Cursor(Ref(ListElement)))
#endif

#ifdef ListElement
#define RefT ListElement
#include <core/Ref.h>

#define OptionValue Ref(ListElement)
#include <core/Option.h>

#define CursorElement Ref(ListElement)
#include <core/collections/cursors/Cursor.h>

#define ArrayElement ListElement
#include <core/collections/Array.h>

typedef struct List(ListElement) {
  Array(ListElement) elements;
  UInt count;
} List(ListElement);

List(ListElement) ListDefault(ListElement)();
List(ListElement) ListCreate(ListElement)(ListElement const elements[], UInt count);
List(ListElement) ListCreateFill(ListElement)(ListElement value, UInt count);
List(ListElement) ListCreateWithCapacity(ListElement)(UInt capacity);
UInt ListCount(ListElement)(List(ListElement) const* list);
UInt ListCapacity(ListElement)(List(ListElement) const* list);
ListElement const* ListAt(ListElement)(List(ListElement) const* list, UInt index);
ListElement* ListAtMut(ListElement)(List(ListElement) * list, UInt index);
Unit ListAppend(ListElement)(List(ListElement) * list, ListElement value);
List(ListElement) ListClone(ListElement)(List(ListElement) const* list);
Unit ListDestroy(ListElement)(List(ListElement) * list);

typedef struct ListCursor(ListElement) {
  List(ListElement) const* list;
  UInt index;
} ListCursor(ListElement);

ListCursor(ListElement) ListCursorCreate(ListElement)(List(ListElement) const* list);
Option(Ref(ListElement)) ListCursorNext(ListElement)(ListCursor(ListElement) * cursor);
ListCursor(ListElement) ListCursorClone(ListElement)(ListCursor(ListElement) const* cursor);
Unit ListCursorDestroy(ListElement)(ListCursor(ListElement) * cursor);
IMPLEMENT_SIG(ListCursor(ListElement), Cursor(Ref(ListElement)));

#ifdef LIST_IMPLEMENTATION
#include <core/Debug.h>

COREAPI List(ListElement) ListDefault(ListElement)() {
  return (List(ListElement)){
    .elements = ArrayDefault(ListElement)(),
    .count    = 0,
  };
}

COREAPI List(ListElement) ListCreate(ListElement)(ListElement const elements[], UInt count) {
  return (List(ListElement)){
    .elements = ArrayCreate(ListElement)(elements, count),
    .count    = count,
  };
}

COREAPI List(ListElement) ListCreateFill(ListElement)(ListElement value, UInt count) {
  return (List(ListElement)){
    .elements = ArrayCreateFill(ListElement)(value, count),
    .count    = count,
  };
}

COREAPI List(ListElement) ListCreateWithCapacity(ListElement)(UInt capacity) {
  return (List(ListElement)){
    .elements = ArrayCreateWithCapacity(ListElement)(capacity),
    .count    = 0,
  };
}

COREAPI UInt ListCount(ListElement)(List(ListElement) const* list) {
  return list->count;
}

COREAPI UInt ListCapacity(ListElement)(List(ListElement) const* list) {
  return ArrayCapacity(ListElement)(&list->elements);
}

COREAPI ListElement const* ListAt(ListElement)(List(ListElement) const* list, UInt index) {
#ifndef DISABLE_BOUNDS_CHECK
  if (index >= list->count) {
    Error("Index out of bounds.");
  }
#endif

  return ArrayAt(ListElement)(&list->elements, index);
}

COREAPI ListElement* ListAtMut(ListElement)(List(ListElement) * list, UInt index) {
#ifndef DISABLE_BOUNDS_CHECK
  if (index >= list->count) {
    Error("Index out of bounds.");
  }
#endif

  return ArrayAtMut(ListElement)(&list->elements, index);
}

COREAPI Unit ListAppend(ListElement)(List(ListElement) * list, ListElement value) {
  if (list->count == ArrayCapacity(ListElement)(&list->elements)) {
    ArrayResize(ListElement)(&list->elements, ArrayCapacity(ListElement)(&list->elements) * 2 + 8);
  }

  *ArrayAtMut(ListElement)(&list->elements, list->count) = value;
  ++list->count;
  return_unit;
}

COREAPI List(ListElement) ListClone(ListElement)(List(ListElement) const* list) {
  return (List(ListElement)){
    .elements = ArrayClone(ListElement)(&list->elements),
    .count    = list->count,
  };
}

COREAPI Unit ListDestroy(ListElement)(List(ListElement) * list) {
  ArrayDestroy(ListElement)(&list->elements);
  list->count = 0;
  return_unit;
}

COREAPI ListCursor(ListElement) ListCursorCreate(ListElement)(List(ListElement) const* list) {
  return (ListCursor(ListElement)){
    .list  = list,
    .index = 0,
  };
}

COREAPI Option(Ref(ListElement)) ListCursorNext(ListElement)(ListCursor(ListElement) * cursor) {
  if (cursor->index >= ListCount(ListElement)(cursor->list)) {
    return OptionNone(Ref(ListElement))();
  }

  return OptionSome(Ref(ListElement))(ListAt(ListElement)(cursor->list, cursor->index++));
}

COREAPI ListCursor(ListElement) ListCursorClone(ListElement)(ListCursor(ListElement) const* cursor) {
  return (ListCursor(ListElement)){
    .list  = cursor->list,
    .index = cursor->index,
  };
}

COREAPI Unit ListCursorDestroy(ListElement)(ListCursor(ListElement) * cursor) {
  cursor->index = 0;
  return_unit;
}

COREAPI IMPLEMENT(
  ListCursor(ListElement),
  Cursor(Ref(ListElement)),
  .Next    = (void*)ListCursorNext(ListElement),
  .Destroy = (void*)ListCursorDestroy(ListElement),
);
#endif // LIST_IMPLEMENTATION
#endif // ListElement

#undef LIST_IMPLEMENTATION
#undef ListElement
#undef ListElementDefault
#undef ListElementClone
#undef ListElementDestroy
#undef DISABLE_BOUNDS_CHECK
