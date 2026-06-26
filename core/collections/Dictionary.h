#ifndef DictionaryKey
#error Type parameter 'DictionaryKey' is not defined
#endif

#ifndef DictionaryKeyHash
#error Function 'UInt DictionaryKeyHash(DictionaryKey const* value)' is not defined
#endif

#ifndef DictionaryKeyEqual
#error Function 'Bool DictionaryKeyEqual(DictionaryKey const* left, DictionaryKey const* right)' is not defined
#endif

#ifndef DictionaryKeyClone
#define DictionaryKeyClone(value) (*(value))
#endif

#ifndef DictionaryKeyDestroy
#define DictionaryKeyDestroy(value) ((void)(value))
#endif

#ifndef DictionaryValue
#error Type parameter 'DictionaryValue' is not defined
#endif

#ifndef DictionaryValueClone
#define DictionaryValueClone(value) (*(value))
#endif

#ifndef DictionaryValueDestroy
#define DictionaryValueDestroy(value) ((void)(value))
#endif

#ifndef Dictionary
#include <core/Core.h>
#include <core/Hash.h>

#define Dictionary(Key, Value) GENERIC(Dictionary, Key, Value)
#define DictionaryDefault(Key, Value) CONCAT(Dictionary(Key, Value), Default)
#define DictionaryCreateWithCapacity(Key, Value) CONCAT(Dictionary(Key, Value), CreateWithCapacity)
#define DictionaryCount(Key, Value) CONCAT(Dictionary(Key, Value), Count)
#define DictionaryInsert(Key, Value) CONCAT(Dictionary(Key, Value), Insert)
#define DictionaryContainsKey(Key, Value) CONCAT(Dictionary(Key, Value), ContainsKey)
#define DictionaryAt(Key, Value) CONCAT(Dictionary(Key, Value), At)
#define DictionaryAtMut(Key, Value) CONCAT(Dictionary(Key, Value), AtMut)
#define DictionaryRemove(Key, Value) CONCAT(Dictionary(Key, Value), Remove)
#define DictionaryDestroy(Key, Value) CONCAT(Dictionary(Key, Value), Destroy)
#define DictionaryCursor(Key, Value) GENERIC(DictionaryCursor, Key, Value)
#define DictionaryCursorCreate(Key, Value) CONCAT(DictionaryCursor(Key, Value), Create)
#define DictionaryCursorNext(Key, Value) CONCAT(DictionaryCursor(Key, Value), Next)
#define DictionaryCursorClone(Key, Value) CONCAT(DictionaryCursor(Key, Value), Clone)
#define DictionaryCursorDestroy(Key, Value) CONCAT(DictionaryCursor(Key, Value), Destroy)
#define DictionaryCursorAsCursor(Key, Value) CONCAT(DictionaryCursor(Key, Value), As, Cursor(Ref(Tuple(Key, Value))))
#endif

#if defined DictionaryKey && defined DictionaryValue && defined DictionaryKeyHash && defined DictionaryKeyEqual
#define OptionValue DictionaryValue
#include <core/Option.h>

#define RefT DictionaryValue
#include <core/Ref.h>

#define OptionValue Ref(DictionaryValue)
#include <core/Option.h>

#define OptionValue RefMut(DictionaryValue)
#include <core/Option.h>

#define TupleArgs DictionaryKey, DictionaryValue
#include <core/Tuple.h>

#define OptionValue Tuple(DictionaryKey, DictionaryValue)
#include <core/Option.h>

#define ArrayElement Option(Tuple(DictionaryKey, DictionaryValue))
#include <core/collections/Array.h>

#define RefT Tuple(DictionaryKey, DictionaryValue)
#include <core/Ref.h>

#define CursorElement Ref(Tuple(DictionaryKey, DictionaryValue))
#include <core/collections/cursors/Cursor.h>

typedef struct Dictionary(DictionaryKey, DictionaryValue) {
  Array(Option(Tuple(DictionaryKey, DictionaryValue))) entries;
  UInt count;
} Dictionary(DictionaryKey, DictionaryValue);

