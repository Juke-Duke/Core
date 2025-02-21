#ifndef DequeElement
#error Type parameter 'DequeElement' is not defined.
#endif

#include <core/Core.h>
#include <core/Generic.h>

#ifndef DISABLE_Array_DequeElement
#define ArrayElement DequeElement
#include <core/collections/Array.h>
#endif
#undef DISABLE_Array_DequeElement

#ifndef DISABLE_Option_DequeElement
#define OptionValue DequeElement
#include <core/Option.h>
#endif
#undef DISABLE_Option_DequeElement

#ifndef Deque
#define Deque(DequeElement) GENERIC(Deque, DequeElement)
#define DequeDefault(DequeElement) GENERIC(DequeDefault, DequeElement)
#define DequeCount(DequeElement) GENERIC(DequeCount, DequeElement)
#define DequeResize(DequeElement) GENERIC(DequeResize, DequeElement)
#define DequeFront(DequeElement) GENERIC(DequeFront, DequeElement)
#define DequeBack(DequeElement) GENERIC(DequeBack, DequeElement)
#define DequeQueueFront(DequeElement) GENERIC(DequeQueueFront, DequeElement)
#define DequeQueueBack(DequeElement) GENERIC(DequeQueueBack, DequeElement)
#define DequeDequeueFront(DequeElement) GENERIC(DequeDequeueFront, DequeElement)
#define DequeDequeueBack(DequeElement) GENERIC(DequeDequeueBack, DequeElement)
#define DequeDestroy(DequeElement) GENERIC(DequeDestroy, DequeElement)
#endif

typedef struct {
  Array(DequeElement) ring;
  UInt front;
  UInt count;
} Deque(DequeElement);

static Deque(DequeElement) DequeDefault(DequeElement)() {
  return (Deque(DequeElement)){
    .ring = ArrayDefault(DequeElement)(),
    .front = 0,
    .count = 0,
  };
}

static UInt DequeCount(DequeElement)(Deque(DequeElement) * deque) {
  return deque->count;
}

static void DequeResize(DequeElement)(Deque(DequeElement) * deque) {
  var oldRing = deque->ring;

  deque->ring = ArrayCreateWithCapacity(DequeElement)(ArrayCapacity(DequeElement)(&oldRing) * 2 + 8);

  for (var i = 0; i < deque->count; ++i) {
    ArraySetAt(DequeElement)(
      &deque->ring,
      i,
      ArrayAt(DequeElement)(
        &oldRing,
        (deque->front + i) % ArrayCapacity(DequeElement)(&oldRing)
      )
    );
  }

  deque->front = 0;
  ArrayDestroy(DequeElement)(oldRing);
}

static Option(DequeElement) DequeFront(DequeElement)(Deque(DequeElement) * deque) {
  if (deque->count == 0) {
    return OptionNone(DequeElement)();
  }

  return OptionSome(DequeElement)(ArrayAt(DequeElement)(&deque->ring, deque->front));
}

static Option(DequeElement) DequeBack(DequeElement)(Deque(DequeElement) * deque) {
  if (deque->count == 0) {
    return OptionNone(DequeElement)();
  }

  return OptionSome(DequeElement)(
    ArrayAt(DequeElement)(&deque->ring, (deque->front + deque->count - 1) % ArrayCapacity(DequeElement)(&deque->ring))
  );
}

static void DequeQueueFront(DequeElement)(Deque(DequeElement) * deque, DequeElement element) {
  if (deque->count == ArrayCapacity(DequeElement)(&deque->ring)) {
    DequeResize(DequeElement)(deque);
  }

  deque->front = (deque->front - 1 + ArrayCapacity(DequeElement)(&deque->ring)) % ArrayCapacity(DequeElement)(&deque->ring);
  ArraySetAt(DequeElement)(&deque->ring, deque->front, element);
  ++deque->count;
}

static void DequeQueueBack(DequeElement)(Deque(DequeElement) * deque, DequeElement element) {
  if (deque->count == ArrayCapacity(DequeElement)(&deque->ring)) {
    DequeResize(DequeElement)(deque);
  }

  var back = (deque->front + deque->count) % ArrayCapacity(DequeElement)(&deque->ring);
  ArraySetAt(DequeElement)(&deque->ring, back, element);
  ++deque->count;
}

static Option(DequeElement) DequeDequeueFront(DequeElement)(Deque(DequeElement) * deque) {
  if (deque->count == 0) {
    return OptionNone(DequeElement)();
  }

  var element = ArrayAt(DequeElement)(&deque->ring, deque->front);
  deque->front = (deque->front + 1) % ArrayCapacity(DequeElement)(&deque->ring);
  --deque->count;

  return OptionSome(DequeElement)(element);
}

static Option(DequeElement) DequeDequeueBack(DequeElement)(Deque(DequeElement) * deque) {
  if (deque->count == 0) {
    return OptionNone(DequeElement)();
  }

  var back = (deque->front + deque->count - 1) % ArrayCapacity(DequeElement)(&deque->ring);
  var element = ArrayAt(DequeElement)(&deque->ring, back);
  --deque->count;

  return OptionSome(DequeElement)(element);
}

static void DequeDestroy(DequeElement)(Deque(DequeElement) deque) {
  ArrayDestroy(DequeElement)(deque.ring);
}

#undef DequeElement
