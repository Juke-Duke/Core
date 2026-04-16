#pragma once

#include <core/Core.h>

#define interface(name, ...) \
  struct name {              \
    struct {                 \
      __VA_ARGS__            \
    }* vTable;               \
    UInt8 self[];            \
  } name

#define implement(...) _implement(__VA_ARGS__)

#define _implement(Interface, Type, ...)                                                            \
  static Interface* Type##_as_##Interface(Type self) {                                              \
    static typeof(*(Interface){}.vTable) vTable = {__VA_ARGS__};                                    \
    auto interface                              = (Interface*)malloc(sizeof(void*) + sizeof(Type)); \
    interface->vTable                           = &vTable;                                          \
    memcpy(interface->self, &self, sizeof(Type));                                                   \
    return interface;                                                                               \
  }

#define as(Type, Interface) Type##_as_##Interface
