#ifndef CursorElement
#error Type parameter 'CursorElement' is not defined.
#endif

#ifndef DISABLE_Option_CursorElement
#define OptionValue CursorElement
#include <core/Option.h>
#endif
#undef DISABLE_Option_CursorElement

#ifndef Cursor
#include <core/Generic.h>
#define Cursor(CursorElement) GENERIC(Cursor, CursorElement)
#define CursorNext(CursorElement) GENERIC(CursorNext, CursorElement)
#endif

#include <core/Interface.h>

typedef interface(Cursor(CursorElement),
  Option(CursorElement) (*Next)(void*);
);

static Option(CursorElement) CursorNext(CursorElement)(Cursor(CursorElement) * cursor) {
  return cursor->vTable->Next(cursor->self);
}

#define foreach(CursorElement, element, SequenceType, cursor)          \
  for (auto element = SequenceType##CursorNext(CursorElement)(cursor); \
       element.tag != Option_None;                                     \
       element = SequenceType##CursorNext(CursorElement)(cursor))

#undef CursorElement
