#pragma once

#include <stdint.h>
#include <stdlib.h>

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

#define return_unit return ((Unit){})

#define nameof(x) _nameof(x)
#define _nameof(x) #x

static inline Unit DefaultDestroy(void* self) {
  (void)self;
  return_unit;
}

#if defined(_MSC_VER)
#define COREAPI __declspec(selectany)
#else
#define COREAPI __attribute__((weak))
#endif

#define UNPACK(...) __VA_ARGS__

#define MACRO_OVERLOAD(Name, ...) _MACRO_OVERLOAD(Name, COUNT_ARGS(__VA_ARGS__))
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
#define GET_ARG9(x, ...) GET_ARG8(__VA_ARGS__)

#define SHIFT_ARG(i, ...) CONCAT(SHIFT_ARG, i)(__VA_ARGS__)
#define SHIFT_ARG1(x, ...) __VA_ARGS__
#define SHIFT_ARG2(x, ...) SHIFT_ARG1(__VA_ARGS__)
#define SHIFT_ARG3(x, ...) SHIFT_ARG2(__VA_ARGS__)
#define SHIFT_ARG4(x, ...) SHIFT_ARG3(__VA_ARGS__)
#define SHIFT_ARG5(x, ...) SHIFT_ARG4(__VA_ARGS__)
#define SHIFT_ARG6(x, ...) SHIFT_ARG5(__VA_ARGS__)
#define SHIFT_ARG7(x, ...) SHIFT_ARG6(__VA_ARGS__)
#define SHIFT_ARG8(x, ...) SHIFT_ARG7(__VA_ARGS__)

#define EACH(F, ...) MACRO_OVERLOAD(EACH, __VA_ARGS__)(F, __VA_ARGS__)
#define EACH1(F, _1) F(_1)
#define EACH2(F, _1, _2) F(_1) F(_2)
#define EACH3(F, _1, _2, _3) F(_1) F(_2) F(_3)
#define EACH4(F, _1, _2, _3, _4) F(_1) F(_2) F(_3) F(_4)
#define EACH5(F, _1, _2, _3, _4, _5) F(_1) F(_2) F(_3) F(_4) F(_5)
#define EACH6(F, _1, _2, _3, _4, _5, _6) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6)
#define EACH7(F, _1, _2, _3, _4, _5, _6, _7) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7)
#define EACH8(F, _1, _2, _3, _4, _5, _6, _7, _8) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8)
#define EACH9(F, _1, _2, _3, _4, _5, _6, _7, _8, _9) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9)
#define EACH10(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10)
#define EACH11(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10) F(_11)
#define EACH12(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10) F(_11) F(_12)
#define EACH13(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10) F(_11) F(_12) F(_13)
#define EACH14(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10) F(_11) F(_12) F(_13) F(_14)
#define EACH15(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10) F(_11) F(_12) F(_13) F(_14) F(_15)
#define EACH16(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10) F(_11) F(_12) F(_13) F(_14) F(_15) F(_16)
#define EACH17(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10) F(_11) F(_12) F(_13) F(_14) F(_15) F(_16) F(_17)
#define EACH18(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10) F(_11) F(_12) F(_13) F(_14) F(_15) F(_16) F(_17) F(_18)
#define EACH19(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10) F(_11) F(_12) F(_13) F(_14) F(_15) F(_16) F(_17) F(_18) F(_19)
#define EACH20(F, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) F(_1) F(_2) F(_3) F(_4) F(_5) F(_6) F(_7) F(_8) F(_9) F(_10) F(_11) F(_12) F(_13) F(_14) F(_15) F(_16) F(_17) F(_18) F(_19) F(_20)

#define REMOVE_LAST_COMMA(...) MACRO_OVERLOAD(REMOVE_LAST_COMMA, __VA_ARGS__)(__VA_ARGS__)
#define REMOVE_LAST_COMMA1(_1)
#define REMOVE_LAST_COMMA2(_1, _2) _1
#define REMOVE_LAST_COMMA3(_1, _2, _3) _1, _2
#define REMOVE_LAST_COMMA4(_1, _2, _3, _4) _1, _2, _3
#define REMOVE_LAST_COMMA5(_1, _2, _3, _4, _5) _1, _2, _3, _4
#define REMOVE_LAST_COMMA6(_1, _2, _3, _4, _5, _6) _1, _2, _3, _4, _5
#define REMOVE_LAST_COMMA7(_1, _2, _3, _4, _5, _6, _7) _1, _2, _3, _4, _5, _6
#define REMOVE_LAST_COMMA8(_1, _2, _3, _4, _5, _6, _7, _8) _1, _2, _3, _4, _5, _6, _7
#define REMOVE_LAST_COMMA9(_1, _2, _3, _4, _5, _6, _7, _8, _9) _1, _2, _3, _4, _5, _6, _7, _8
#define REMOVE_LAST_COMMA10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) _1, _2, _3, _4, _5, _6, _7, _8, _9
#define REMOVE_LAST_COMMA11(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) _1, _2, _3, _4, _5, _6, _7, _8, _9, _10
#define REMOVE_LAST_COMMA12(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11
#define REMOVE_LAST_COMMA13(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12
#define REMOVE_LAST_COMMA14(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13
#define REMOVE_LAST_COMMA15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14
#define REMOVE_LAST_COMMA16(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15
#define REMOVE_LAST_COMMA17(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16
#define REMOVE_LAST_COMMA18(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17
#define REMOVE_LAST_COMMA19(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18
#define REMOVE_LAST_COMMA20(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20) _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19

