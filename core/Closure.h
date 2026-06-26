// Closure(Return [, Arg0 [, Arg1 [, ...]]])
//
// Generic dispatchable callable, built on top of the standard interface(...)
// pattern. A Closure is an interface with exactly one user-facing slot, `Call`,
// plus the Destroy slot that every interface gets automatically — so closures
// can own state, clean it up, and be passed around behind a uniform pointer
// like any other interface.
//
// Usage:
//   #define ClosureArgs Bool, Ref(Int)        // (return, arg0, ..., argN)
//   #include <core/Closure.h>                 // declarations only
//
//   // ...and exactly once per (Return, Args) per program, also do:
//   #define CLOSURE_IMPLEMENTATION
//   #define ClosureArgs Bool, Ref(Int)
//   #include <core/Closure.h>                 // emits dispatch bodies
//
//   // Define a concrete callable:
//   typedef struct AtLeast { Int threshold; } AtLeast;
//   Bool AtLeastCall(AtLeast* self, Ref(Int) value) {
//     return *value >= self->threshold;
//   }
//   Unit AtLeastDestroy(AtLeast* self) { (void)self; return (Unit){}; }
//
//   IMPLEMENT(AtLeast, Closure(Bool, Ref(Int)),
//     .Call    = (void*)AtLeastCall,
//     .Destroy = (void*)AtLeastDestroy);
//
//   // Wrap and invoke:
//   auto closure = to(AtLeast, Closure(Bool, Ref(Int)), (AtLeast){ .threshold = 5 });
//   Bool ok = ClosureCall(Bool, Ref(Int))(closure, &someValue);
//   ClosureDestroy(Bool, Ref(Int))(closure);
//   free(closure);
//
// Arity goes from 1 (return only, nullary closure) up to 9 (return + 8 args).

#ifndef ClosureArgs
#error Define 'ClosureArgs' as 'Return [, Arg0 [, ...]]' (0..8 arguments).
#endif

#ifndef Closure
#include <core/Core.h>

#define Closure(...) GENERIC(Closure, __VA_ARGS__)
#define ClosureCall(...) CONCAT(Closure(__VA_ARGS__), Call)
#define ClosureDestroy(...) CONCAT(Closure(__VA_ARGS__), Destroy)
#endif

#define ClosureArity COUNT_ARGS(ClosureArgs)

#if ClosureArity < 1
#error Closure must specify at least a return type.
#endif

#if ClosureArity > 9
#error Closure may have at most 8 arguments (plus the return type).
#endif

#define ClosureReturn GET_ARG(1, ClosureArgs)

#if ClosureArity >= 2
#define ClosureArg0 GET_ARG(2, ClosureArgs)
#endif

#if ClosureArity >= 3
#define ClosureArg1 GET_ARG(3, ClosureArgs)
#endif

#if ClosureArity >= 4
#define ClosureArg2 GET_ARG(4, ClosureArgs)
#endif

#if ClosureArity >= 5
#define ClosureArg3 GET_ARG(5, ClosureArgs)
#endif

#if ClosureArity >= 6
#define ClosureArg4 GET_ARG(6, ClosureArgs)
#endif

#if ClosureArity >= 7
#define ClosureArg5 GET_ARG(7, ClosureArgs)
#endif

#if ClosureArity >= 8
#define ClosureArg6 GET_ARG(8, ClosureArgs)
#endif

#if ClosureArity == 9
#define ClosureArg7 GET_ARG(9, ClosureArgs)
#endif

#ifdef ClosureArgs

#if ClosureArity == 1
typedef struct Closure(ClosureReturn) interface(
  ClosureReturn (*Call)(void* self);
) Closure(ClosureReturn);

DISPATCH_DECL(Closure(ClosureReturn), ClosureReturn, Call, *);
DISPATCH_DECL(Closure(ClosureReturn), Unit, Destroy, *);

#elif ClosureArity == 2
typedef struct Closure(ClosureReturn, ClosureArg0) interface(
  ClosureReturn (*Call)(void* self, ClosureArg0 arg0);
) Closure(ClosureReturn, ClosureArg0);

DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0), ClosureReturn, Call, *, (ClosureArg0, arg0));
DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0), Unit, Destroy, *);

#elif ClosureArity == 3
typedef struct Closure(ClosureReturn, ClosureArg0, ClosureArg1) interface(
  ClosureReturn (*Call)(void* self, ClosureArg0 arg0, ClosureArg1 arg1);
) Closure(ClosureReturn, ClosureArg0, ClosureArg1);

DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1));
DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1), Unit, Destroy, *);

#elif ClosureArity == 4
typedef struct Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2) interface(
  ClosureReturn (*Call)(void* self, ClosureArg0 arg0, ClosureArg1 arg1, ClosureArg2 arg2);
) Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2);

DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2));
DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2), Unit, Destroy, *);