Dictionary(DictionaryKey, DictionaryValue) DictionaryDefault(DictionaryKey, DictionaryValue)();
Dictionary(DictionaryKey, DictionaryValue) DictionaryCreateWithCapacity(DictionaryKey, DictionaryValue)(UInt capacity);
UInt DictionaryCount(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) const* dictionary);
Option(DictionaryValue) DictionaryInsert(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) * dictionary,
  DictionaryKey* key,
  DictionaryValue* value
);
Bool DictionaryContainsKey(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary,
  DictionaryKey* key
);
Option(Ref(DictionaryValue)) DictionaryAt(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary,
  DictionaryKey* key
);
Option(RefMut(DictionaryValue)) DictionaryAtMut(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) * dictionary,
  DictionaryKey* key
);
Option(Tuple(DictionaryKey, DictionaryValue)) DictionaryRemove(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) * dictionary,
  DictionaryKey* key
);
Unit DictionaryDestroy(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) * dictionary);

typedef struct DictionaryCursor(DictionaryKey, DictionaryValue) {
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary;
  UInt index;
} DictionaryCursor(DictionaryKey, DictionaryValue);

DictionaryCursor(DictionaryKey, DictionaryValue) DictionaryCursorCreate(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary
);
Option(Ref(Tuple(DictionaryKey, DictionaryValue))) DictionaryCursorNext(DictionaryKey, DictionaryValue)(
  DictionaryCursor(DictionaryKey, DictionaryValue) * cursor
);
DictionaryCursor(DictionaryKey, DictionaryValue) DictionaryCursorClone(DictionaryKey, DictionaryValue)(
  DictionaryCursor(DictionaryKey, DictionaryValue) const* cursor
);
Unit DictionaryCursorDestroy(DictionaryKey, DictionaryValue)(
  DictionaryCursor(DictionaryKey, DictionaryValue) * cursor
);
IMPLEMENT_SIG(DictionaryCursor(DictionaryKey, DictionaryValue), Cursor(Ref(Tuple(DictionaryKey, DictionaryValue))));

#ifdef DICTIONARY_IMPLEMENTATION
COREAPI Dictionary(DictionaryKey, DictionaryValue) DictionaryDefault(DictionaryKey, DictionaryValue)() {
  return (Dictionary(DictionaryKey, DictionaryValue)){
    .entries = ArrayDefault(Option(Tuple(DictionaryKey, DictionaryValue)))(),
    .count   = 0,
  };
}

COREAPI Dictionary(DictionaryKey, DictionaryValue) DictionaryCreateWithCapacity(DictionaryKey, DictionaryValue)(UInt capacity) {
  auto dictionary = (Dictionary(DictionaryKey, DictionaryValue)){
    .entries = ArrayCreateWithCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(NextPrime(capacity)),
    .count   = 0,
  };

  for (auto i = (UInt)0; i < ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary.entries); ++i) {
    *ArrayAtMut(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary.entries, i) = OptionNone(Tuple(DictionaryKey, DictionaryValue))();
  }

  return dictionary;
}

COREAPI UInt DictionaryCount(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) const* dictionary) {
  return dictionary->count;
}

static inline UInt CONCAT(Dictionary(DictionaryKey, DictionaryValue), FindPosition)(
  Array(Option(Tuple(DictionaryKey, DictionaryValue))) const* entries,
  DictionaryKey* key
) {
  auto cap      = ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(entries);
  auto position = DictionaryKeyHash(key) % cap;
  auto offset   = (UInt)1;

  while (true) {
    auto entryRef = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(entries, position);

    match(entryRef) {
      case (OptionNone) {
        return position;
      }
      case (OptionSome, entry) {
        if (DictionaryKeyEqual(&entry->_0, key)) {
          return position;
        }
      }
    }

    position += offset;
    offset += 2;

    if (position >= cap) {
      position -= cap;
    }
  }
}

Unit CONCAT(Dictionary(DictionaryKey, DictionaryValue), Rehash)(Dictionary(DictionaryKey, DictionaryValue) * dictionary);

