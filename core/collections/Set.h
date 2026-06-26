#ifndef SetElement
#error Type parameter 'SetElement' is not defined
#endif

#ifndef SetElementHash
#error Function 'UInt SetElementHash(SetElement const* value)' is not defined
#endif

#ifndef SetElementEqual
#error Function 'Bool SetElementEqual(SetElement const* left, SetElement const* right)' is not defined
#endif

#ifndef SetElementClone
#define SetElementClone(value) (*(value))
#endif

#ifndef SetElementDestroy
#define SetElementDestroy(value) ((void)(value))
#endif

#ifndef Set
#include <core/Core.h>

#define Set(SetElement) GENERIC(Set, SetElement)
#define SetDefault(SetElement) CONCAT(Set(SetElement), Default)
#define SetCreateWithCapacity(SetElement) CONCAT(Set(SetElement), CreateWithCapacity)
#define SetCount(SetElement) CONCAT(Set(SetElement), Count)
#define SetInsert(SetElement) CONCAT(Set(SetElement), Insert)
#define SetContains(SetElement) CONCAT(Set(SetElement), Contains)
#define SetRemove(SetElement) CONCAT(Set(SetElement), Remove)
#define SetDestroy(SetElement) CONCAT(Set(SetElement), Destroy)

#define SetCursor(SetElement) GENERIC(SetCursor, SetElement)
#define SetCursorCreate(SetElement) CONCAT(SetCursor(SetElement), Create)
#define SetCursorNext(SetElement) CONCAT(SetCursor(SetElement), Next)
#define SetCursorClone(SetElement) CONCAT(SetCursor(SetElement), Clone)
#define SetCursorDestroy(SetElement) CONCAT(SetCursor(SetElement), Destroy)
#define SetCursorAsCursor(SetElement) CONCAT(SetCursor(SetElement), As, Cursor(Ref(SetElement)))
#endif

#ifdef SetElement
#define DictionaryKey SetElement
#define DictionaryKeyHash SetElementHash
#define DictionaryKeyEqual SetElementEqual
#define DictionaryValue Unit
#include <core/collections/Dictionary.h>

#define RefT SetElement
#include <core/Ref.h>

#define OptionValue Ref(SetElement)
#include <core/Option.h>

#define CursorElement Ref(SetElement)
#include <core/collections/cursors/Cursor.h>

typedef Dictionary(SetElement, Unit) Set(SetElement);

Set(SetElement) SetDefault(SetElement)();
Set(SetElement) SetCreateWithCapacity(SetElement)(UInt capacity);
UInt SetCount(SetElement)(Set(SetElement) const* set);
Bool SetInsert(SetElement)(Set(SetElement) * set, SetElement element);
Bool SetContains(SetElement)(Set(SetElement) const* set, SetElement* element);
Option(SetElement) SetRemove(SetElement)(Set(SetElement) * set, SetElement* element);
Unit SetDestroy(SetElement)(Set(SetElement) * set);

typedef DictionaryCursor(SetElement, Unit) SetCursor(SetElement);

SetCursor(SetElement) SetCursorCreate(SetElement)(Set(SetElement) const* set);
Option(Ref(SetElement)) SetCursorNext(SetElement)(SetCursor(SetElement) * cursor);
SetCursor(SetElement) SetCursorClone(SetElement)(SetCursor(SetElement) const* cursor);
Unit SetCursorDestroy(SetElement)(SetCursor(SetElement) * cursor);
IMPLEMENT_SIG(SetCursor(SetElement), Cursor(Ref(SetElement)));

#ifdef SET_IMPLEMENTATION
COREAPI Set(SetElement) SetDefault(SetElement)() {
  return DictionaryDefault(SetElement, Unit)();
}

COREAPI Set(SetElement) SetCreateWithCapacity(SetElement)(UInt capacity) {
  return DictionaryCreateWithCapacity(SetElement, Unit)(capacity);
}

COREAPI UInt SetCount(SetElement)(Set(SetElement) const* set) {
  return DictionaryCount(SetElement, Unit)(set);
}

COREAPI Bool SetInsert(SetElement)(Set(SetElement) * set, SetElement element) {
  auto unit     = (Unit){};
  auto previous = DictionaryInsert(SetElement, Unit)(set, &element, &unit);
  match(&previous) {
    case (OptionNone) {
      return true;
    }
    case (OptionSome) {
      return false;
    }
  }
}

COREAPI Bool SetContains(SetElement)(Set(SetElement) const* set, SetElement* element) {
  return DictionaryContainsKey(SetElement, Unit)(set, element);
}

COREAPI Option(SetElement) SetRemove(SetElement)(Set(SetElement) * set, SetElement* element) {
  auto removed = DictionaryRemove(SetElement, Unit)(set, element);
  match(&removed) {
    case (OptionSome, tup) {
      return OptionSome(SetElement)(tup->_0);
    }
    case (OptionNone) {
      return OptionNone(SetElement)();
    }
  }
}

COREAPI Unit SetDestroy(SetElement)(Set(SetElement) * set) {
  return DictionaryDestroy(SetElement, Unit)(set);
}

COREAPI SetCursor(SetElement) SetCursorCreate(SetElement)(Set(SetElement) const* set) {
  return DictionaryCursorCreate(SetElement, Unit)(set);
}

COREAPI Option(Ref(SetElement)) SetCursorNext(SetElement)(SetCursor(SetElement) * cursor) {
  auto next = DictionaryCursorNext(SetElement, Unit)(cursor);
  match(&next) {
    case (OptionSome, entry) {
      return OptionSome(Ref(SetElement))(&(*entry)->_0);
    }
    case (OptionNone) {
      return OptionNone(Ref(SetElement))();
    }
  }
}

COREAPI SetCursor(SetElement) SetCursorClone(SetElement)(SetCursor(SetElement) const* cursor) {
  return DictionaryCursorClone(SetElement, Unit)(cursor);
}

COREAPI Unit SetCursorDestroy(SetElement)(SetCursor(SetElement) * cursor) {
  return DictionaryCursorDestroy(SetElement, Unit)(cursor);
}

COREAPI IMPLEMENT(
  SetCursor(SetElement),
  Cursor(Ref(SetElement)),
  .Next    = (void*)SetCursorNext(SetElement),
  .Destroy = (void*)SetCursorDestroy(SetElement),
);
#endif // SET_IMPLEMENTATION
#endif // SetElement

#undef SET_IMPLEMENTATION
#undef SetElement
#undef SetElementHash
#undef SetElementEqual
#undef SetElementClone
#undef SetElementDestroy
