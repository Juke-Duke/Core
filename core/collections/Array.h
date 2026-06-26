#ifndef ArrayElement
#error Type parameter 'ArrayElement' is not defined
#endif

#ifndef ArrayElementDefault
#define ArrayElementDefault() ((ArrayElement){})
#endif

#ifndef ArrayElementClone
#define ArrayElementClone(element) (*(element))
#endif

#ifndef ArrayElementDestroy
#define ArrayElementDestroy(element) ((void)(element))
#endif

#ifndef Array
#include <core/Core.h>

#define Array(ArrayElement) GENERIC(Array, ArrayElement)
#define ArrayDefault(ArrayElement) CONCAT(Array(ArrayElement), Default)
#define ArrayCreate(ArrayElement) CONCAT(Array(ArrayElement), Create)
#define ArrayCreateFill(ArrayElement) CONCAT(Array(ArrayElement), CreateFill)
#define ArrayCreateWithCapacity(ArrayElement) CONCAT(Array(ArrayElement), CreateWithCapacity)
#define ArrayCapacity(ArrayElement) CONCAT(Array(ArrayElement), Capacity)
#define ArrayResize(ArrayElement) CONCAT(Array(ArrayElement), Resize)
#define ArrayAt(ArrayElement) CONCAT(Array(ArrayElement), At)
#define ArrayAtMut(ArrayElement) CONCAT(Array(ArrayElement), AtMut)
#define ArrayClone(ArrayElement) CONCAT(Array(ArrayElement), Clone)
#define ArrayDestroy(ArrayElement) CONCAT(Array(ArrayElement), Destroy)

#define ArrayCursor(ArrayElement) GENERIC(ArrayCursor, ArrayElement)
#define ArrayCursorCreate(ArrayElement) CONCAT(ArrayCursor(ArrayElement), Create)
#define ArrayCursorNext(ArrayElement) CONCAT(ArrayCursor(ArrayElement), Next)
#define ArrayCursorClone(ArrayElement) CONCAT(ArrayCursor(ArrayElement), Clone)
#define ArrayCursorDestroy(ArrayElement) CONCAT(ArrayCursor(ArrayElement), Destroy)
#define ArrayCursorAsCursor(ArrayElement) CONCAT(ArrayCursor(ArrayElement), As, Cursor(Ref(ArrayElement)))
#endif

#ifdef ArrayElement
#define RefT ArrayElement
#include <core/Ref.h>

#define OptionValue Ref(ArrayElement)
#include <core/Option.h>

#define CursorElement Ref(ArrayElement)
#include <core/collections/cursors/Cursor.h>

typedef struct Array(ArrayElement) {
  ArrayElement* elements;
  UInt capacity;
} Array(ArrayElement);

Array(ArrayElement) ArrayDefault(ArrayElement)();
Array(ArrayElement) ArrayCreate(ArrayElement)(ArrayElement const elements[], UInt count);
Array(ArrayElement) ArrayCreateFill(ArrayElement)(ArrayElement value, UInt count);
Array(ArrayElement) ArrayCreateWithCapacity(ArrayElement)(UInt capacity);
UInt ArrayCapacity(ArrayElement)(Array(ArrayElement) const* array);
Unit ArrayResize(ArrayElement)(Array(ArrayElement) * array, UInt capacity);
ArrayElement const* ArrayAt(ArrayElement)(Array(ArrayElement) const* array, UInt index);
ArrayElement* ArrayAtMut(ArrayElement)(Array(ArrayElement) * array, UInt index);
Array(ArrayElement) ArrayClone(ArrayElement)(Array(ArrayElement) const* array);
Unit ArrayDestroy(ArrayElement)(Array(ArrayElement) * array);

typedef struct ArrayCursor(ArrayElement) {
  Array(ArrayElement) const* array;
  UInt index;
} ArrayCursor(ArrayElement);

ArrayCursor(ArrayElement) ArrayCursorCreate(ArrayElement)(Array(ArrayElement) const* array);
Option(Ref(ArrayElement)) ArrayCursorNext(ArrayElement)(ArrayCursor(ArrayElement) * cursor);
ArrayCursor(ArrayElement) ArrayCursorClone(ArrayElement)(ArrayCursor(ArrayElement) const* cursor);
Unit ArrayCursorDestroy(ArrayElement)(ArrayCursor(ArrayElement) * cursor);
IMPLEMENT_SIG(ArrayCursor(ArrayElement), Cursor(Ref(ArrayElement)));

#ifdef ARRAY_IMPLEMENTATION
#include <core/Debug.h>
#include <stdlib.h>

COREAPI Array(ArrayElement) ArrayDefault(ArrayElement)() {
  return (Array(ArrayElement)){
    .elements = null,
    .capacity = 0,
  };
}

COREAPI Array(ArrayElement) ArrayCreate(ArrayElement)(ArrayElement const elements[], UInt count) {
  if (count == 0) {
    return ArrayDefault(ArrayElement)();
  }

  auto array = (ArrayElement*)malloc(sizeof(ArrayElement) * count);
  if (array == null) {
    Error("Allocation failed.");
  }

  for (auto i = (UInt)0; i < count; ++i) {
    array[i] = elements[i];
  }

  return (Array(ArrayElement)){
    .elements = array,
    .capacity = count,
  };
}