#define CONCAT(...) MACRO_OVERLOAD(CONCAT, __VA_ARGS__)(__VA_ARGS__)
#define CONCAT2(a, b) a##b
#define CONCAT3(a, b, c) a##b##c
#define CONCAT4(a, b, c, d) a##b##c##d
#define CONCAT5(a, b, c, d, e) a##b##c##d##e
#define CONCAT6(a, b, c, d, e, f) a##b##c##d##e##f
#define CONCAT7(a, b, c, d, e, f, g) a##b##c##d##e##f##g
#define CONCAT8(a, b, c, d, e, f, g, h) a##b##c##d##e##f##g##h

#define GENERIC(Name, ...) MACRO_OVERLOAD(GENERIC, __VA_ARGS__)(Name, __VA_ARGS__)
#define GENERIC1(Name, T) Name##_##T
#define GENERIC2(Name, T1, T2) Name##_##T1##_##T2
#define GENERIC3(Name, T1, T2, T3) Name##_##T1##_##T2##_##T3
#define GENERIC4(Name, T1, T2, T3, T4) Name##_##T1##_##T2##_##T3##_##T4
#define GENERIC5(Name, T1, T2, T3, T4, T5) Name##_##T1##_##T2##_##T3##_##T4##_##T5
#define GENERIC6(Name, T1, T2, T3, T4, T5, T6) Name##_##T1##_##T2##_##T3##_##T4##_##T5##_##T6
#define GENERIC7(Name, T1, T2, T3, T4, T5, T6, T7) Name##_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7
#define GENERIC8(Name, T1, T2, T3, T4, T5, T6, T7, T8) Name##_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8
#define GENERIC9(Name, T1, T2, T3, T4, T5, T6, T7, T8, T9) Name##_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8##_##T9

#define union(TagName, ...)            \
  {                                    \
    enum TagName {                     \
      EACH(UNION_TAG, __VA_ARGS__)     \
    } __tag;                           \
    union {                            \
      EACH(UNION_VARIANT, __VA_ARGS__) \
    };                                 \
  }

#define UNION_TAG(tuple) _UNION_TAG tuple
#define _UNION_TAG(...) MACRO_OVERLOAD(_UNION_TAG, __VA_ARGS__)(__VA_ARGS__)
#define _UNION_TAG1(tag) tag,
#define _UNION_TAG2(tag, _) tag,

#define UNION_VARIANT(tuple) _UNION_VARIANT tuple
#define _UNION_VARIANT(...) MACRO_OVERLOAD(_UNION_VARIANT, __VA_ARGS__)(__VA_ARGS__)
#define _UNION_VARIANT1(tag)
#define _UNION_VARIANT2(tag, VariantType) VariantType tag;

#define VARIANT_CREATE_DECL(UnionType, FunctionName, tuple) _VARIANT_CREATE_DECL(UnionType, FunctionName, UNPACK tuple)
#define _VARIANT_CREATE_DECL(UnionType, FunctionName, ...) MACRO_OVERLOAD(_VARIANT_CREATE_DECL, __VA_ARGS__)(UnionType, FunctionName, __VA_ARGS__)
#define _VARIANT_CREATE_DECL1(UnionType, FunctionName, VariantName) UnionType FunctionName()
#define _VARIANT_CREATE_DECL2(UnionType, FunctionName, VariantName, VariantType) UnionType FunctionName(VariantType value)

#define VARIANT_CREATE_IMPL(UnionType, FunctionName, tuple) _VARIANT_CREATE_IMPL(UnionType, FunctionName, UNPACK tuple)
#define _VARIANT_CREATE_IMPL(UnionType, FunctionName, ...) MACRO_OVERLOAD(_VARIANT_CREATE_IMPL, __VA_ARGS__)(UnionType, FunctionName, __VA_ARGS__)
#define _VARIANT_CREATE_IMPL1(UnionType, FunctionName, VariantName) \
  _VARIANT_CREATE_DECL1(UnionType, FunctionName, VariantName) {     \
    return (UnionType){.__tag = VariantName};                       \
  }
