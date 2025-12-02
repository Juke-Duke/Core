#ifndef DictionaryKey
#error Type parameter 'DictionaryKey' is not defined.
#endif

#ifndef DictionaryKeyHash
#error Function 'DictionaryKeyHash' is not defined.
#endif

#ifndef DictionaryKeyEqual
#error Function 'DictionaryKeyEqual' is not defined.
#endif

#ifndef DictionaryValue
#error Type parameter 'DictionaryValue' is not defined.
#endif

#include <core/Core.h>
#include <core/Generic.h>
#include <core/Hash.h>

#ifndef DISABLE_Tuple_DictionaryKey_DictionaryValue
#define TupleArgs 2
#define TupleT0 DictionaryKey
#define TupleT1 DictionaryValue
#include <core/Tuple.h>
#endif
#undef DISABLE_Tuple_DictionaryKey_DictionaryValue

#ifndef DISABLE_Option_Tuple_DictionaryKey_DictionaryValue
#define OptionValue Tuple(DictionaryKey, DictionaryValue)
#include <core/Option.h>
#endif
#undef DISABLE_Option_Tuple_DictionaryKey_DictionaryValue

#ifndef DISABLE_Option_DictionaryValue
#define OptionValue DictionaryValue
#include <core/Option.h>
#endif
#undef DISABLE_Option_DictionaryValue

#ifndef DISABLE_List_Option_Tuple_DictionaryKey_DictionaryValue
#define ListElement Option(Tuple(DictionaryKey, DictionaryValue))
#include <core/collections/List.h>
#endif
#undef DISABLE_List_Option_Tuple_DictionaryKey_DictionaryValue

#ifndef Dictionary
#define Dictionary(Key, Value) GENERIC2(Dictionary, Key, Value)
#define DictionaryDefault(Key, Value) GENERIC2(DictionaryDefault, Key, Value)
#define DictionaryCount(Key, Value) GENERIC2(DictionaryCount, Key, Value)
#define DictionaryFindPosition(Key, Value) GENERIC2(DictionaryFindPosition, Key, Value)
#define DictionaryInsert(Key, Value) GENERIC2(DictionaryInsert, Key, Value)
#define DictionaryRehash(Key, Value) GENERIC2(DictionaryRehash, Key, Value)
#define DictionaryContainsKey(Key, Value) GENERIC2(DictionaryContains, Key, Value)
#define DictionaryAt(Key, Value) GENERIC2(DictionaryAt, Key, Value)
#define DictionaryRemove(Key, Value) GENERIC2(DictionaryRemoveAt, Key, Value)
#define DictionaryDestroy(Key, Value) GENERIC2(DictionaryDestroy, Key, Value)
#endif

typedef struct {
  List(Option(Tuple(DictionaryKey, DictionaryValue))) entries;
  UInt count;
} Dictionary(DictionaryKey, DictionaryValue);

static Dictionary(DictionaryKey, DictionaryValue) DictionaryDefault(DictionaryKey, DictionaryValue)() {
  return (Dictionary(DictionaryKey, DictionaryValue)){
    .entries = ListCreate(Option(Tuple(DictionaryKey, DictionaryValue)))(11),
    .count = 0,
  };
}

static UInt DictionaryCount(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) const* dictionary) {
  return dictionary->count;
}

