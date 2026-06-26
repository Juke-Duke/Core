#ifndef DequeElement
#error Type parameter 'DequeElement' is not defined
#endif

#ifndef DequeElementDefault
#define DequeElementDefault() ((DequeElement){})
#endif

#ifndef DequeElementClone
#define DequeElementClone(element) (*(element))
#endif

#ifndef DequeElementDestroy
#define DequeElementDestroy(element) ((void)(element))
#endif

#ifndef Deque
#include <core/Core.h>

#define Deque(DequeElement) GENERIC(Deque, DequeElement)
#define DequeDefault(DequeElement) CONCAT(Deque(DequeElement), Default)
#define DequeCount(DequeElement) CONCAT(Deque(DequeElement), Count)
#define DequeFront(DequeElement) CONCAT(Deque(DequeElement), Front)
#define DequeBack(DequeElement) CONCAT(Deque(DequeElement), Back)
#define DequeQueueFront(DequeElement) CONCAT(Deque(DequeElement), QueueFront)
#define DequeQueueBack(DequeElement) CONCAT(Deque(DequeElement), QueueBack)
#define DequeDequeueFront(DequeElement) CONCAT(Deque(DequeElement), DequeueFront)
#define DequeDequeueBack(DequeElement) CONCAT(Deque(DequeElement), DequeueBack)
#define DequeClone(DequeElement) CONCAT(Deque(DequeElement), Clone)
#define DequeDestroy(DequeElement) CONCAT(Deque(DequeElement), Destroy)

#define DequeCursor(DequeElement) GENERIC(DequeCursor, DequeElement)
#define DequeCursorCreate(DequeElement) CONCAT(DequeCursor(DequeElement), Create)
#define DequeCursorNext(DequeElement) CONCAT(DequeCursor(DequeElement), Next)
#define DequeCursorClone(DequeElement) CONCAT(DequeCursor(DequeElement), Clone)
#define DequeCursorDestroy(DequeElement) CONCAT(DequeCursor(DequeElement), Destroy)
#endif

#ifdef DequeElement
#define ArrayElement DequeElement
#include <core/collections/Array.h>

#define OptionValue DequeElement
#include <core/Option.h>

#define RefT DequeElement
#include <core/Ref.h>

#define OptionValue Ref(DequeElement)
#include <core/Option.h>

#define CursorElement DequeElement
#include <core/collections/Cursor.h>

typedef struct Deque(DequeElement) {
  Array(DequeElement) ring;
  UInt front;
  UInt count;
} Deque(DequeElement);

Deque(DequeElement) DequeDefault(DequeElement)();
UInt DequeCount(DequeElement)(Deque(DequeElement) * deque);
Option(Ref(DequeElement)) DequeFront(DequeElement)(Deque(DequeElement) * deque);
Option(Ref(DequeElement)) DequeBack(DequeElement)(Deque(DequeElement) * deque);
Unit DequeQueueFront(DequeElement)(Deque(DequeElement) * deque, DequeElement element);
Unit DequeQueueBack(DequeElement)(Deque(DequeElement) * deque, DequeElement element);
Option(DequeElement) DequeDequeueFront(DequeElement)(Deque(DequeElement) * deque);
Option(DequeElement) DequeDequeueBack(DequeElement)(Deque(DequeElement) * deque);
Deque(DequeElement) DequeClone(DequeElement)(Deque(DequeElement) const* deque);
Unit DequeDestroy(DequeElement)(Deque(DequeElement) * deque);

typedef struct DequeCursor(DequeElement) {
  Deque(DequeElement) const* deque;
  UInt index;
} DequeCursor(DequeElement);

DequeCursor(DequeElement) DequeCursorCreate(DequeElement)(Deque(DequeElement) const* deque);
Option(Ref(DequeElement)) DequeCursorNext(DequeElement)(DequeCursor(DequeElement) * cursor);
DequeCursor(DequeElement) DequeCursorClone(DequeElement)(DequeCursor(DequeElement) const* cursor);
Unit DequeCursorDestroy(DequeElement)(DequeCursor(DequeElement) * cursor);
IMPLEMENT_SIG(DequeCursor(DequeElement), Cursor(DequeElement));

#ifdef DEQUE_IMPLEMENTATION
COREAPI Deque(DequeElement) DequeDefault(DequeElement)() {
  return (Deque(DequeElement)){
    .ring  = ArrayDefault(DequeElement)(),
    .front = 0,
    .count = 0,
  };
}

COREAPI UInt DequeCount(DequeElement)(Deque(DequeElement) * deque) {
  return deque->count;
}

static Unit CONCAT(Deque(DequeElement), Resize)(Deque(DequeElement) * deque) {
  auto oldRing = deque->ring;
  deque->ring  = ArrayCreateWithCapacity(DequeElement)(ArrayCapacity(DequeElement)(&oldRing) * 2 + 8);

  for (auto i = (UInt)0; i < deque->count; ++i) {
    *ArrayAtMut(DequeElement)(&deque->ring, i) = *ArrayAt(DequeElement)(&oldRing, (deque->front + i) % ArrayCapacity(DequeElement)(&oldRing));
  }

  ArrayDestroy(DequeElement)(&oldRing);
  deque->front = 0;
  return_unit;
}