#elif ClosureArity == 5
typedef struct Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3) interface(
  ClosureReturn (*Call)(void* self, ClosureArg0 arg0, ClosureArg1 arg1, ClosureArg2 arg2, ClosureArg3 arg3);
) Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3);

DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2), (ClosureArg3, arg3));
DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3), Unit, Destroy, *);

#elif ClosureArity == 6
typedef struct Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4) interface(
  ClosureReturn (*Call)(void* self, ClosureArg0 arg0, ClosureArg1 arg1, ClosureArg2 arg2, ClosureArg3 arg3, ClosureArg4 arg4);
) Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4);

DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2), (ClosureArg3, arg3), (ClosureArg4, arg4), (ClosureArg5, arg5), (ClosureArg6, arg6));
DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6), Unit, Destroy, *);

#elif ClosureArity == 7
typedef struct Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5) interface(
  ClosureReturn (*Call)(void* self, ClosureArg0 arg0, ClosureArg1 arg1, ClosureArg2 arg2, ClosureArg3 arg3, ClosureArg4 arg4, ClosureArg5 arg5);
) Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5);

DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2), (ClosureArg3, arg3), (ClosureArg4, arg4), (ClosureArg5, arg5));
DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5), Unit, Destroy, *);

#elif ClosureArity == 8
typedef struct Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6) interface(
  ClosureReturn (*Call)(void* self, ClosureArg0 arg0, ClosureArg1 arg1, ClosureArg2 arg2, ClosureArg3 arg3, ClosureArg4 arg4, ClosureArg5 arg5, ClosureArg6 arg6);
) Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6);

DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2), (ClosureArg3, arg3), (ClosureArg4, arg4), (ClosureArg5, arg5), (ClosureArg6, arg6));
DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6), Unit, Destroy, *);

#elif ClosureArity == 9
typedef struct Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6, ClosureArg7) interface(
  ClosureReturn (*Call)(void* self, ClosureArg0 arg0, ClosureArg1 arg1, ClosureArg2 arg2, ClosureArg3 arg3, ClosureArg4 arg4, ClosureArg5 arg5, ClosureArg6 arg6, ClosureArg7 arg7);
) Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6, ClosureArg7);

DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6, ClosureArg7), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2), (ClosureArg3, arg3), (ClosureArg4, arg4), (ClosureArg5, arg5), (ClosureArg6, arg6), (ClosureArg7, arg7));
DISPATCH_DECL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6, ClosureArg7), Unit, Destroy, *);
#endif

#ifdef CLOSURE_IMPLEMENTATION
#if ClosureArity == 1
COREAPI DISPATCH_IMPL(Closure(ClosureReturn), ClosureReturn, Call, *);
COREAPI DISPATCH_IMPL(Closure(ClosureReturn), Unit, Destroy, *);

#elif ClosureArity == 2
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0), ClosureReturn, Call, *, (ClosureArg0, arg0));
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0), Unit, Destroy, *);

#elif ClosureArity == 3
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1));
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1), Unit, Destroy, *);

#elif ClosureArity == 4
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2));
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2), Unit, Destroy, *);

#elif ClosureArity == 5
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2), (ClosureArg3, arg3));
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3), Unit, Destroy, *);

#elif ClosureArity == 6
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2), (ClosureArg3, arg3), (ClosureArg4, arg4), (ClosureArg5, arg5), (ClosureArg6, arg6));
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6), Unit, Destroy, *);

#elif ClosureArity == 7
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2), (ClosureArg3, arg3), (ClosureArg4, arg4), (ClosureArg5, arg5));
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5), Unit, Destroy, *);

#elif ClosureArity == 8
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2), (ClosureArg3, arg3), (ClosureArg4, arg4), (ClosureArg5, arg5), (ClosureArg6, arg6));
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6), Unit, Destroy, *);

#elif ClosureArity == 9
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6, ClosureArg7), ClosureReturn, Call, *, (ClosureArg0, arg0), (ClosureArg1, arg1), (ClosureArg2, arg2), (ClosureArg3, arg3), (ClosureArg4, arg4), (ClosureArg5, arg5), (ClosureArg6, arg6), (ClosureArg7, arg7));
COREAPI DISPATCH_IMPL(Closure(ClosureReturn, ClosureArg0, ClosureArg1, ClosureArg2, ClosureArg3, ClosureArg4, ClosureArg5, ClosureArg6, ClosureArg7), Unit, Destroy, *);
#endif
#endif // CLOSURE_IMPLEMENTATION

#endif // ClosureArgs

#undef CLOSURE_IMPLEMENTATION
#undef ClosureArgs
#undef ClosureArity
#undef ClosureReturn
#undef ClosureArg0
#undef ClosureArg1
#undef ClosureArg2
#undef ClosureArg3
#undef ClosureArg4
#undef ClosureArg5
#undef ClosureArg6
#undef ClosureArg7
