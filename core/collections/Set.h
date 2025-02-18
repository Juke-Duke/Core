#ifndef SetElement
#error "Type parameter 'SetElement' is not defined."
#endif

#ifndef SetElementHash
#error "Function 'SetElementHash' is not defined."
#define SetElementHash(key)
#endif

#ifndef SetElementEqual
#error "Function 'SetElementEqual' is not defined."
#define SetElementEqual(a, b)
#endif

#include <core/Core.h>

#define DictionaryKey SetElement
#define DictionaryKeyHash(key) SetElementHash(key)
#define DictionaryKeyEqual(a, b) SetElementEqual(a, b)
#define DictionaryValue Unit
#include <core/collections/Dictionary.h>

#ifndef Set
#define Set(SetElement) GENERIC(Set, SetElement)
#define SetDefault(SetElement) GENERIC(SetDefault, SetElement)
#define SetCount(SetElement) GENERIC(SetCount, SetElement)
#define SetInsert(SetElement) GENERIC(SetInsert, SetElement)
#define SetContains(SetElement) GENERIC(SetContains, SetElement)
#define SetRemove(SetElement) GENERIC(SetRemove, SetElement)
#define SetIsDisjoint(SetElement) GENERIC(SetIsDisjoint, SetElement)
#define SetDestroy(SetElement) GENERIC(SetDestroy, SetElement)
#endif

typedef Dictionary(SetElement, Unit) Set(SetElement);

static Set(SetElement) SetDefault(SetElement)() {
  return DictionaryDefault(SetElement, Unit)();
}

static UInt SetCount(SetElement)(Set(SetElement) const* set) {
  return DictionaryCount(SetElement, Unit)(set);
}

static Bool SetInsert(SetElement)(Set(SetElement)* set, SetElement element) {
  return DictionaryInsert(SetElement, Unit)(set, element, (Unit){}).tag == Option_None;
}

static Bool SetContains(SetElement)(Set(SetElement) const* set, SetElement element) {
  return DictionaryContainsKey(SetElement, Unit)(set, element);
}

static Bool SetRemove(SetElement)(Set(SetElement)* set, SetElement element) {
  return DictionaryRemove(SetElement, Unit)(set, element).tag == Option_Some;
}

static void SetDestroy(SetElement)(Set(SetElement) set) {
  DictionaryDestroy(SetElement, Unit)(set);
}

#undef SetElement
#undef SetElementHash
#undef SetElementEqual