#define _VARIANT_CREATE_IMPL2(UnionType, FunctionName, VariantName, VariantType) \
  _VARIANT_CREATE_DECL2(UnionType, FunctionName, VariantName, VariantType) {     \
    return (UnionType){.__tag = VariantName, .VariantName = value};              \
  }

#define is(UnionType, tag, VariableName)

#define match(union)                          \
  for (auto __union = (union);; ({ break; })) \
    switch (__union->__tag)

#define case(...) MACRO_OVERLOAD(case, __VA_ARGS__)(__VA_ARGS__)
#define case1(tag) \
  break;           \
  case tag:
#define case2(tag, VariableName) \
  break;                         \
  case tag:                      \
    auto VariableName = &__union->tag;

#define interface(...)             \
  {                                \
    struct {                       \
      __VA_ARGS__                  \
      Unit (*Destroy)(void* self); \
      UInt size;                   \
    }* dispatchTable;              \
    UInt8 self[];                  \
  }

#define IMPLEMENT_SIG(TypeName, InterfaceName) \
  Unit CONCAT(TypeName, As, InterfaceName)(TypeName * self, InterfaceName * interface)

#define IMPLEMENT(TypeName, InterfaceName, ...)                       \
  IMPLEMENT_SIG(TypeName, InterfaceName) {                            \
    static typeof(*(InterfaceName){}.dispatchTable) dispatchTable = { \
      .size = sizeof(TypeName),                                       \
      __VA_ARGS__                                                     \
    };                                                                \
    interface->dispatchTable    = &dispatchTable;                     \
    *(TypeName*)interface->self = *self;                              \
    return_unit;                                                      \
  }

#define DISPATCH_DECL(InterfaceName, ReturnType, FunctionName, mutability, ...)                       \
  ReturnType CONCAT(InterfaceName, FunctionName)(                                                     \
    InterfaceName mutability interface __VA_OPT__(, REMOVE_LAST_COMMA(EACH(PARAM_DECL, __VA_ARGS__))) \
  )

#define DISPATCH_IMPL(InterfaceName, ReturnType, FunctionName, mutability, ...)      \
  DISPATCH_DECL(InterfaceName, ReturnType, FunctionName, mutability, __VA_ARGS__) {  \
    return interface->dispatchTable->FunctionName(                                   \
      interface->self __VA_OPT__(, REMOVE_LAST_COMMA(EACH(PARAM_NAME, __VA_ARGS__))) \
    );                                                                               \
  }

#define PARAM_DECL(tuple) _PARAM_DECL tuple,
#define _PARAM_DECL(ParameterType, ParameterName) ParameterType ParameterName

#define PARAM_NAME(tuple) _PARAM_NAME tuple,
#define _PARAM_NAME(_, ParameterName) ParameterName

#define as(Type, InterfaceType, fromValue)                                       \
  ({                                                                             \
    auto value     = (fromValue);                                                \
    UInt size      = __builtin_types_compatible_p(typeof(value), InterfaceType*) \
                       ? ((InterfaceType*)value)->dispatchTable->size            \
                       : sizeof(Type);                                           \
    auto interface = (InterfaceType*)alloca(sizeof(InterfaceType) + size);       \
    if (__builtin_types_compatible_p(typeof(value), InterfaceType*)) {           \
      memcpy(interface, (InterfaceType*)value, sizeof(InterfaceType) + size);    \
    }                                                                            \
    else {                                                                       \
      CONCAT(Type, As, InterfaceType)((Type*)value, interface);                  \
    }                                                                            \
    interface;                                                                   \
  })

#define to(Type, InterfaceType, fromValue)                                       \
  ({                                                                             \
    auto value     = (fromValue);                                                \
    UInt size      = __builtin_types_compatible_p(typeof(value), InterfaceType*) \
                       ? ((InterfaceType*)value)->dispatchTable->size            \
                       : sizeof(Type);                                           \
    auto interface = (InterfaceType*)malloc(sizeof(InterfaceType) + size);       \
    if (__builtin_types_compatible_p(typeof(value), InterfaceType*)) {           \
      memcpy(interface, (InterfaceType*)value, sizeof(InterfaceType) + size);    \
    }                                                                            \
    else {                                                                       \
      CONCAT(Type, As, InterfaceType)((Type*)value, interface);                  \
    }                                                                            \
    interface;                                                                   \
  })
