#ifndef CursorElement
#error Type parameter 'CursorElement' is not defined.
#endif

#include <core/Core.h>
#include <core/Generic.h>
#include <core/Interface.h>

#ifndef DISABLE_Option_CursorElement
#define OptionValue CursorElement
#include <core/Option.h>
#endif
#undef DISABLE_Option_CursorElement

#ifndef Cursor
#define Cursor(CursorElement) GENERIC(Cursor, CursorElement)
#define CursorNext(CursorElement) GENERIC(CursorNext, CursorElement)
#endif

typedef interface(Cursor(CursorElement),
  Option(CursorElement) (*Next)(void*);
);

static Option(CursorElement) CursorNext(CursorElement)(Cursor(CursorElement)* cursor) {
  return cursor->interface->Next(cursor->self);
}

#undef CursorElement