COREAPI Array(ArrayElement) ArrayCreateFill(ArrayElement)(ArrayElement value, UInt count) {
  if (count == 0) {
    return ArrayDefault(ArrayElement)();
  }

  auto array = (ArrayElement*)malloc(sizeof(ArrayElement) * count);
  if (array == null) {
    Error("Allocation failed.");
  }

  for (auto i = (UInt)0; i < count - 1; ++i) {
    array[i] = ArrayElementClone(&value);
  }

  if (count > 0) {
    array[count - 1] = value;
  }

  return (Array(ArrayElement)){
    .elements = array,
    .capacity = count,
  };
}

COREAPI Array(ArrayElement) ArrayCreateWithCapacity(ArrayElement)(UInt capacity) {
  if (capacity == 0) {
    return ArrayDefault(ArrayElement)();
  }

  auto array = (ArrayElement*)malloc(sizeof(ArrayElement) * capacity);
  if (array == null) {
    Error("Allocation failed.");
  }

  for (auto i = (UInt)0; i < capacity; ++i) {
    array[i] = ArrayElementDefault();
  }

  return (Array(ArrayElement)){
    .elements = array,
    .capacity = capacity,
  };
}

COREAPI UInt ArrayCapacity(ArrayElement)(Array(ArrayElement) const* array) {
  return array->capacity;
}

COREAPI Unit ArrayResize(ArrayElement)(Array(ArrayElement) * array, UInt capacity) {
  if (capacity == 0) {
    ArrayDestroy(ArrayElement)(array);
    return_unit;
  }

  auto resized = (ArrayElement*)realloc(array->elements, sizeof(ArrayElement) * capacity);
  if (resized == null) {
    Error("Allocation failed.");
  }

  if (capacity < array->capacity) {
    for (auto i = capacity; i < array->capacity; ++i) {
      ArrayElementDestroy(&array->elements[i]);
    }
  }

  array->elements = resized;
  array->capacity = capacity;

  return_unit;
}

COREAPI ArrayElement const* ArrayAt(ArrayElement)(Array(ArrayElement) const* array, UInt index) {
#ifndef DISABLE_BOUNDS_CHECK
  if (index >= array->capacity) {
    Error("Index out of bounds.");
  }
#endif

  return &array->elements[index];
}

COREAPI ArrayElement* ArrayAtMut(ArrayElement)(Array(ArrayElement) * array, UInt index) {
#ifndef DISABLE_BOUNDS_CHECK
  if (index >= array->capacity) {
    Error("Index out of bounds.");
  }
#endif

  return &array->elements[index];
}

COREAPI Array(ArrayElement) ArrayClone(ArrayElement)(Array(ArrayElement) const* array) {
  auto clone = ArrayCreateWithCapacity(ArrayElement)(array->capacity);

  for (auto i = (UInt)0; i < array->capacity; ++i) {
    clone.elements[i] = ArrayElementClone(&array->elements[i]);
  }

  return clone;
}

COREAPI Unit ArrayDestroy(ArrayElement)(Array(ArrayElement) * array) {
  for (auto i = (UInt)0; i < array->capacity; ++i) {
    ArrayElementDestroy(&array->elements[i]);
  }

  free(array->elements);
  array->elements = null;
  array->capacity = 0;
  return_unit;
}

COREAPI ArrayCursor(ArrayElement) ArrayCursorCreate(ArrayElement)(Array(ArrayElement) const* array) {
  return (ArrayCursor(ArrayElement)){
    .array = array,
    .index = 0,
  };
}

COREAPI Option(Ref(ArrayElement)) ArrayCursorNext(ArrayElement)(ArrayCursor(ArrayElement) * cursor) {
  if (cursor->index >= ArrayCapacity(ArrayElement)(cursor->array)) {
    return OptionNone(Ref(ArrayElement))();
  }

  return OptionSome(Ref(ArrayElement))(ArrayAt(ArrayElement)(cursor->array, cursor->index++));
}

COREAPI ArrayCursor(ArrayElement) ArrayCursorClone(ArrayElement)(ArrayCursor(ArrayElement) const* cursor) {
  return (ArrayCursor(ArrayElement)){
    .array = cursor->array,
    .index = cursor->index,
  };
}

COREAPI Unit ArrayCursorDestroy(ArrayElement)(ArrayCursor(ArrayElement) * cursor) {
  cursor->index = 0;
  return_unit;
}

COREAPI IMPLEMENT(
  ArrayCursor(ArrayElement),
  Cursor(Ref(ArrayElement)),
  .Next    = (void*)ArrayCursorNext(ArrayElement),
  .Destroy = (void*)ArrayCursorDestroy(ArrayElement),
);
#endif // ARRAY_IMPLEMENTATION
#endif // ArrayElement

#undef ARRAY_IMPLEMENTATION
#undef ArrayElement
#undef ArrayElementDefault
#undef ArrayElementClone
#undef ArrayElementDestroy
#undef DISABLE_BOUNDS_CHECK