// Places a fully-owned tuple at the slot its key probes to. Does not adjust
// count or destroy any previous occupant — the caller is responsible for both.
// Used by Rehash (rebuilding into a fresh table) and Remove (shuffling a
// cluster after a hole opens).
static inline Unit CONCAT(Dictionary(DictionaryKey, DictionaryValue), Place)(
  Dictionary(DictionaryKey, DictionaryValue) * dictionary,
  Tuple(DictionaryKey, DictionaryValue) entry
) {
  auto position = CONCAT(Dictionary(DictionaryKey, DictionaryValue), FindPosition)(&dictionary->entries, &entry._0);
  *ArrayAtMut(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position) = OptionSome(Tuple(DictionaryKey, DictionaryValue))(entry);
  return_unit;
}

COREAPI Option(DictionaryValue) DictionaryInsert(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) * dictionary,
  DictionaryKey* key,
  DictionaryValue* value
) {
  // Lazy allocation: a default-constructed dictionary has no storage.
  if (ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries) == 0) {
    *dictionary = DictionaryCreateWithCapacity(DictionaryKey, DictionaryValue)(8);
  }

  auto position      = CONCAT(Dictionary(DictionaryKey, DictionaryValue), FindPosition)(&dictionary->entries, key);
  auto previousValue = OptionNone(DictionaryValue)();

  match(ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position)) {
    case (OptionSome, entry) {
      previousValue = OptionSome(DictionaryValue)(entry->_1);
      DictionaryKeyDestroy(&entry->_0);
    }
    case (OptionNone) {
      ++dictionary->count;
    }
  }

  *ArrayAtMut(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position) = OptionSome(Tuple(DictionaryKey, DictionaryValue))(
    (Tuple(DictionaryKey, DictionaryValue)){
      ._0 = DictionaryKeyClone(key),
      ._1 = DictionaryValueClone(value),
    }
  );

  if (dictionary->count > ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries) / 2) {
    CONCAT(Dictionary(DictionaryKey, DictionaryValue), Rehash)(dictionary);
  }

  return previousValue;
}

COREAPI Unit CONCAT(Dictionary(DictionaryKey, DictionaryValue), Rehash)(Dictionary(DictionaryKey, DictionaryValue) * dictionary) {
  auto oldEntries = dictionary->entries;
  auto oldCount   = dictionary->count;

  *dictionary     = DictionaryCreateWithCapacity(DictionaryKey, DictionaryValue)(ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries) * 2);

  for (auto i = (UInt)0; i < ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries); ++i) {
    match(ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries, i)) {
      case (OptionSome, entry) {
        CONCAT(Dictionary(DictionaryKey, DictionaryValue), Place)(dictionary, *entry);
      }
      default: break;
    }
  }

  dictionary->count = oldCount;
  ArrayDestroy(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries);
  return_unit;
}

COREAPI Bool DictionaryContainsKey(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary,
  DictionaryKey* key
) {
  auto position = CONCAT(Dictionary(DictionaryKey, DictionaryValue), FindPosition)(&dictionary->entries, key);
  match(ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position)) {
    case (OptionSome) {
      return true;
    } default: return false;
  }
}

COREAPI Option(Ref(DictionaryValue)) DictionaryAt(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary,
  DictionaryKey* key
) {
  auto position = CONCAT(Dictionary(DictionaryKey, DictionaryValue), FindPosition)(&dictionary->entries, key);
  auto entryRef = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position);
  match(entryRef) {
    case (OptionSome, entry) {
      return OptionSome(Ref(DictionaryValue))(&entry->_1);
    } default: return OptionNone(Ref(DictionaryValue))();
  }
}

COREAPI Option(RefMut(DictionaryValue)) DictionaryAtMut(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) * dictionary,
  DictionaryKey* key
) {
  auto position = CONCAT(Dictionary(DictionaryKey, DictionaryValue), FindPosition)(&dictionary->entries, key);
  auto entryRef = ArrayAtMut(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position);
  match(entryRef) {
    case (OptionSome, entry) {
      return OptionSome(RefMut(DictionaryValue))(&entry->_1);
    } default: return OptionNone(RefMut(DictionaryValue))();
  }
}

