#pragma once

#include <core/Core.h>

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
