#include <core/String.h>
#include <stdlib.h>
#include <string.h>

#define OPTION_IMPLEMENTATION
#define OptionValue Rune
#include <core/Option.h>

#define CURSOR_IMPLEMENTATION
#define CursorElement Rune
#include <core/collections/cursors/Cursor.h>

#define OPTION_IMPLEMENTATION
#define OptionValue Ref(UInt8)
#include <core/Option.h>

#define CURSOR_IMPLEMENTATION
#define CursorElement Ref(UInt8)
#include <core/collections/cursors/Cursor.h>

#define ARRAY_IMPLEMENTATION
#define ArrayElement UInt8
#include <core/collections/Array.h>

#define LIST_IMPLEMENTATION
#define ListElement UInt8
#include <core/collections/List.h>

String StringDefault() {
  return (String){
    .bytes = ListDefault(UInt8)(),
  };
}

String StringCreate(char const cString[]) {
  auto string = StringCreateWithCapacity(strlen(cString));
  StringAppendCString(&string, cString);
  return string;
}

String StringCreateWithCapacity(UInt capacity) {
  return (String){
    .bytes = ListCreateWithCapacity(UInt8)(capacity),
  };
}

UInt StringCountBytes(String const* string) {
  return ListCount(UInt8)(&string->bytes);
}

static UInt RuneToUTF8(Rune rune, UInt8 utf8[4]) {
  if (rune <= 0x7F) {
    utf8[0] = rune;
    return 1;
  }
  else if (rune <= 0x7FF) {
    utf8[0] = 0xC0 | (rune >> 6);
    utf8[1] = 0x80 | (rune & 0x3F);
    return 2;
  }
  else if (rune <= 0xFFFF) {
    utf8[0] = 0xE0 | (rune >> 12);
    utf8[1] = 0x80 | ((rune >> 6) & 0x3F);
    utf8[2] = 0x80 | (rune & 0x3F);
    return 3;
  }
  else if (rune <= 0x10FFFF) {
    utf8[0] = 0xF0 | (rune >> 18);
    utf8[1] = 0x80 | ((rune >> 12) & 0x3F);
    utf8[2] = 0x80 | ((rune >> 6) & 0x3F);
    utf8[3] = 0x80 | (rune & 0x3F);
    return 4;
  }

  return 0;
}

void StringAppend(String* string, Rune rune) {
  auto bytes = (UInt8[4]){};
  auto count = RuneToUTF8(rune, bytes);

  for (auto i = (UInt)0; i < count; ++i) {
    ListAppend(UInt8)(&string->bytes, bytes[i]);
  }
}

void StringAppendCString(String* string, char const cString[]) {
  for (; *cString != '\0'; ++cString) {
    ListAppend(UInt8)(&string->bytes, *cString);
  }
}

void StringAppendString(String* string, String const* other) {
  for (auto i = (UInt)0; i < StringCountBytes(other); ++i) {
    ListAppend(UInt8)(&string->bytes, *ListAt(UInt8)(&other->bytes, i));
  }
}

char* StringToCString(String const* string) {
  auto cString = (char*)malloc(StringCountBytes(string) + 1);

  memcpy(cString, string->bytes.elements.elements, StringCountBytes(string));
  cString[StringCountBytes(string)] = '\0';

  return cString;
}

Bool StringEqual(String const* left, String const* right) {
  if (StringCountBytes(left) != StringCountBytes(right)) {
    return false;
  }

  for (auto i = (UInt)0; i < StringCountBytes(left); ++i) {
    if (*ListAt(UInt8)(&left->bytes, i) != *ListAt(UInt8)(&right->bytes, i)) {
      return false;
    }
  }

  return true;
}

UInt StringHash(String const* string) {
  auto hash = 14695981039346656037ULL; // FNV offset basis

  for (auto i = (UInt)0; i < StringCountBytes(string); ++i) {
    hash ^= *ListAt(UInt8)(&string->bytes, i);
    hash *= 1099511628211ULL; // FNV prime
  }

  return (UInt)hash;
}

Array(UInt8) StringToBytes(String const* string) {
  auto bytes = ArrayCreateWithCapacity(UInt8)(StringCountBytes(string));

  for (auto i = (UInt)0; i < StringCountBytes(string); ++i) {
    *ArrayAtMut(UInt8)(&bytes, i) = *ListAt(UInt8)(&string->bytes, i);
  }

  return bytes;
}

