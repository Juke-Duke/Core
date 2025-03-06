#ifndef CursorElement
#error Type parameter 'CursorElement' is not defined.
#endif

#include <core/Core.h>
#include <core/Generic.h>

#ifndef DISABLE_Option_CursorElement
#define OptionValue CursorElement
#include <core/Option.h>
#endif
#undef DISABLE_Option_CursorElement

#ifndef Cursor
#define Cursor(CursorElement) GENERIC(Cursor, CursorElement)
#define CursorNext(CursorElement) GENERIC(CursorNext, CursorElement)
#endif

typedef struct {
  void* self;
  struct {
    Option(CursorElement) (*Next)(void*);
  }* interface;
} Cursor(CursorElement);

static inline Option(CursorElement) CursorNext(CursorElement)(Cursor(CursorElement) cursor) {
  return cursor.interface->Next(cursor.self);
}

#undef CursorElement
