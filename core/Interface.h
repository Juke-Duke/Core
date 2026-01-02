#pragma once

#include <core/Core.h>

#define interface(name, ...) \
  struct {                   \
    struct {                 \
      __VA_ARGS__            \
    }* interface;            \
    UInt8 self[];            \
  } name

#define implement(interfaceName, typeName, ...)                            \
  interfaceName* typeName##_as_##interfaceName(typeName self) {            \
    static typeof(*(interfaceName){}.interface) interface = {__VA_ARGS__}; \
    auto obj = (interfaceName*)malloc(sizeof(void*) + sizeof(typeName));   \
    obj->interface = &interface;                                           \
    memcpy(obj->self, &self, sizeof(typeName));                            \
    return obj;                                                            \
  }

#define as(typeName, interfaceName) typeName##_as_##interfaceName