ListCursor(UInt8) StringBytesCursorCreate(String const* string) {
  return ListCursorCreate(UInt8)(&string->bytes);
}

String StringClone(String const* string) {
  return (String){
    .bytes = ListClone(UInt8)(&string->bytes),
  };
}

void StringDestroy(String* string) {
  ListDestroy(UInt8)(&string->bytes);
}

StringCursor StringCursorCreate(String const* string) {
  return (StringCursor){
    .string = string,
    .index  = 0,
  };
}

Option(Rune) StringCursorNext(StringCursor* cursor) {
  if (cursor->index == StringCountBytes(cursor->string)) {
    return OptionNone(Rune)();
  }

  auto rune = (Rune){};

  if ((*ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x80) == 0) {
    rune = *ListAt(UInt8)(&cursor->string->bytes, cursor->index);
    cursor->index += 1;
  }
  else if ((*ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0xE0) == 0xC0) {
    rune = (*ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x1F) << 6;
    rune |= *ListAt(UInt8)(&cursor->string->bytes, cursor->index + 1) & 0x3F;
    cursor->index += 2;
  }
  else if ((*(ListAt(UInt8)(&cursor->string->bytes, cursor->index)) & 0xF0) == 0xE0) {
    rune = (*ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x0F) << 12;
    rune |= (*ListAt(UInt8)(&cursor->string->bytes, cursor->index + 1) & 0x3F) << 6;
    rune |= *ListAt(UInt8)(&cursor->string->bytes, cursor->index + 2) & 0x3F;
    cursor->index += 3;
  }
  else if ((*(ListAt(UInt8)(&cursor->string->bytes, cursor->index)) & 0xF8) == 0xF0) {
    rune = (*ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x07) << 18;
    rune |= (*ListAt(UInt8)(&cursor->string->bytes, cursor->index + 1) & 0x3F) << 12;
    rune |= (*ListAt(UInt8)(&cursor->string->bytes, cursor->index + 2) & 0x3F) << 6;
    rune |= *ListAt(UInt8)(&cursor->string->bytes, cursor->index + 3) & 0x3F;
    cursor->index += 4;
  }

  return OptionSome(Rune)(rune);
}

Option(Rune) StringCursorPeek(StringCursor* cursor) {
  if (cursor->index == StringCountBytes(cursor->string)) {
    return OptionNone(Rune)();
  }

  auto rune = (Rune){};

  if ((*ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x80) == 0) {
    rune = *ListAt(UInt8)(&cursor->string->bytes, cursor->index);
  }
  else if ((*ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0xE0) == 0xC0) {
    rune = (*ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x1F) << 6;
    rune |= *ListAt(UInt8)(&cursor->string->bytes, cursor->index + 1) & 0x3F;
  }
  else if ((*(ListAt(UInt8)(&cursor->string->bytes, cursor->index)) & 0xF0) == 0xE0) {
    rune = (*ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x0F) << 12;
    rune |= (*ListAt(UInt8)(&cursor->string->bytes, cursor->index + 1) & 0x3F) << 6;
    rune |= *ListAt(UInt8)(&cursor->string->bytes, cursor->index + 2) & 0x3F;
  }
  else if ((*(ListAt(UInt8)(&cursor->string->bytes, cursor->index)) & 0xF8) == 0xF0) {
    rune = (*ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x07) << 18;
    rune |= (*ListAt(UInt8)(&cursor->string->bytes, cursor->index + 1) & 0x3F) << 12;
    rune |= (*ListAt(UInt8)(&cursor->string->bytes, cursor->index + 2) & 0x3F) << 6;
    rune |= *ListAt(UInt8)(&cursor->string->bytes, cursor->index + 3) & 0x3F;
  }

  return OptionSome(Rune)(rune);
}

StringCursor StringCursorClone(StringCursor const* cursor) {
  return (StringCursor){
    .string = cursor->string,
    .index  = cursor->index,
  };
}

void StringCursorDestroy(StringCursor* cursor) {
  cursor->index = 0;
}

IMPLEMENT(
  StringCursor,
  Cursor(Rune),
  .Next    = (void*)StringCursorNext,
  .Destroy = (void*)StringCursorDestroy
);
