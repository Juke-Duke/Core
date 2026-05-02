#ifndef Dictionary
#include <core/Core.h>
#include <core/Hash.h>

#define Dictionary(Key, Value) GENERIC(Dictionary, Key, Value)
#define DictionaryDefault(Key, Value) CONCAT(Dictionary(Key, Value), Default)
#define DictionaryCreateWithCapacity(Key, Value) CONCAT(Dictionary(Key, Value), CreateWithCapacity)
#define DictionaryCount(Key, Value) CONCAT(Dictionary(Key, Value), Count)
#define DictionaryFindPosition(Key, Value) CONCAT(Dictionary(Key, Value), FindPosition)
#define DictionaryInsert(Key, Value) CONCAT(Dictionary(Key, Value), Insert)
#define DictionaryRehash(Key, Value) CONCAT(Dictionary(Key, Value), Rehash)
#define DictionaryContainsKey(Key, Value) CONCAT(Dictionary(Key, Value), ContainsKey)
#define DictionaryAt(Key, Value) CONCAT(Dictionary(Key, Value), At)
#define DictionaryRemove(Key, Value) CONCAT(Dictionary(Key, Value), Remove)
#define DictionaryDestroy(Key, Value) CONCAT(Dictionary(Key, Value), Destroy)
#endif

#ifndef DictionaryKey
#error Type parameter 'DictionaryKey' is not defined.
#endif

#ifndef DictionaryKeyHash
#error Function 'UInt DictionaryKeyHash(DictionaryKey const* value)' is not defined.
#endif

#ifndef DictionaryKeyEqual
#error Function 'Bool DictionaryKeyEqual(DictionaryKey const* left, DictionaryKey const* right)' is not defined.
#endif

#ifndef DictionaryKeyClone
#define DictionaryKeyClone(value) (*(value))
#endif

#ifndef DictionaryKeyDestroy
#define DictionaryKeyDestroy(value) ((void)(value))
#endif

#ifndef DictionaryValue
#error Type parameter 'DictionaryValue' is not defined.
#endif

#ifndef DictionaryValueClone
#define DictionaryValueClone(value) (*(value))
#endif

#ifndef DictionaryValueDestroy
#define DictionaryValueDestroy(value) ((void)(value))
#endif

#if defined DictionaryKey && defined DictionaryValue && defined DictionaryKeyHash && defined DictionaryKeyEqual
#ifdef DICTIONARY_IMPLEMENTATION
#define TUPLE_IMPLEMENTATION
#endif
#define TupleArgs DictionaryKey, DictionaryValue
#define TupleT0Clone DictionaryKeyClone
#define TupleT0Destroy DictionaryKeyDestroy
#define TupleT1Clone DictionaryValueClone
#define TupleT1Destroy DictionaryValueDestroy
#include <core/Tuple.h>

#ifdef DICTIONARY_IMPLEMENTATION
#define OPTION_IMPLEMENTATION
#endif
#define OptionValue Tuple(DictionaryKey, DictionaryValue)
#define OptionValueClone TupleClone(DictionaryKey, DictionaryValue)
#define OptionValueDestroy TupleDestroy(DictionaryKey, DictionaryValue)
#include <core/Option.h>

#ifdef DICTIONARY_IMPLEMENTATION
#define ARRAY_IMPLEMENTATION
#endif
#define ArrayElement Option(Tuple(DictionaryKey, DictionaryValue))
#define ArrayElementClone OptionClone(Tuple(DictionaryKey, DictionaryValue))
#define ArrayElementDestroy OptionDestroy(Tuple(DictionaryKey, DictionaryValue))
#include <core/collections/Array.h>

typedef struct Dictionary(DictionaryKey, DictionaryValue) {
  Array(Option(Tuple(DictionaryKey, DictionaryValue))) entries;
  UInt count;
} Dictionary(DictionaryKey, DictionaryValue);

Dictionary(DictionaryKey, DictionaryValue) DictionaryDefault(DictionaryKey, DictionaryValue)();
Dictionary(DictionaryKey, DictionaryValue) DictionaryCreateWithCapacity(DictionaryKey, DictionaryValue)(UInt capacity);
UInt DictionaryCount(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) const* dictionary);
UInt DictionaryFindPosition(DictionaryKey, DictionaryValue)(Array(Option(Tuple(DictionaryKey, DictionaryValue))) const* entries, DictionaryKey key);

#endif

static Dictionary(DictionaryKey, DictionaryValue) DictionaryDefault(DictionaryKey, DictionaryValue)() {
  return (Dictionary(DictionaryKey, DictionaryValue)){
    .entries = null,
    .count   = 0,
  };
}

static Dictionary(DictionaryKey, DictionaryValue) DictionaryCreateWithCapacity(DictionaryKey, DictionaryValue)(UInt capacity) {
  return (Dictionary(DictionaryKey, DictionaryValue)){
    .entries = ArrayCreateWithCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(NextPrime(capacity)),
    .count   = 0,
  };
}

static UInt DictionaryCount(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) const* dictionary) {
  return dictionary->count;
}

