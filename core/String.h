#pragma once

#ifndef DISABLE_List_UInt8
#define ListElement UInt8
#include <core/collections/List.h>
#endif
#undef DISABLE_List_UInt8

typedef List(UInt8) String;

String StringDefault();

String StringCreate(char const* cString);

UInt StringCount(String const* string);

void StringAppend(String* string, Rune rune);

Array(UInt8) StringToBytes(String const* string);

void StringDestroy(String string);
