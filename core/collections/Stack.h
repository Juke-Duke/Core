#ifndef StackElement
#error Type parameter 'StackElement' is not defined.
#endif

#include <core/Core.h>
#include <core/Generic.h>

#ifndef DISABLE_Array_StackElement
#define ArrayElement StackElement
#include <core/collections/Array.h>
#endif

#ifndef DISABLE_Option_StackElement
#define OptionValue StackElement
#include <core/Option.h>
#endif

#ifndef Stack
#define Stack(StackElement) GENERIC(Stack, StackElement)
#define StackDefault(StackElement) GENERIC(StackDefault, StackElement)
#define StackCount(StackElement) GENERIC(StackCount, StackElement)
#define StackPush(StackElement) GENERIC(StackPush, StackElement)
#define StackPop(StackElement) GENERIC(StackPop, StackElement)
#define StackPeek(StackElement) GENERIC(StackPeek, StackElement)
#define StackDestroy(StackElement) GENERIC(StackDestroy, StackElement)
#endif

typedef struct {
  Array(StackElement) elements;
  UInt count;
} Stack(StackElement);

static Stack(StackElement) StackDefault(StackElement)() {
  return (Stack(StackElement)){
    .elements = ArrayDefault(StackElement)(),
    .count = 0,
  };
}

static UInt StackCount(StackElement)(Stack(StackElement) const* stack) {
  return stack->count;
}

static void StackPush(StackElement)(Stack(StackElement) * stack, StackElement element) {
  if (stack->count == ArrayCapacity(StackElement)(&stack->elements)) {
    ArrayResize(StackElement)(&stack->elements, ArrayCapacity(StackElement)(&stack->elements) * 2 + 8);
  }

  ArraySetAt(StackElement)(&stack->elements, stack->count, element);
  ++stack->count;
}

static Option(StackElement) StackPop(StackElement)(Stack(StackElement) * stack) {
  if (stack->count == 0) {
    return OptionNone(StackElement)();
  }

  var element = ArrayAt(StackElement)(&stack->elements, stack->count - 1);
  --stack->count;

  return OptionSome(StackElement)(element);
}

static Option(StackElement) StackPeek(StackElement)(Stack(StackElement) const* stack) {
  if (stack->count == 0) {
    return OptionNone(StackElement)();
  }

  return OptionSome(StackElement)(ArrayAt(StackElement)(&stack->elements, stack->count - 1));
}

static void StackDestroy(StackElement)(Stack(StackElement) stack) {
  ArrayDestroy(StackElement)(stack.elements);
}

#undef StackElement
