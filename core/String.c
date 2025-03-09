#include <core/String.h>

String StringDefault() {
  return (String){
    .bytes = ListDefault(UInt8)(),
  };
}

String StringCreate(char const* cString) {
  var string = StringDefault();

  StringAppendCString(&string, cString);

  return string;
}

UInt StringCountBytes(String const* string) {
  return ListCount(UInt8)(&string->bytes);
}

UInt RuneToUTF8(Rune rune, UInt8 utf8[4]) {
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
  var bytes = (UInt8[4]){};
  var count = RuneToUTF8(rune, bytes);

  for (var i = 0; i < count; ++i) {
    ListAppend(UInt8)(&string->bytes, bytes[i]);
  }
}

void StringAppendCString(String* string, char const* cString) {
  for (; *cString; ++cString) {
    ListAppend(UInt8)(&string->bytes, *cString);
  }
}

void StringAppendString(String* string, String const* other) {
  for (var i = 0; i < StringCountBytes(other); ++i) {
    ListAppend(UInt8)(&string->bytes, ListAt(UInt8)(&other->bytes, i));
  }
}

Bool StringEqual(String const* a, String const* b) {
  if (StringCountBytes(a) != StringCountBytes(b)) {
    return false;
  }

  for (var i = 0; i < StringCountBytes(a); ++i) {
    if (ListAt(UInt8)(&a->bytes, i) != ListAt(UInt8)(&b->bytes, i)) {
      return false;
    }
  }

  return true;
}

UInt StringHash(String const* string) {
  var hash = (UInt)5381;

  for (var i = 0; i < StringCountBytes(string); ++i) {
    hash = hash * 33 ^ ListAt(UInt8)(&string->bytes, i);
  }

  return hash;
}

ListCursor(UInt8) StringBytesCursorCreate(String* string) {
  return ListCursorCreate(UInt8)(&string->bytes);
}

void StringDestroy(String string) {
  ListDestroy(UInt8)(string.bytes);
}

StringCursor StringCursorCreate(String const* string) {
  return (StringCursor){
    .string = string,
    .index = 0,
  };
}

Option(Rune) StringCursorNext(StringCursor* cursor) {
  if (cursor->index == StringCountBytes(cursor->string)) {
    return OptionNone(Rune)();
  }

  var rune = (Rune){};

  if ((ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x80) == 0) {
    rune = ListAt(UInt8)(&cursor->string->bytes, cursor->index);
    cursor->index += 1;
  }
  else if ((ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0xE0) == 0xC0) {
    rune = (ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x1F) << 6;
    rune |= ListAt(UInt8)(&cursor->string->bytes, cursor->index + 1) & 0x3F;
    cursor->index += 2;
  }
  else if ((ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0xF0) == 0xE0) {
    rune = (ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x0F) << 12;
    rune |= (ListAt(UInt8)(&cursor->string->bytes, cursor->index + 1) & 0x3F) << 6;
    rune |= ListAt(UInt8)(&cursor->string->bytes, cursor->index + 2) & 0x3F;
    cursor->index += 3;
  }
  else if ((ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0xF8) == 0xF0) {
    rune = (ListAt(UInt8)(&cursor->string->bytes, cursor->index) & 0x07) << 18;
    rune |= (ListAt(UInt8)(&cursor->string->bytes, cursor->index + 1) & 0x3F) << 12;
    rune |= (ListAt(UInt8)(&cursor->string->bytes, cursor->index + 2) & 0x3F) << 6;
    rune |= ListAt(UInt8)(&cursor->string->bytes, cursor->index + 3) & 0x3F;
    cursor->index += 4;
  }

  return OptionSome(Rune)(rune);
}

Cursor(Rune) StringCursor_as_Cursor(StringCursor* cursor) {
  static typeof(*(Cursor(Rune)){}.interface) interface = {
    .Next = (void*)StringCursorNext,
  };

  return (Cursor(Rune)){
    .self = cursor,
    .interface = &interface,
  };
}
