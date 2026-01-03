#ifndef SetElement
#error Type parameter 'SetElement' is not defined.
#endif

#ifndef SetElementHash
#error Function 'UInt32 SetElementHash(SetElement value)' is not defined.
#define SetElementHash(key)
#endif

#ifndef SetElementEqual
#error Function 'Bool SetElementEqual(SetElement left, SetElement right)' is not defined.
#define SetElementEqual(a, b)
#endif

#include <core/Core.h>
#include <core/Generic.h>

#ifndef DISABLE_Dectionary_SetElement_Unit
#define DictionaryKey SetElement
#define DictionaryKeyHash SetElementHash
#define DictionaryKeyEqual SetElementEqual
#define DictionaryValue Unit
#include <core/collections/Dictionary.h>
#endif
#undef DISABLE_Dectionary_SetElement_Unit

#ifndef DISABLE_Option_SetElement
#define OptionValue SetElement
#include <core/Option.h>
#endif
#undef DISABLE_Option_SetElement

#ifndef DISABLE_Cursor_SetElement
#define CursorElement SetElement
#include <core/collections/Cursor.h>
#endif
#undef DISABLE_Cursor_SetElement

#ifndef Set
#define Set(SetElement) GENERIC(Set, SetElement)
#define SetDefault(SetElement) GENERIC(SetDefault, SetElement)
#define SetCount(SetElement) GENERIC(SetCount, SetElement)
#define SetInsert(SetElement) GENERIC(SetInsert, SetElement)
#define SetContains(SetElement) GENERIC(SetContains, SetElement)
#define SetRemove(SetElement) GENERIC(SetRemove, SetElement)
#define SetDestroy(SetElement) GENERIC(SetDestroy, SetElement)
#define SetCursor(SetElement) GENERIC(SetCursor, SetElement)
#define SetCursorCreate(SetElement) GENERIC(SetCursorCreate, SetElement)
#define SetCursorNext(SetElement) GENERIC(SetCursorNext, SetElement)
#endif

typedef Dictionary(SetElement, Unit) Set(SetElement);

static Set(SetElement) SetDefault(SetElement)() {
  return DictionaryDefault(SetElement, Unit)();
}

static UInt SetCount(SetElement)(Set(SetElement) const* set) {
  return DictionaryCount(SetElement, Unit)(set);
}

static Bool SetInsert(SetElement)(Set(SetElement) * set, SetElement element) {
  return DictionaryInsert(SetElement, Unit)(set, element, (Unit){}).tag == Option_None;
}

static Bool SetContains(SetElement)(Set(SetElement) const* set, SetElement element) {
  return DictionaryContainsKey(SetElement, Unit)(set, element);
}

static Bool SetRemove(SetElement)(Set(SetElement) * set, SetElement element) {
  return DictionaryRemove(SetElement, Unit)(set, element).tag == Option_Some;
}

static void SetDestroy(SetElement)(Set(SetElement) set) {
  DictionaryDestroy(SetElement, Unit)(set);
}

typedef DictionaryCursor(SetElement, Unit) SetCursor(SetElement);

static SetCursor(SetElement) SetCursorCreate(SetElement)(Set(SetElement) const* set) {
  return DictionaryCursorCreate(SetElement, Unit)(set);
}

static Option(SetElement) SetCursorNext(SetElement)(SetCursor(SetElement) * cursor) {
  auto result = DictionaryCursorNext(SetElement, Unit)(cursor);
  return result.tag == Option_Some
           ? OptionSome(SetElement)(result.value._0)
           : OptionNone(SetElement)();
}

implement(
  Cursor(SetElement),
  SetCursor(SetElement),
  .Next = (void*)SetCursorNext(SetElement),
);

#undef SetElement
#undef SetElementHash
#undef SetElementEqual
