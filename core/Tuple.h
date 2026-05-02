#ifndef Tuple
#include <core/Core.h>

#define Tuple(...) GENERIC(Tuple, __VA_ARGS__)
#define TupleClone(...) GENERIC(TupleClone, __VA_ARGS__)
#define TupleDestroy(...) GENERIC(TupleDestroy, __VA_ARGS__)
#endif

#ifndef TupleArgs
#error Define 'TupleArgs' to specify the type arguments of the tuple.
#endif

#define TupleArity COUNT_ARGS(TupleArgs)

#if TupleArity < 2
#error Tuple arity must be at least 2.
#endif

#if TupleArity > 8
#error Tuple arity may be at most 8.
#endif

#define TupleT0 GET_ARG(1, TupleArgs)

#ifndef TupleT0Clone
#define TupleT0Clone(value) (*(value))
#endif

#ifndef TupleT0Destroy
#define TupleT0Destroy(value) ((void)(value))
#endif

#define TupleT1 GET_ARG(2, TupleArgs)

#ifndef TupleT1Clone
#define TupleT1Clone(value) (*(value))
#endif

#ifndef TupleT1Destroy
#define TupleT1Destroy(value) ((void)(value))
#endif

#if TupleArity >= 3
#define TupleT2 GET_ARG(3, TupleArgs)

#ifndef TupleT2Clone
#define TupleT2Clone(value) (*(value))
#endif

#ifndef TupleT2Destroy
#define TupleT2Destroy(value) ((void)(value))
#endif
#endif

#if TupleArity >= 4
#define TupleT3 GET_ARG(4, TupleArgs)

#ifndef TupleT3Clone
#define TupleT3Clone(value) (*(value))
#endif

#ifndef TupleT3Destroy
#define TupleT3Destroy(value) ((void)(value))
#endif
#endif

#if TupleArity >= 5
#define TupleT4 GET_ARG(5, TupleArgs)

#ifndef TupleT4Clone
#define TupleT4Clone(value) (*(value))
#endif

#ifndef TupleT4Destroy
#define TupleT4Destroy(value) ((void)(value))
#endif
#endif

#if TupleArity >= 6
#define TupleT5 GET_ARG(6, TupleArgs)

#ifndef TupleT5Clone
#define TupleT5Clone(value) (*(value))
#endif

#ifndef TupleT5Destroy
#define TupleT5Destroy(value) ((void)(value))
#endif
#endif

#if TupleArity >= 7
#define TupleT6 GET_ARG(7, TupleArgs)

#ifndef TupleT6Clone
#define TupleT6Clone(value) (*(value))
#endif

#ifndef TupleT6Destroy
#define TupleT6Destroy(value) ((void)(value))
#endif
#endif

#if TupleArity == 8
#define TupleT7 GET_ARG(8, TupleArgs)

#ifndef TupleT7Clone
#define TupleT7Clone(value) (*(value))
#endif

#ifndef TupleT7Destroy
#define TupleT7Destroy(value) ((void)(value))
#endif
#endif

#ifdef TupleArgs
typedef struct
#if TupleArity == 2
Tuple(TupleT0, TupleT1) {
#elif TupleArity == 3
Tuple(TupleT0, TupleT1, TupleT2) {
#elif TupleArity == 4
Tuple(TupleT0, TupleT1, TupleT2, TupleT3) {
#elif TupleArity == 5
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4) {
#elif TupleArity == 6
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5) {
#elif TupleArity == 7
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6) {
#elif TupleArity == 8
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7) {
#endif
  TupleT0 _0;
  TupleT1 _1;

#if TupleArity >= 3
  TupleT2 _2;
#endif

#if TupleArity >= 4
  TupleT3 _3;
#endif

#if TupleArity >= 5
  TupleT4 _4;
#endif

#if TupleArity >= 6
  TupleT5 _5;
#endif

#if TupleArity >= 7
  TupleT6 _6;
#endif

#if TupleArity == 8
  TupleT7 _7;
#endif
}
#if TupleArity == 2
Tuple(TupleT0, TupleT1);
#elif TupleArity == 3
Tuple(TupleT0, TupleT1, TupleT2);
#elif TupleArity == 4
Tuple(TupleT0, TupleT1, TupleT2, TupleT3);
#elif TupleArity == 5
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4);
#elif TupleArity == 6
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5);
#elif TupleArity == 7
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6);
#elif TupleArity == 8
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7);
#endif

#if TupleArity == 2
Tuple(TupleT0, TupleT1) TupleClone(TupleT0, TupleT1)(Tuple(TupleT0, TupleT1) const* tuple);
#elif TupleArity == 3
Tuple(TupleT0, TupleT1, TupleT2) TupleClone(TupleT0, TupleT1, TupleT2)(Tuple(TupleT0, TupleT1, TupleT2) const* tuple);
#elif TupleArity == 4
Tuple(TupleT0, TupleT1, TupleT2, TupleT3) TupleClone(TupleT0, TupleT1, TupleT2, TupleT3)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3) const* tuple);
#elif TupleArity == 5
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4) TupleClone(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4) const* tuple);
#elif TupleArity == 6
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5) TupleClone(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5) const* tuple);
#elif TupleArity == 7
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6) TupleClone(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6) const* tuple);
#elif TupleArity == 8
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7) TupleClone(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7) const* tuple);
#endif

