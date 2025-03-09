#ifndef SetElement
#error Type parameter 'SetElement' is not defined.
#endif

#ifndef SetElementHash
#error Function 'SetElementHash' is not defined.
#define SetElementHash(key)
#endif

#ifndef SetElementEqual
#error Function 'SetElementEqual' is not defined.
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

#ifndef Set
#define Set(SetElement) GENERIC(Set, SetElement)
#define SetDefault(SetElement) GENERIC(SetDefault, SetElement)
#define SetCount(SetElement) GENERIC(SetCount, SetElement)
#define SetInsert(SetElement) GENERIC(SetInsert, SetElement)
#define SetContains(SetElement) GENERIC(SetContains, SetElement)
#define SetRemove(SetElement) GENERIC(SetRemove, SetElement)
#define SetDestroy(SetElement) GENERIC(SetDestroy, SetElement)
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

#undef SetElement
#undef SetElementHash
#undef SetElementEqual
