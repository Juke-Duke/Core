#include <core/String.h>

String StringDefault() {
  return ListDefault(UInt8)();
}

String StringCreate(char const* cString) {
  var string = StringDefault();

  for (; *cString; ++cString) {
    ListAppend(UInt8)(&string, *cString);
  }

  return string;
}

UInt StringCount(String const* string) {
  return ListCount(UInt8)(string);
}

int RuneToUTF8(Rune rune, UInt8* utf8) {
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
  var utf8 = (UInt8[4]){};
  var count = RuneToUTF8(rune, utf8);

  for (var i = 0; i < count; ++i) {
    ListAppend(UInt8)(string, utf8[i]);
  }
}

Array(UInt8) StringToBytes(String const* string) {
  var bytes = ArrayCreateWithCapacity(UInt8)(StringCount(string));

  for (var i = 0; i < StringCount(string); ++i) {
    ArraySetAt(UInt8)(&bytes, i, ListAt(UInt8)(string, i));
  }

  return bytes;
}

void StringDestroy(String string) {
  ListDestroy(UInt8)(string);
}
