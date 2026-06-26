#pragma once

#include <core/Core.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <bcrypt.h>
#else
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#endif

#define IsEven(num) ((num & 1) == 0)

static Bool IsPrime(UInt num) {
  if (num == 2 || num == 3) {
    return true;
  }

  if (num == 1 || IsEven(num)) {
    return false;
  }

  for (auto divisor = 3UL; divisor * divisor <= num; divisor += 2) {
    if (num % divisor == 0) {
      return false;
    }
  }

  return true;
}

static UInt NextPrime(UInt num) {
  if (IsEven(num)) {
    ++num;
  }

  while (!IsPrime(num)) {
    num += 2;
  }

  return num;
}

static UInt NextPowerOfTwo(UInt num) {
  if (num == 0) {
    return 1;
  }

  --num;
  num |= num >> 1;
  num |= num >> 2;
  num |= num >> 4;
  num |= num >> 8;
  num |= num >> 16;
#if UINTPTR_MAX == UINT64_MAX
  num |= num >> 32;
#endif

  return num + 1;
}

static void FillRandomBytes(UInt8* buffer, size_t count) {
#ifdef _WIN32
  BCryptGenRandom(null, buffer, (ULONG)count, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
#else
  auto fd = open("/dev/urandom", O_RDONLY);
  read(fd, buffer, count);
  close(fd);
#endif
}

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