COREAPI Option(Tuple(DictionaryKey, DictionaryValue)) DictionaryRemove(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) * dictionary,
  DictionaryKey* key
) {
  auto position = CONCAT(Dictionary(DictionaryKey, DictionaryValue), FindPosition)(&dictionary->entries, key);
  auto entryRef = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position);

  match(entryRef) {
    case (OptionSome, entry) {
      auto removed = *entry;
      *ArrayAtMut(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position) = OptionNone(Tuple(DictionaryKey, DictionaryValue))();
      --dictionary->count;

      // Reinsert following cluster
      auto cap     = ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries);
      auto offset  = (UInt)1;
      auto nextPos = position + offset;
      offset += 2;
      if (nextPos >= cap) {
        nextPos -= cap;
      }

      while (true) {
        match(ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, nextPos)) {
          case (OptionSome, clustered) {
            auto moved = *clustered;
            *ArrayAtMut(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, nextPos) = OptionNone(Tuple(DictionaryKey, DictionaryValue))();
            CONCAT(Dictionary(DictionaryKey, DictionaryValue), Place)(dictionary, moved);

            nextPos += offset;
            offset += 2;
            if (nextPos >= cap) {
              nextPos -= cap;
            }
          }
          case (OptionNone) {
            return OptionSome(Tuple(DictionaryKey, DictionaryValue))(removed);
          }
        }
      }
    }
    case (OptionNone) {
      return OptionNone(Tuple(DictionaryKey, DictionaryValue))();
    }
  }
}

COREAPI Unit DictionaryDestroy(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue)* dictionary) {
  ArrayDestroy(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries);
  dictionary->count = 0;
  return_unit;
}

COREAPI DictionaryCursor(DictionaryKey, DictionaryValue) DictionaryCursorCreate(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary
) {
  return (DictionaryCursor(DictionaryKey, DictionaryValue)){
    .dictionary = dictionary,
    .index      = 0,
  };
}

COREAPI Option(Ref(Tuple(DictionaryKey, DictionaryValue))) DictionaryCursorNext(DictionaryKey, DictionaryValue)(
  DictionaryCursor(DictionaryKey, DictionaryValue) * dictionaryCursor
) {
  while (dictionaryCursor->index < ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionaryCursor->dictionary->entries)) {
    auto entryRef = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(
      &dictionaryCursor->dictionary->entries,
      dictionaryCursor->index++
    );

    match(entryRef) {
      case (OptionSome, entry) {
        return OptionSome(Ref(Tuple(DictionaryKey, DictionaryValue)))(entry);
      }
      default: break;
  }
}

return OptionNone(Ref(Tuple(DictionaryKey, DictionaryValue)))();
}

COREAPI DictionaryCursor(DictionaryKey, DictionaryValue) DictionaryCursorClone(DictionaryKey, DictionaryValue)(
  DictionaryCursor(DictionaryKey, DictionaryValue) const* cursor
) {
  return (DictionaryCursor(DictionaryKey, DictionaryValue)){
    .dictionary = cursor->dictionary,
    .index      = cursor->index,
  };
}

COREAPI Unit DictionaryCursorDestroy(DictionaryKey, DictionaryValue)(
  DictionaryCursor(DictionaryKey, DictionaryValue) * cursor
) {
  cursor->index = 0;
  return_unit;
}

COREAPI IMPLEMENT(
  DictionaryCursor(DictionaryKey, DictionaryValue),
  Cursor(Ref(Tuple(DictionaryKey, DictionaryValue))),
  .Next    = (void*)DictionaryCursorNext(DictionaryKey, DictionaryValue),
  .Destroy = (void*)DictionaryCursorDestroy(DictionaryKey, DictionaryValue),
);
#endif // defined DictionaryKey && defined DictionaryValue && defined DictionaryKeyHash && defined DictionaryKeyEqual
#endif // DictionaryKey

#undef DICTIONARY_IMPLEMENTATION
#undef DictionaryKey
#undef DictionaryKeyHash
#undef DictionaryKeyEqual
#undef DictionaryKeyClone
#undef DictionaryKeyDestroy
#undef DictionaryValue
#undef DictionaryValueClone
#undef DictionaryValueDestroy
