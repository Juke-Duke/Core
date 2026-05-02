#ifndef StackElement
#error Type parameter 'StackElement' is not defined.
#endif

#ifndef StackElementDefault
#define StackElementDefault() ((StackElement){})
#endif

#ifndef StackElementClone
#define StackElementClone(value) (*(value))
#endif

#ifndef StackElementDestroy
#define StackElementDestroy(value) ((void)(value))
#endif

#ifndef Stack
#include <core/Core.h>

#define Stack(StackElement) GENERIC(Stack, StackElement)
#define StackDefault(StackElement) CONCAT(Stack(StackElement), Default)
#define StackCount(StackElement) CONCAT(Stack(StackElement), Count)
#define StackPush(StackElement) CONCAT(Stack(StackElement), Push)
#define StackPop(StackElement) CONCAT(Stack(StackElement), Pop)
#define StackPeek(StackElement) CONCAT(Stack(StackElement), Peek)
#define StackClone(StackElement) CONCAT(Stack(StackElement), Clone)
#define StackDestroy(StackElement) CONCAT(Stack(StackElement), Destroy)

#define StackCursor(StackElement) GENERIC(StackCursor, StackElement)
#define StackCursorCreate(StackElement) CONCAT(StackCursor(StackElement), Create)
#define StackCursorNext(StackElement) CONCAT(StackCursor(StackElement), Next)
#define StackCursorClone(StackElement) CONCAT(StackCursor(StackElement), Clone)
#define StackCursorDestroy(StackElement) CONCAT(StackCursor(StackElement), Destroy)
#endif

#ifdef StackElement
#if defined STACK_IMPLEMENTATION && !defined DISABLE_ARRAY_StackElement_IMPLEMENTATION
#define ARRAY_IMPLEMENTATION
#define DISABLE_OPTION_REF_ArrayElement_IMPLEMENTATION
#define DISABLE_CURSOR_ArrayElement_IMPLEMENTATION
#endif
#define ArrayElement StackElement
#define ArrayElementDefault StackElementDefault
#define ArrayElementClone StackElementClone
#define ArrayElementDestroy StackElementDestroy
#include <core/collections/Array.h>

#if defined STACK_IMPLEMENTATION && !defined DISABLE_OPTION_StackElement_IMPLEMENTATION
#define OPTION_IMPLEMENTATION
#endif
#define OptionValue StackElement
#define OptionValueClone StackElementClone
#define OptionValueDestroy StackElementDestroy
#include <core/Option.h>

#define RefT StackElement
#include <core/Ref.h>

#if defined STACK_IMPLEMENTATION && !defined DISABLE_OPTION_REF_StackElement_IMPLEMENTATION
#define OPTION_IMPLEMENTATION
#endif
#define OptionValue Ref(StackElement)
#include <core/Option.h>

#if defined STACK_IMPLEMENTATION && !defined DISABLE_Cursor_StackElement_IMPLEMENTATION
#define CURSOR_IMPLEMENTATION
#define DISABLE_OPTION_REF_CursorElement_IMPLEMENTATION
#endif
#define CursorElement StackElement
#include <core/collections/Cursor.h>

typedef struct Stack(StackElement) {
  Array(StackElement) elements;
  UInt count;
} Stack(StackElement);

Stack(StackElement) StackDefault(StackElement)();
UInt StackCount(StackElement)(Stack(StackElement) const* stack);
void StackPush(StackElement)(Stack(StackElement) * stack, StackElement element);
Option(StackElement) StackPop(StackElement)(Stack(StackElement) * stack);
Option(StackElement) StackPeek(StackElement)(Stack(StackElement) const* stack);
Stack(StackElement) StackClone(StackElement)(Stack(StackElement) const* stack);
void StackDestroy(StackElement)(Stack(StackElement) * stack);

typedef struct StackCursor(StackElement) {
  Stack(StackElement) const* stack;
  UInt index;
} StackCursor(StackElement);

StackCursor(StackElement) StackCursorCreate(StackElement)(Stack(StackElement) const* stack);
Option(Ref(StackElement)) StackCursorNext(StackElement)(StackCursor(StackElement) * stackCursor);
StackCursor(StackElement) StackCursorClone(StackElement)(StackCursor(StackElement) const* stackCursor);
void StackCursorDestroy(StackElement)(StackCursor(StackElement) * stackCursor);

#ifdef STACK_IMPLEMENTATION
Stack(StackElement) StackDefault(StackElement)() {
  return (Stack(StackElement)){
    .elements = ArrayDefault(StackElement)(),
    .count    = 0,
  };
}

UInt StackCount(StackElement)(Stack(StackElement) const* stack) {
  return stack->count;
}

void StackPush(StackElement)(Stack(StackElement) * stack, StackElement element) {
  if (stack->count == ArrayCapacity(StackElement)(&stack->elements)) {
    ArrayResize(StackElement)(&stack->elements, ArrayCapacity(StackElement)(&stack->elements) * 2 + 8);
  }

  *ArrayAtMut(StackElement)(&stack->elements, stack->count) = element;
  ++stack->count;
}

Option(StackElement) StackPop(StackElement)(Stack(StackElement) * stack) {
  if (stack->count == 0) {
    return OptionNone(StackElement)();
  }

  --stack->count;
  return OptionSome(StackElement)(*ArrayAt(StackElement)(&stack->elements, stack->count));
}

Option(StackElement) StackPeek(StackElement)(Stack(StackElement) const* stack) {
  if (stack->count == 0) {
    return OptionNone(StackElement)();
  }

  return OptionSome(StackElement)(*ArrayAt(StackElement)(&stack->elements, stack->count - 1));
}

Stack(StackElement) StackClone(StackElement)(Stack(StackElement) const* stack) {
  return (Stack(StackElement)){
    .elements = ArrayClone(StackElement)(&stack->elements),
    .count    = stack->count,
  };
}

void StackDestroy(StackElement)(Stack(StackElement) * stack) {
  ArrayDestroy(StackElement)(&stack->elements);
  stack->count = 0;
}

StackCursor(StackElement) StackCursorCreate(StackElement)(Stack(StackElement) const* stack) {
  return (StackCursor(StackElement)){
    .stack = stack,
    .index = StackCount(StackElement)(stack),
  };
}

Option(Ref(StackElement)) StackCursorNext(StackElement)(StackCursor(StackElement) * stackCursor) {
  if (stackCursor->index == 0) {
    return OptionNone(Ref(StackElement))();
  }

  --stackCursor->index;
  return OptionSome(Ref(StackElement))(ArrayAt(StackElement)(&stackCursor->stack->elements, stackCursor->index));
}

StackCursor(StackElement) StackCursorClone(StackElement)(StackCursor(StackElement) const* stackCursor) {
  return (StackCursor(StackElement)){
    .stack = stackCursor->stack,
    .index = stackCursor->index,
  };
}

void StackCursorDestroy(StackElement)(StackCursor(StackElement) * stackCursor) {
  stackCursor->index = 0;
}

implement(
  StackCursor(StackElement),
  Cursor(StackElement),
  .Next = (void*)StackCursorNext(StackElement),
);
#endif // STACK_IMPLEMENTATION
#endif // StackElement

#undef StackElement
#undef StackElementClone
#undef StackElementDestroy
#undef STACK_IMPLEMENTATION
