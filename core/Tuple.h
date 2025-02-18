#ifndef TupleArgs
#error "Define 'TupleArgs' to specify tuple arity."
#endif

#if TupleArgs < 2
#error "Tuple arity must be at least 2."
#endif

#if TupleArgs > 8
#error "Tuple arity must be at most 8."
#endif

#ifndef TupleT0
#error "Type parameter 'TupleT0' is not defined."
#endif

#ifndef TupleT1
#error "Type parameter 'TupleT1' is not defined."
#endif

#if TupleArgs >= 3
#ifndef TupleT2
#error "Type parameter 'TupleT2' is not defined."
#endif
#endif

#if TupleArgs >= 4
#ifndef TupleT3
#error "Type parameter 'TupleT3' is not defined."
#endif
#endif

#if TupleArgs >= 5
#ifndef TupleT4
#error "Type parameter 'TupleT4' is not defined."
#endif
#endif

#if TupleArgs >= 6
#ifndef TupleT5
#error "Type parameter 'TupleT5' is not defined."
#endif
#endif

#if TupleArgs >= 7
#ifndef TupleT6
#error "Type parameter 'TupleT6' is not defined."
#endif
#endif

#if TupleArgs == 8
#ifndef TupleT7
#error "Type parameter 'TupleT7' is not defined."
#endif
#endif

#include <core/Core.h>
#include <core/Generic.h>

#ifndef Tuple
#define Tuple(TupleT0, TupleT1) GENERIC2(Tuple, TupleT0, TupleT1)
#define Tuple2(TupleT0, TupleT1) GENERIC2(Tuple, TupleT0, TupleT1)
#define Tuple3(TupleT0, TupleT1, TupleT2) GENERIC3(Tuple, TupleT0, TupleT1, TupleT2)
#define Tuple4(TupleT0, TupleT1, TupleT2, TupleT3) GENERIC4(Tuple, TupleT0, TupleT1, TupleT2, TupleT3)
#define Tuple5(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4) GENERIC5(Tuple, TupleT0, TupleT1, TupleT2, TupleT3, TupleT4)
#define Tuple6(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5) GENERIC6(Tuple, TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5)
#define Tuple7(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6) GENERIC7(Tuple, TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6)
#define Tuple8(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7) GENERIC8(Tuple, TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7)
#endif

typedef struct {
  TupleT0 _0;
  TupleT1 _1;

#if TupleArgs >= 3
  TupleT2 _2;
#endif

#if TupleArgs >= 4
  TupleT3 _3;
#endif

#if TupleArgs >= 5
  TupleT4 _4;
#endif

#if TupleArgs >= 6
  TupleT5 _5;
#endif

#if TupleArgs >= 7
  TupleT6 _6;
#endif

#if TupleArgs == 8
  TupleT7 _7;
#endif
}
#if TupleArgs == 2
Tuple(TupleT0, TupleT1);
#elif TupleArgs == 3
Tuple3(TupleT0, TupleT1, TupleT2);
#elif TupleArgs == 4
Tuple4(TupleT0, TupleT1, TupleT2, TupleT3);
#elif TupleArgs == 5
Tuple5(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4);
#elif TupleArgs == 6
Tuple6(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5);
#elif TupleArgs == 7
Tuple7(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6);
#elif TupleArgs == 8
Tuple8(TupleT0, TupleT1, TupleT2, TupleT3, TupleT4, TupleT5, TupleT6, TupleT7);
#endif
