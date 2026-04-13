#include <core/String.h>
#include <core/UUID.h>
#include <stdio.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <bcrypt.h>
#else
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#endif

static UInt64 GetCurrentTimeMs() {
#ifdef _WIN32
  auto fs = (FILETIME){};
  GetSystemTimeAsFileTime(&fs);
  auto time = ((UInt64)fs.dwHighDateTime << 32) | fs.dwLowDateTime;
  return time / 10000ULL - 11644473600000ULL;
#else
  auto ts = (struct timespec){};
  clock_gettime(CLOCK_REALTIME, &ts);
  return (UInt64)ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL;
#endif
}

static void GetRandomBytes(UInt8* buffer, size_t count) {
#ifdef _WIN32
  BCryptGenRandom(null, buffer, (ULONG)count, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
#else
  auto fd = open("/dev/urandom", O_RDONLY);
  read(fd, buffer, count);
  close(fd);
#endif
}

UUID UUIDDefault() {
  return (UUID){
    .bytes = {0},
  };
}

UUID UUIDCreateV4() {
  auto uuid = (UUID){};

  GetRandomBytes((UInt8*)&uuid.bytes, 16);

  uuid.bytes[6] = (uuid.bytes[6] & 0x0F) | 0x40; // Set version to 4
  uuid.bytes[8] = (uuid.bytes[8] & 0x3F) | 0x80; // Set variant to 2

  return uuid;
}

UUID UUIDCreateV7() {
  auto uuid = (UUID){};

  // First 48 bits: Unix timestamp in milliseconds
  auto timestamp = GetCurrentTimeMs();
  uuid.bytes[0] = (UInt8)((timestamp >> 40) & 0xFF);
  uuid.bytes[1] = (UInt8)((timestamp >> 32) & 0xFF);
  uuid.bytes[2] = (UInt8)((timestamp >> 24) & 0xFF);
  uuid.bytes[3] = (UInt8)((timestamp >> 16) & 0xFF);
  uuid.bytes[4] = (UInt8)((timestamp >> 8) & 0xFF);
  uuid.bytes[5] = (UInt8)(timestamp & 0xFF);

  GetRandomBytes((UInt8*)&uuid.bytes[6], 10);

  uuid.bytes[6] = (uuid.bytes[6] & 0x0F) | 0x70; // Set version to 7
  uuid.bytes[8] = (uuid.bytes[8] & 0x3F) | 0x80; // Set variant to 2

  return uuid;
}

String UUIDToString(UUID const* uuid, Bool uppercase) {
  auto buffer = (char[37]){};
  auto format = uppercase
                  ? "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X"
                  : "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x";

  snprintf(buffer, 37, format, uuid->bytes[0], uuid->bytes[1], uuid->bytes[2], uuid->bytes[3], uuid->bytes[4], uuid->bytes[5], uuid->bytes[6], uuid->bytes[7], uuid->bytes[8], uuid->bytes[9], uuid->bytes[10], uuid->bytes[11], uuid->bytes[12], uuid->bytes[13], uuid->bytes[14], uuid->bytes[15]);

  return StringCreate(buffer);
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
  auto a = 0ULL;
  auto b = 0ULL;

  for (auto i = (UInt)0; i < 8; ++i) {
    a |= (UInt64)uuid->bytes[i] << (i * 8);
  }

  for (auto i = (UInt)0; i < 8; ++i) {
    b |= (UInt64)uuid->bytes[i + 8] << (i * 8);
  }

  return a ^ b;
}