void
#if TupleArity == 2
  TupleDestroy(TupleT0, TupleT1)(Tuple(TupleT0, TupleT1) * tuple);
#elif TupleArity == 3
  TupleDestroy(TupleT0, TupleT1, TupleT2)(Tuple(TupleT0, TupleT1, TupleT2) * tuple);
#elif TupleArity == 4
  TupleDestroy(TupleT0, TupleT1, TupleT2, TupleT3)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3) * tuple);
#elif TupleArity == 5
  TupleDestroy(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4) * tuple);
#elif TupleArity == 6
  TupleDestroy(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5) * tuple);
#elif TupleArity == 7
  TupleDestroy(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6) * tuple);
#elif TupleArity == 8
  TupleDestroy(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7) * tuple);
#endif

#ifdef TUPLE_IMPLEMENTATION
#if TupleArity == 2
Tuple(TupleT0, TupleT1) TupleClone(TupleT0, TupleT1)(Tuple(TupleT0, TupleT1) const* tuple) {
  return (Tuple(TupleT0, TupleT1)) {
#elif TupleArity == 3
Tuple(TupleT0, TupleT1, TupleT2) TupleClone(TupleT0, TupleT1, TupleT2)(Tuple(TupleT0, TupleT1, TupleT2) const* tuple) {
  return (Tuple(TupleT0, TupleT1, TupleT2)) {
#elif TupleArity == 4
Tuple(TupleT0, TupleT1, TupleT2, TupleT3) TupleClone(TupleT0, TupleT1, TupleT2, TupleT3)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3) const* tuple) {
  return (Tuple(TupleT0, TupleT1, TupleT2, TupleT3)) {
#elif TupleArity == 5
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4) TupleClone(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4) const* tuple) {
  return (Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4)) {
#elif TupleArity == 6
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5) TupleClone(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5) const* tuple) {
  return (Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5)) {
#elif TupleArity == 7
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6) TupleClone(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6) const* tuple) {
  return (Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6)) {
#elif TupleArity == 8
Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7) TupleClone(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7) const* tuple) {
  return (Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7)){
#endif
    ._0 = TupleT0Clone(&tuple->_0),
    ._1 = TupleT1Clone(&tuple->_1),
#if TupleArity >= 3
    ._2 = TupleT2Clone(&tuple->_2),
#elif TupleArity >= 4
    ._3 = TupleT3Clone(&tuple->_3),
#elif TupleArity >= 5
    ._4 = TupleT4Clone(&tuple->_4),
#elif TupleArity >= 6
    ._5 = TupleT5Clone(&tuple->_5),
#elif TupleArity >= 7
    ._6 = TupleT6Clone(&tuple->_6),
#elif TupleArity == 8
    ._7 = TupleT7Clone(&tuple->_7),
#endif
  };
}

void
#if TupleArity == 2
TupleDestroy(TupleT0, TupleT1)(Tuple(TupleT0, TupleT1) * tuple) {
#elif TupleArity == 3
TupleDestroy(TupleT0, TupleT1, TupleT2)(Tuple(TupleT0, TupleT1, TupleT2) * tuple) {
#elif TupleArity == 4
TupleDestroy(TupleT0, TupleT1, TupleT2, TupleT3)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3) * tuple) {
#elif TupleArity == 5
TupleDestroy(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4) * tuple) {
#elif TupleArity == 6
TupleDestroy(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5) * tuple) {
#elif TupleArity == 7
TupleDestroy(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6) * tuple) {
#elif TupleArity == 8
TupleDestroy(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7)(Tuple(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7) * tuple) {
#endif
  TupleT0Destroy(&tuple->_0);
  TupleT1Destroy(&tuple->_1);
#if TupleArity >= 3
  TupleT2Destroy(&tuple->_2);
#elif TupleArity >= 4
  TupleT3Destroy(&tuple->_3);
#elif TupleArity >= 5
  TupleT4Destroy(&tuple->_4);
#elif TupleArity >= 6
  TupleT5Destroy(&tuple->_5);
#elif TupleArity >= 7
  TupleT6Destroy(&tuple->_6);
#elif TupleArity == 8
  TupleT7Destroy(&tuple->_7);
#endif
}
#endif // TUPLE_IMPLEMENTATION
#endif // TupleArity

#undef TupleArgs
#undef TupleArity
#undef TupleT0
#undef TupleT0Clone
#undef TupleT0Destroy
#undef TupleT1
#undef TupleT1Clone
#undef TupleT1Destroy
#undef TupleT2
#undef TupleT2Clone
#undef TupleT2Destroy
#undef TupleT3
#undef TupleT3Clone
#undef TupleT3Destroy
#undef TupleT4
#undef TupleT4Clone
#undef TupleT4Destroy
#undef TupleT5
#undef TupleT5Clone
#undef TupleT5Destroy
#undef TupleT6
#undef TupleT6Clone
#undef TupleT6Destroy
#undef TupleT7
#undef TupleT7Clone
#undef TupleT7Destroy
#undef TUPLE_IMPLEMENTATION
