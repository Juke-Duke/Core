#ifndef CursorElement
#error Type parameter 'CursorElement' is not defined.
#endif

#ifndef Cursor
#include <core/Core.h>

#define each(element, Cursor, sequence) (auto __each_flag = true; __each_flag;) for (auto cursor = CONCAT(Cursor, Create)(sequence); __each_flag; (CONCAT(Cursor, Destroy)(&cursor), __each_flag = false)) for (auto element = CONCAT(Cursor, Next)(&cursor); element.tag == Option_Some; element = CONCAT(Cursor, Next)(&cursor))

#define Cursor(CursorElement) GENERIC(Cursor, CursorElement)
#define CursorNext(CursorElement) CONCAT(Cursor(CursorElement), Next)
#define CursorClone(CursorElement) CONCAT(Cursor(CursorElement), Clone)
#define CursorDestroy(CursorElement) CONCAT(Cursor(CursorElement), Destroy)
#endif

#ifdef CursorElement
#define RefT CursorElement
#include <core/Ref.h>

#if defined CURSOR_IMPLEMENTATION && !defined DISABLE_OPTION_REF_CursorElement_IMPLEMENTATION
#define OPTION_IMPLEMENTATION
#endif
#define OptionValue Ref(CursorElement)
#include <core/Option.h>

typedef interface(Cursor(CursorElement),
  Option(Ref(CursorElement)) (*Next)(void*);
) Cursor(CursorElement);

Option(Ref(CursorElement)) CursorNext(CursorElement)(Cursor(CursorElement) * cursor);
Cursor(CursorElement) * CursorClone(CursorElement)(Cursor(CursorElement) const* cursor);
void CursorDestroy(CursorElement)(Cursor(CursorElement) * cursor);

#ifdef CURSOR_IMPLEMENTATION
#include <stdlib.h>

Option(Ref(CursorElement)) CursorNext(CursorElement)(Cursor(CursorElement) * cursor) {
  return InterfaceDispatch(Next, cursor);
}

Cursor(CursorElement) * CursorClone(CursorElement)(Cursor(CursorElement) const* cursor) {
  return InterfaceDispatch(Clone, cursor);
}

void CursorDestroy(CursorElement)(Cursor(CursorElement) * cursor) {
  InterfaceDispatch(Destroy, cursor);
  free(cursor);
}
#endif // CURSOR_IMPLEMENTATION
#endif // CursorElement

#undef CursorElement
#undef CursorElementClone
#undef CursorElementDestroy
#undef CURSOR_IMPLEMENTATION
