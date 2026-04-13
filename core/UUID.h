#pragma once

#include <core/Core.h>
#include <core/String.h>

typedef struct {
  UInt8 bytes[16];
} UUID;

UUID UUIDDefault();

UUID UUIDCreateV4();

UUID UUIDCreateV7();

String UUIDToString(UUID const* uuid, Bool uppercase);

Bool UUIDEqual(UUID const* left, UUID const* right);

UInt UUIDHash(UUID const* uuid);