COREAPI Option(Ref(DequeElement)) DequeFront(DequeElement)(Deque(DequeElement) * deque) {
  if (deque->count == 0) {
    return OptionNone(Ref(DequeElement))();
  }

  return OptionSome(Ref(DequeElement))(ArrayAt(DequeElement)(&deque->ring, deque->front));
}

COREAPI Option(Ref(DequeElement)) DequeBack(DequeElement)(Deque(DequeElement) * deque) {
  if (deque->count == 0) {
    return OptionNone(Ref(DequeElement))();
  }

  return OptionSome(Ref(DequeElement))(
    ArrayAt(DequeElement)(&deque->ring, (deque->front + deque->count - 1) % ArrayCapacity(DequeElement)(&deque->ring))
  );
}

COREAPI Unit DequeQueueFront(DequeElement)(Deque(DequeElement) * deque, DequeElement element) {
  if (deque->count == ArrayCapacity(DequeElement)(&deque->ring)) {
    CONCAT(Deque(DequeElement), Resize)(deque);
  }

  deque->front                                          = (deque->front - 1 + ArrayCapacity(DequeElement)(&deque->ring)) % ArrayCapacity(DequeElement)(&deque->ring);
  *ArrayAtMut(DequeElement)(&deque->ring, deque->front) = DequeElementClone(&element);
  ++deque->count;
  return_unit;
}

COREAPI Unit DequeQueueBack(DequeElement)(Deque(DequeElement) * deque, DequeElement element) {
  if (deque->count == ArrayCapacity(DequeElement)(&deque->ring)) {
    CONCAT(Deque(DequeElement), Resize)(deque);
  }

  auto back                                     = (deque->front + deque->count) % ArrayCapacity(DequeElement)(&deque->ring);
  *ArrayAtMut(DequeElement)(&deque->ring, back) = DequeElementClone(&element);
  ++deque->count;
  return_unit;
}

COREAPI Option(DequeElement) DequeDequeueFront(DequeElement)(Deque(DequeElement) * deque) {
  if (deque->count == 0) {
    return OptionNone(DequeElement)();
  }

  auto element = *ArrayAt(DequeElement)(&deque->ring, deque->front);
  deque->front = (deque->front + 1) % ArrayCapacity(DequeElement)(&deque->ring);
  --deque->count;

  return OptionSome(DequeElement)(element);
}

COREAPI Option(DequeElement) DequeDequeueBack(DequeElement)(Deque(DequeElement) * deque) {
  if (deque->count == 0) {
    return OptionNone(DequeElement)();
  }

  auto back    = (deque->front + deque->count - 1) % ArrayCapacity(DequeElement)(&deque->ring);
  auto element = *ArrayAt(DequeElement)(&deque->ring, back);
  --deque->count;

  return OptionSome(DequeElement)(element);
}

COREAPI Deque(DequeElement) DequeClone(DequeElement)(Deque(DequeElement) const* deque) {
  return (Deque(DequeElement)){
    .ring  = ArrayClone(DequeElement)(&deque->ring),
    .front = deque->front,
    .count = deque->count,
  };
}

COREAPI Unit DequeDestroy(DequeElement)(Deque(DequeElement) * deque) {
  ArrayDestroy(DequeElement)(&deque->ring);
  deque->front = 0;
  deque->count = 0;
  return_unit;
}

COREAPI DequeCursor(DequeElement) DequeCursorCreate(DequeElement)(Deque(DequeElement) const* deque) {
  return (DequeCursor(DequeElement)){
    .deque = deque,
    .index = 0,
  };
}

COREAPI Option(Ref(DequeElement)) DequeCursorNext(DequeElement)(DequeCursor(DequeElement) * cursor) {
  if (cursor->index >= cursor->deque->count) {
    return OptionNone(Ref(DequeElement))();
  }

  auto element = ArrayAt(DequeElement)(&cursor->deque->ring, (cursor->deque->front + cursor->index) % ArrayCapacity(DequeElement)(&cursor->deque->ring));
  ++cursor->index;
  return OptionSome(Ref(DequeElement))(element);
}

COREAPI DequeCursor(DequeElement) DequeCursorClone(DequeElement)(DequeCursor(DequeElement) const* cursor) {
  return (DequeCursor(DequeElement)){
    .deque = cursor->deque,
    .index = cursor->index,
  };
}

COREAPI Unit DequeCursorDestroy(DequeElement)(DequeCursor(DequeElement) * cursor) {
  cursor->index = 0;
  return_unit;
}

COREAPI IMPLEMENT(

  DequeCursor(DequeElement),
  Cursor(DequeElement),
  .Next    = (void*)DequeCursorNext(DequeElement),
  .Destroy = (void*)DequeCursorDestroy(DequeElement),
);
#endif // DEQUE_IMPLEMENTATION
#endif // DequeElement

#undef DEQUE_IMPLEMENTATION
#undef DequeElement
#undef DequeElementDefault
#undef DequeElementClone
#undef DequeElementDestroy