static UInt DictionaryFindPosition(DictionaryKey, DictionaryValue)(
  Array(Option(Tuple(DictionaryKey, DictionaryValue))) const* entries,
  DictionaryKey key
) {
  auto offset   = (UInt)1;
  auto position = DictionaryKeyHash(&key) % ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(entries);

  for (
    auto entry = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(entries, position);
    entry.tag == Option_Some && !DictionaryKeyEqual(&entry.value._0, &key);
    entry = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(entries, position)) {
    position += offset;
    offset += 2;

    if (position >= ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(entries)) {
      position -= ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(entries);
    }
  }

  return position;
}

static void DictionaryRehash(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) * dictionary);

static Option(DictionaryValue) DictionaryInsert(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) * dictionary,
  DictionaryKey key,
  DictionaryValue value
) {
  auto position      = DictionaryFindPosition(DictionaryKey, DictionaryValue)(&dictionary->entries, key);

  auto previousValue = OptionNone(DictionaryValue)();

  auto entry         = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position);
  if (entry.tag == Option_Some) {
    previousValue = OptionSome(DictionaryValue)(entry.value._1);
  }
  else {
    ++dictionary->count;
  }

  ArraySetAt(Option(Tuple(DictionaryKey, DictionaryValue)))(
    &dictionary->entries,
    position,
    OptionSome(Tuple(DictionaryKey, DictionaryValue))(
      (Tuple(DictionaryKey, DictionaryValue)){._0 = key, ._1 = value}
    )
  );

  if (dictionary->count > ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries) / 2) {
    DictionaryRehash(DictionaryKey, DictionaryValue)(dictionary);
  }

  return previousValue;
}

static void DictionaryRehash(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) * dictionary) {
  auto oldEntries = dictionary->entries;

  *dictionary     = DictionaryCreateWithCapacity(DictionaryKey, DictionaryValue)(ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries) * 2);

  for (auto i = 0; i < ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries); ++i) {
    ArraySetAt(Option(Tuple(DictionaryKey, DictionaryValue)))(
      &dictionary->entries,
      i,
      OptionNone(Tuple(DictionaryKey, DictionaryValue))()
    );
  }

  for (auto i = 0; i < ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries); ++i) {
    if (ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries, i).tag == Option_Some) {
      auto entry = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries, i).value;
      DictionaryInsert(DictionaryKey, DictionaryValue)(dictionary, entry._0, entry._1);
    }
  }

  ArrayDestroy(Option(Tuple(DictionaryKey, DictionaryValue)))(oldEntries);
}

static Option(DictionaryValue) DictionaryAt(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary,
  DictionaryKey key
);

static Bool DictionaryContainsKey(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary,
  DictionaryKey key
) {
  auto position = DictionaryFindPosition(DictionaryKey, DictionaryValue)(&dictionary->entries, key);
  return ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position).tag == Option_Some;
}

static Option(DictionaryValue) DictionaryAt(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary,
  DictionaryKey key
) {
  auto position = DictionaryFindPosition(DictionaryKey, DictionaryValue)(&dictionary->entries, key);
  auto entry    = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position);
  return entry.tag == Option_Some ? OptionSome(DictionaryValue)(entry.value._1) : OptionNone(DictionaryValue)();
}

static Option(Tuple(DictionaryKey, DictionaryValue)) DictionaryRemove(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) * dictionary,
  DictionaryKey key
) {
  auto position = DictionaryFindPosition(DictionaryKey, DictionaryValue)(&dictionary->entries, key);
  auto entry    = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position);

  if (entry.tag == Option_Some) {
    ArraySetAt(Option(Tuple(DictionaryKey, DictionaryValue)))(
      &dictionary->entries,
      position,
      OptionNone(Tuple(DictionaryKey, DictionaryValue))()
    );

    --dictionary->count;
  }

  return entry;
}

static void DictionaryDestroy(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) dictionary) {
  ArrayDestroy(Option(Tuple(DictionaryKey, DictionaryValue)))(dictionary.entries);
  dictionary.count = 0;
}

typedef struct {
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary;
  UInt index;
} DictionaryCursor(DictionaryKey, DictionaryValue);

static DictionaryCursor(DictionaryKey, DictionaryValue) DictionaryCursorCreate(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary
) {
  return (DictionaryCursor(DictionaryKey, DictionaryValue)){
    .dictionary = dictionary,
    .index      = 0,
  };
}

static Option(Tuple(DictionaryKey, DictionaryValue)) DictionaryCursorNext(DictionaryKey, DictionaryValue)(
  DictionaryCursor(DictionaryKey, DictionaryValue) * dictionaryCursor
) {
  while (dictionaryCursor->index < ArrayCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionaryCursor->dictionary->entries)) {
    auto entry = ArrayAt(Option(Tuple(DictionaryKey, DictionaryValue)))(
      &dictionaryCursor->dictionary->entries,
      dictionaryCursor->index++
    );

    if (entry.tag == Option_Some) {
      return OptionSome(Tuple(DictionaryKey, DictionaryValue))(entry.value);
    }
  }

  return OptionNone(Tuple(DictionaryKey, DictionaryValue))();
}

implement(
  Cursor(Tuple(DictionaryKey, DictionaryValue)),
  DictionaryCursor(DictionaryKey, DictionaryValue),
  .Next = (void*)DictionaryCursorNext(DictionaryKey, DictionaryValue),
);

#undef DictionaryKey
#undef DictionaryKeyHash
#undef DictionaryKeyEqual
#undef DictionaryValue
