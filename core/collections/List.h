#ifndef ListElement
#error Type parameter 'ListElement' is not defined.
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
#endif

#ifdef ListElement
#if defined LIST_IMPLEMENTATION && !defined DISABLE_ARRAY_ListElement_IMPLEMENTATION
#define ARRAY_IMPLEMENTATION
#define DISABLE_OPTION_REF_ArrayElement_IMPLEMENTATION
#define DISABLE_CURSOR_ArrayElement_IMPLEMENTATION
#endif
#define ArrayElement ListElement
#define ArrayElementDefault ListElementDefault
#define ArrayElementClone ListElementClone
#define ArrayElementDestroy ListElementDestroy
#include <core/collections/Array.h>

#define RefT ListElement
#include <core/Ref.h>

#if defined LIST_IMPLEMENTATION && !defined DISABLE_OPTION_REF_ListElement_IMPLEMENTATION
#define OPTION_IMPLEMENTATION
#endif
#define OptionValue Ref(ListElement)
#include <core/Option.h>

#if defined LIST_IMPLEMENTATION && !defined DISABLE_CURSOR_ListElement_IMPLEMENTATION
#define CURSOR_IMPLEMENTATION
#define DISABLE_OPTION_REF_CursorElement_IMPLEMENTATION
#endif
#define CursorElement ListElement
#include <core/collections/Cursor.h>

typedef struct List(ListElement) {
  Array(ListElement) elements;
  UInt count;
} List(ListElement);

List(ListElement) ListDefault(ListElement)();
List(ListElement) ListCreate(ListElement)(ListElement const* elements, UInt count);
List(ListElement) ListCreateFill(ListElement)(ListElement value, UInt count);
List(ListElement) ListCreateWithCapacity(ListElement)(UInt capacity);
UInt ListCount(ListElement)(List(ListElement) const* list);
UInt ListCapacity(ListElement)(List(ListElement) const* list);
ListElement const* ListAt(ListElement)(List(ListElement) const* list, UInt index);
ListElement* ListAtMut(ListElement)(List(ListElement) * list, UInt index);
void ListAppend(ListElement)(List(ListElement) * list, ListElement value);
List(ListElement) ListClone(ListElement)(List(ListElement) const* list);
void ListDestroy(ListElement)(List(ListElement) * list);

typedef struct ListCursor(ListElement) {
  List(ListElement) const* list;
  UInt index;
} ListCursor(ListElement);

ListCursor(ListElement) ListCursorCreate(ListElement)(List(ListElement) const* list);
Option(Ref(ListElement)) ListCursorNext(ListElement)(ListCursor(ListElement) * cursor);
ListCursor(ListElement) ListCursorClone(ListElement)(ListCursor(ListElement) const* cursor);
void ListCursorDestroy(ListElement)(ListCursor(ListElement) * cursor);

#ifdef LIST_IMPLEMENTATION
#include <core/Debug.h>

List(ListElement) ListDefault(ListElement)() {
  return (List(ListElement)){
    .elements = ArrayDefault(ListElement)(),
    .count    = 0,
  };
}

List(ListElement) ListCreate(ListElement)(ListElement const elements[], UInt count) {
  return (List(ListElement)){
    .elements = ArrayCreate(ListElement)(elements, count),
    .count    = count,
  };
}

List(ListElement) ListCreateFill(ListElement)(ListElement value, UInt count) {
  return (List(ListElement)){
    .elements = ArrayCreateFill(ListElement)(value, count),
    .count    = count,
  };
}

List(ListElement) ListCreateWithCapacity(ListElement)(UInt capacity) {
  return (List(ListElement)){
    .elements = ArrayCreateWithCapacity(ListElement)(capacity),
    .count    = 0,
  };
}

UInt ListCount(ListElement)(List(ListElement) const* list) {
  return list->count;
}

UInt ListCapacity(ListElement)(List(ListElement) const* list) {
  return ArrayCapacity(ListElement)(&list->elements);
}

ListElement const* ListAt(ListElement)(List(ListElement) const* list, UInt index) {
#ifndef DISABLE_BOUNDS_CHECK
  if (index >= list->count) {
    Error("Index out of bounds.");
  }
#endif

  return ArrayAt(ListElement)(&list->elements, index);
}

ListElement* ListAtMut(ListElement)(List(ListElement) * list, UInt index) {
#ifndef DISABLE_BOUNDS_CHECK
  if (index >= list->count) {
    Error("Index out of bounds.");
  }
#endif

  return ArrayAtMut(ListElement)(&list->elements, index);
}

void ListAppend(ListElement)(List(ListElement) * list, ListElement value) {
  if (list->count == ArrayCapacity(ListElement)(&list->elements)) {
    ArrayResize(ListElement)(&list->elements, ArrayCapacity(ListElement)(&list->elements) * 2 + 8);
  }

  *ArrayAtMut(ListElement)(list, list->count) = value;
  ++list->count;
}

List(ListElement) ListClone(ListElement)(List(ListElement) const* list) {
  return (List(ListElement)){
    .elements = ArrayClone(ListElement)(&list->elements),
    .count    = list->count,
  };
}

void ListDestroy(ListElement)(List(ListElement) * list) {
  ArrayDestroy(ListElement)(&list->elements);
  list->count = 0;
}

ListCursor(ListElement) ListCursorCreate(ListElement)(List(ListElement) const* list) {
  return (ListCursor(ListElement)){
    .list  = list,
    .index = 0,
  };
}

Option(Ref(ListElement)) ListCursorNext(ListElement)(ListCursor(ListElement) * cursor) {
  if (cursor->index >= ListCount(ListElement)(cursor->list)) {
    return OptionNone(Ref(ListElement))();
  }

  return OptionSome(Ref(ListElement))(ListAt(ListElement)(cursor->list, cursor->index++));
}

ListCursor(ListElement) ListCursorClone(ListElement)(ListCursor(ListElement) const* cursor) {
  return (ListCursor(ListElement)){
    .list  = cursor->list,
    .index = cursor->index,
  };
}

void ListCursorDestroy(ListElement)(ListCursor(ListElement) * cursor) {
  cursor->index = 0;
}

implement(
  ListCursor(ListElement),
  Cursor(ListElement),
  .Next = (void*)ListCursorNext(ListElement),
);
#endif // LIST_IMPLEMENTATION
#endif // ListElement

#undef ListElement
#undef ListElementClone
#undef ListElementDestroy
#undef LIST_IMPLEMENTATION
#undef DISABLE_BOUNDS_CHECK
