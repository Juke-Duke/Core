#include <core/Hash.h>
#include <core/UUID.h>
#include <stdio.h>

#define VERSION_MASK 0xF0
#define VERSION_4 0x40
#define VERSION_7 0x70

#define VARIANT_MASK 0xC0
#define VARIANT_VALUE 0x80

UUID UUIDDefault() {
  return (UUID){
    .bytes = {},
  };
}

UUID UUIDCreateV4() {
  auto uuid = (UUID){};

  FillRandomBytes((UInt8*)&uuid.bytes, 16);

  uuid.bytes[6] = (uuid.bytes[6] & ~VERSION_MASK) | VERSION_4;     // Set version to 4
  uuid.bytes[8] = (uuid.bytes[8] & ~VARIANT_MASK) | VARIANT_VALUE; // Set variant

  return uuid;
}

UUID UUIDCreateV7() {
  auto uuid = (UUID){};

  // First 48 bits: Unix timestamp in milliseconds
  auto timestamp = GetCurrentTimeMs();
  uuid.bytes[0]  = (UInt8)((timestamp >> 40) & 0xFF);
  uuid.bytes[1]  = (UInt8)((timestamp >> 32) & 0xFF);
  uuid.bytes[2]  = (UInt8)((timestamp >> 24) & 0xFF);
  uuid.bytes[3]  = (UInt8)((timestamp >> 16) & 0xFF);
  uuid.bytes[4]  = (UInt8)((timestamp >> 8) & 0xFF);
  uuid.bytes[5]  = (UInt8)(timestamp & 0xFF);

  FillRandomBytes((UInt8*)&uuid.bytes[6], 10);

  uuid.bytes[6] = (uuid.bytes[6] & ~VERSION_MASK) | VERSION_7;     // Set version to 7
  uuid.bytes[8] = (uuid.bytes[8] & ~VARIANT_MASK) | VARIANT_VALUE; // Set variant

  return uuid;
}

String UUIDToString(UUID const* uuid, Bool isUppercase) {
  auto buffer = (char[37]){};
  auto format = isUppercase
                  ? "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X"
                  : "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x";

  snprintf(buffer, 37, format, uuid->bytes[0], uuid->bytes[1], uuid->bytes[2], uuid->bytes[3], uuid->bytes[4], uuid->bytes[5], uuid->bytes[6], uuid->bytes[7], uuid->bytes[8], uuid->bytes[9], uuid->bytes[10], uuid->bytes[11], uuid->bytes[12], uuid->bytes[13], uuid->bytes[14], uuid->bytes[15]);

  return StringCreate(buffer);
}

UInt UUIDVersion(UUID const* uuid) {
  return (uuid->bytes[6] & VERSION_MASK) >> 4;
}

UInt UUIDVariant(UUID const* uuid) {
  return (uuid->bytes[8] & VARIANT_MASK) >> 6;
}

Bool UUIDEqual(UUID const* left, UUID const* right) {
  for (auto i = 0; i < 16; ++i) {
    if (left->bytes[i] != right->bytes[i]) {
      return false;
    }
  }

  return true;
}

UInt UUIDHash(UUID const* uuid) {
  auto a = (UInt64)0;
  auto b = (UInt64)0;

  for (auto i = 0; i < 8; ++i) {
    a |= (UInt64)uuid->bytes[i] << (i * 8);
  }

  for (auto i = 0; i < 8; ++i) {
    b |= (UInt64)uuid->bytes[i + 8] << (i * 8);
  }

  return a ^ b;
}
