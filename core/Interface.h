#pragma once

#include <core/Core.h>

#define interface(name, ...) \
  struct {                   \
    struct {                 \
      __VA_ARGS__            \
    }* interface;            \
    UInt8 self[];            \
  } name

#define implement(...) implement_i(__VA_ARGS__)

#define implement_i(interfaceName, typeName, ...)                                                                     \
  static interfaceName* typeName##_as_##interfaceName(typeName self) {                                                \
    static typeof(*(interfaceName){}.interface) interface = {__VA_ARGS__};                                            \
    auto obj                                              = (interfaceName*)malloc(sizeof(void*) + sizeof(typeName)); \
    obj->interface                                        = &interface;                                               \
    memcpy(obj->self, &self, sizeof(typeName));                                                                       \
    return obj;                                                                                                       \
  }

#define as(typeName, interfaceName) typeName##_as_##interfaceName
