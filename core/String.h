#pragma once

#define ListElement UInt8
#include <core/collections/List.h>

typedef struct {
  List(UInt8) utf8;
} String;

String StringDefault();

String StringCreate(char const* cString);

UInt StringCount(String const* string);

void StringAppend(String* string, Rune rune);

Array(UInt8) StringToBytes(String const* string);

void StringDestroy(String string);
