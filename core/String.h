#pragma once

#define RefT UInt8
#include <core/Ref.h>

#define OptionValue Rune
#include <core/Option.h>

#define CursorElement Rune
#include <core/collections/cursors/Cursor.h>

#define OptionValue Ref(UInt8)
#include <core/Option.h>

#define CursorElement Ref(UInt8)
#include <core/collections/cursors/Cursor.h>

#define ArrayElement UInt8
#include <core/collections/Array.h>

#define ListElement UInt8
#include <core/collections/List.h>

typedef struct String {
  List(UInt8) bytes;
} String;

String StringDefault();
String StringCreate(char const cString[]);
String StringCreateWithCapacity(UInt capacity);
UInt StringCountBytes(String const* string);
void StringAppend(String* string, Rune rune);
void StringAppendCString(String* string, char const cString[]);
void StringAppendString(String* string, String const* other);
char* StringToCString(String const* string);
Bool StringEqual(String const* left, String const* right);
UInt StringHash(String const* string);
ListCursor(UInt8) StringBytesCursorCreate(String const* string);
String StringClone(String const* string);
void StringDestroy(String* string);

typedef struct StringCursor {
  String const* string;
  UInt index;
} StringCursor;

StringCursor StringCursorCreate(String const* string);
Option(Rune) StringCursorNext(StringCursor* cursor);
Option(Rune) StringCursorPeek(StringCursor* cursor);
StringCursor StringCursorClone(StringCursor const* cursor);
void StringCursorDestroy(StringCursor* cursor);
IMPLEMENT_SIG(StringCursor, Cursor(Rune));
