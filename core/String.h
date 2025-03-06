#pragma once

#ifndef DISABLE_List_UInt8
#define ListElement UInt8
#include <core/collections/List.h>
#endif
#undef DISABLE_List_UInt8

#ifndef DISABLE_Cursor_Rune
#define CursorElement Rune
#include <core/collections/Cursor.h>
#endif
#undef DISABLE_Cursor_Rune

typedef struct {
  List(UInt8) bytes;
} String;

String StringDefault();

String StringCreate(char const* cString);

UInt StringCountBytes(String const* string);

void StringAppend(String* string, Rune rune);

void StringAppendCString(String* string, char const* cString);

void StringAppendString(String* string, String const* other);

Bool StringEqual(String const* a, String const* b);

ListCursor(UInt8) StringBytesCursorCreate(String* string);

void StringDestroy(String string);

typedef struct {
  String* string;
  UInt index;
} StringCursor;

StringCursor StringCursorCreate(String* string);

Option(Rune) StringCursorNext(StringCursor* cursor);

Cursor(Rune) StringCursor_as_Cursor(StringCursor* cursor);
