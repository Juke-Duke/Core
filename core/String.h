#pragma once

#define ListElement UInt8
#include <core/collections/List.h>

#define CursorElement Rune
#include <core/collections/Cursor.h>

typedef struct String {
  List(UInt8) bytes;
} String;

String StringDefault();
String StringCreate(char const* cString);
UInt StringCountBytes(String const* string);
void StringAppend(String* string, Rune rune);
void StringAppendCString(String* string, char const* cString);
void StringAppendString(String* string, String const* other);
char* StringToCString(String const* string);
Bool StringEqual(String const* a, String const* b);
UInt StringHash(String const* string);
ListCursor(UInt8) StringBytesCursorCreate(String const* string);
String StringClone(String const* string);
void StringDestroy(String* string);

typedef struct StringCursor {
  String const* string;
  UInt index;
} StringCursor;

StringCursor StringCursorCreate(String const* string);
Option(Ref(Rune)) StringCursorNext(StringCursor* cursor);
Option(Ref(Rune)) StringCursorPeek(StringCursor* cursor);
