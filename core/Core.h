#pragma once

#include <stdint.h>

#define null nullptr

typedef struct Unit {
} Unit;

typedef bool Bool;

typedef uint8_t Char;
typedef uint32_t Rune;

typedef uint8_t UInt8;
typedef int8_t Int8;

typedef uint16_t UInt16;
typedef int16_t Int16;

typedef uint32_t UInt32;
typedef int32_t Int32;

typedef uint64_t UInt64;
typedef int64_t Int64;

typedef uintptr_t UInt;
typedef intptr_t Int;

typedef float Float32;
typedef double Float64;

#define nameof(x) _nameof(x)
#define _nameof(x) #x

#define MACRO_OVERLOAD(Name, ...) _MACRO_OVERLOAD(Name, COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)
#define _MACRO_OVERLOAD(a, b) __MACRO_OVERLOAD(a, b)
#define __MACRO_OVERLOAD(a, b) a##b
#define COUNT_ARGS(...) NTH_ARG(__VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, N, ...) N

#define GET_ARG(i, ...) CONCAT(GET_ARG, i)(__VA_ARGS__)
#define GET_ARG1(x, ...) x
#define GET_ARG2(x, ...) GET_ARG1(__VA_ARGS__)
#define GET_ARG3(x, ...) GET_ARG2(__VA_ARGS__)
#define GET_ARG4(x, ...) GET_ARG3(__VA_ARGS__)
#define GET_ARG5(x, ...) GET_ARG4(__VA_ARGS__)
#define GET_ARG6(x, ...) GET_ARG5(__VA_ARGS__)
#define GET_ARG7(x, ...) GET_ARG6(__VA_ARGS__)
#define GET_ARG8(x, ...) GET_ARG7(__VA_ARGS__)

#define CONCAT(...) MACRO_OVERLOAD(CONCAT, __VA_ARGS__)
#define CONCAT2(a, b) a##b
#define CONCAT3(a, b, c) a##b##c
#define CONCAT4(a, b, c, d) a##b##c##d
#define CONCAT5(a, b, c, d, e) a##b##c##d##e
#define CONCAT6(a, b, c, d, e, f) a##b##c##d##e##f
#define CONCAT7(a, b, c, d, e, f, g) a##b##c##d##e##f##g
#define CONCAT8(a, b, c, d, e, f, g, h) a##b##c##d##e##f##g##h

#define GENERIC(...) MACRO_OVERLOAD(GENERIC, __VA_ARGS__)
#define GENERIC2(Name, T) Name##_##T
#define GENERIC3(Name, T1, T2) Name##_##T1##_##T2
#define GENERIC4(Name, T1, T2, T3) Name##_##T1##_##T2##_##T3
#define GENERIC5(Name, T1, T2, T3, T4) Name##_##T1##_##T2##_##T3##_##T4
#define GENERIC6(Name, T1, T2, T3, T4, T5) Name##_##T1##_##T2##_##T3##_##T4##_##T5
#define GENERIC7(Name, T1, T2, T3, T4, T5, T6) Name##_##T1##_##T2##_##T3##_##T4##_##T5##_##T6
#define GENERIC8(Name, T1, T2, T3, T4, T5, T6, T7) Name##_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7
#define GENERIC9(Name, T1, T2, T3, T4, T5, T6, T7, T8) Name##_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8

#define interface(Interface, ...)              \
  struct Interface {                           \
    struct CONCAT(Interface, DispatchTable) {  \
      __VA_ARGS__                              \
      struct Interface* (*Clone)(void const*); \
      void (*Destroy)(void*);                  \
    }* vTable;                                 \
    UInt8 self[];                              \
  }

#define implement(Type, Interface, ...)                                       \
  Interface* as(Type, Interface)(Type self);                                  \
                                                                              \
  static Interface* CONCAT(Interface, CloneFrom, Type)(Type const* self) {    \
    return as(Type, Interface)(CONCAT(Type, Clone)(self));                    \
  }                                                                           \
                                                                              \
  Interface* as(Type, Interface)(Type self) {                                 \
    static typeof(*(Interface){}.vTable) vTable = {                           \
      .Clone   = (void*)CONCAT(Interface, CloneFrom, Type),                   \
      .Destroy = (void*)CONCAT(Type, Destroy),                                \
      __VA_ARGS__                                                             \
    };                                                                        \
    auto interface    = (Interface*)malloc(sizeof(Interface) + sizeof(Type)); \
    interface->vTable = &vTable;                                              \
    memcpy(interface->self, &self, sizeof(Type));                             \
    return interface;                                                         \
  }

#define InterfaceDispatch(Function, interface, ...) ((interface)->vTable->Function((interface)->self __VA_OPT__(, ) __VA_ARGS__))

#define as(Type, Interface) CONCAT(Type, As, Interface)
