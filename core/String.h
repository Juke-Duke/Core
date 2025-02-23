#pragma once

#ifndef DISABLE_List_UInt8
#define ListElement UInt8
#include <core/collections/List.h>
#endif
#undef DISABLE_List_UInt8

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

Array(UInt8) StringToBytes(String const* string);

void StringDestroy(String string);
