#ifndef CursorElement
#error Type parameter 'CursorElement' is not defined
#endif

#ifndef Cursor
#include <core/Core.h>

#define each(ElementType, element, CursorType, cursor)                                                                                       \
  for (                                                                                                                                      \
    struct {                                                                                                                                 \
      CursorType* inner;                                                                                                                     \
      Option(ElementType) next;                                                                                                              \
    } __cursor = {.inner = cursor};                                                                                                          \
    (__cursor.next = CONCAT(CursorType, Next)(__cursor.inner)).__tag != OptionNone || (CONCAT(CursorType, Destroy)(__cursor.inner), false);) \
    for (auto element = __cursor.next.OptionSome;; ({ break; }))

#define Cursor(CursorElement) GENERIC(Cursor, CursorElement)
#define CursorNext(CursorElement) CONCAT(Cursor(CursorElement), Next)
#define CursorDestroy(CursorElement) CONCAT(Cursor(CursorElement), Destroy)
#endif

#ifdef CursorElement
#define OptionValue CursorElement
#include <core/Option.h>

typedef struct Cursor(CursorElement) interface(
  Option(CursorElement) (*Next)(void* self);
) Cursor(CursorElement);

DISPATCH_DECL(Cursor(CursorElement), Option(CursorElement), Next, *);
DISPATCH_DECL(Cursor(CursorElement), Unit, Destroy, *);
IMPLEMENT_SIG(Cursor(CursorElement), Cursor(CursorElement));

#ifdef CURSOR_IMPLEMENTATION
COREAPI DISPATCH_IMPL(Cursor(CursorElement), Option(CursorElement), Next, *);
COREAPI DISPATCH_IMPL(Cursor(CursorElement), Unit, Destroy, *);

COREAPI IMPLEMENT(
  Cursor(CursorElement),
  Cursor(CursorElement),
  .Next    = (void*)CursorNext(CursorElement),
  .Destroy = (void*)CursorDestroy(CursorElement),
);
#endif // CURSOR_IMPLEMENTATION
#endif // CursorElement

#undef CursorElement
#undef CURSOR_IMPLEMENTATION