static UInt DictionaryFindPosition(DictionaryKey, DictionaryValue)(
  List(Option(Tuple(DictionaryKey, DictionaryValue))) const* entries,
  DictionaryKey key
) {
  auto offset = (UInt)1;
  auto position = DictionaryKeyHash(key) % ListCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(entries);

  for (
    auto entry = ListAt(Option(Tuple(DictionaryKey, DictionaryValue)))(entries, position);
    entry.tag == Option_Some && !DictionaryKeyEqual(entry.value._0, key);
    entry = ListAt(Option(Tuple(DictionaryKey, DictionaryValue)))(entries, position)
  ) {
    position += offset;
    offset += 2;

    if (position >= ListCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(entries)) {
      position -= ListCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(entries);
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
  auto position = DictionaryFindPosition(DictionaryKey, DictionaryValue)(&dictionary->entries, key);

  auto previousValue = OptionNone(DictionaryValue)();

  auto entry = ListAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position);
  if (entry.tag == Option_Some) {
    previousValue = OptionSome(DictionaryValue)(entry.value._1);
  }
  else {
    ++dictionary->count;
  }

  ListSetAt(Option(Tuple(DictionaryKey, DictionaryValue)))(
    &dictionary->entries,
    position,
    OptionSome(Tuple(DictionaryKey, DictionaryValue))(
      (Tuple(DictionaryKey, DictionaryValue)){._0 = key, ._1 = value}
    )
  );

  if (dictionary->count > ListCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries) / 2) {
    DictionaryRehash(DictionaryKey, DictionaryValue)(dictionary);
  }

  return previousValue;
}

static Option(DictionaryValue) DictionaryAt(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary,
  DictionaryKey key
);

static void DictionaryRehash(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) * dictionary) {
  auto oldEntries = dictionary->entries;

  dictionary->entries = ListCreate(Option(Tuple(DictionaryKey, DictionaryValue)))(
    NextPrime(ListCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries) * 2)
  );

  for (auto i = 0; i < ListCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries); ++i) {
    ListSetAt(Option(Tuple(DictionaryKey, DictionaryValue)))(
      &dictionary->entries,
      i,
      OptionNone(Tuple(DictionaryKey, DictionaryValue))()
    );
  }

  for (auto i = 0; i < ListCapacity(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries); ++i) {
    if (ListAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries, i).tag == Option_Some) {
      auto entry = ListAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&oldEntries, i).value;
      DictionaryInsert(DictionaryKey, DictionaryValue)(dictionary, entry._0, entry._1);
    }
  }

  ListDestroy(Option(Tuple(DictionaryKey, DictionaryValue)))(oldEntries);
}

static Bool DictionaryContainsKey(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary,
  DictionaryKey key
) {
  auto position = DictionaryFindPosition(DictionaryKey, DictionaryValue)(&dictionary->entries, key);
  return ListAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position).tag == Option_Some;
}

static Option(DictionaryValue) DictionaryAt(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) const* dictionary,
  DictionaryKey key
) {
  auto position = DictionaryFindPosition(DictionaryKey, DictionaryValue)(&dictionary->entries, key);
  auto entry = ListAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position);
  return entry.tag == Option_Some ? OptionSome(DictionaryValue)(entry.value._1) : OptionNone(DictionaryValue)();
}

static Option(Tuple(DictionaryKey, DictionaryValue)) DictionaryRemove(DictionaryKey, DictionaryValue)(
  Dictionary(DictionaryKey, DictionaryValue) * dictionary,
  DictionaryKey key
) {
  auto position = DictionaryFindPosition(DictionaryKey, DictionaryValue)(&dictionary->entries, key);
  auto entry = ListAt(Option(Tuple(DictionaryKey, DictionaryValue)))(&dictionary->entries, position);

  if (entry.tag == Option_Some) {
    ListSetAt(Option(Tuple(DictionaryKey, DictionaryValue)))(
      &dictionary->entries,
      position,
      OptionNone(Tuple(DictionaryKey, DictionaryValue))()
    );

    --dictionary->count;
  }

  return entry;
}

static void DictionaryDestroy(DictionaryKey, DictionaryValue)(Dictionary(DictionaryKey, DictionaryValue) dictionary) {
  ListDestroy(Option(Tuple(DictionaryKey, DictionaryValue)))(dictionary.entries);
  dictionary.count = 0;
}

#undef DictionaryKey
#undef DictionaryKeyHash
#undef DictionaryKeyEqual
#undef DictionaryValue
