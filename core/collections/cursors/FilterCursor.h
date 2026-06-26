#ifndef FilterCursorSourceCursor
#error Type parameter 'FilterCursorSourceCursor' is not defined
#endif

#ifndef FilterCursorSourceCursorNext
#error Function parameter 'Option(FilterCursorElement) FilterCursorSourceCursorNext(FilterCursorSourceCursor* cursor)' is not defined
#endif

#ifndef FilterCursorSourceCursorDestroy
#error Function parameter 'Unit FilterCursorSourceCursorDestroy(FilterCursorSourceCursor* cursor)' is not defined
#endif

#ifndef FilterCursorFilterClosure
#error Type parameter 'FilterCursorFilterClosure' is not defined
#endif

#ifndef FilterCursorFilterClosureCall
#error Function parameter 'Bool FilterCursorFilterClosureCall(FilterCursorFilterClosure* closure, FilterCursorElement value)' is not defined
#endif

#ifndef FilterCursorFilterClosureDestroy
#error Function parameter 'Unit FilterCursorFilterClosureDestroy(FilterCursorFilterClosure* closure)' is not defined
#endif

#ifndef FilterCursorElement
#error Type parameter 'FilterCursorElement' is not defined
#endif

#ifndef FilterCursor
#include <core/Core.h>

#define FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) GENERIC(FilterCursor, FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement)
#define FilterCursorCreate(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) CONCAT(FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement), Create)
#define FilterCursorNext(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) CONCAT(FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement), Next)
#define FilterCursorClone(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) CONCAT(FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement), Clone)
#define FilterCursorDestroy(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) CONCAT(FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement), Destroy)
#endif

#if defined FilterCursorSourceCursor && defined FilterCursorFilterClosure && defined FilterCursorElement
typedef struct FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) {
  FilterCursorSourceCursor source;
  FilterCursorFilterClosure Filter;
} FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement);

FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) FilterCursorCreate(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement)(
  FilterCursorSourceCursor source,
  FilterCursorFilterClosure Filter
);
Option(FilterCursorElement) FilterCursorNext(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement)(
  FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) * self
);
Unit FilterCursorDestroy(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement)(
  FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) * self
);
IMPLEMENT_SIG(
  FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement),
  Cursor(FilterCursorElement)
);

#ifdef FILTER_CURSOR_IMPLEMENTATION
COREAPI FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) FilterCursorCreate(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement)(
  FilterCursorSourceCursor source,
  FilterCursorFilterClosure Filter
) {
  return (FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement)){
    .source = source,
    .Filter = Filter,
  };
}

COREAPI Option(FilterCursorElement) FilterCursorNext(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement)(
  FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) * self
) {
  auto next = FilterCursorSourceCursorNext(&self->source);

  match(&next) {
    case(OptionSome, sourceElement) {
      if (FilterCursorFilterClosureCall(&self->Filter, *sourceElement)) {
        return OptionSome(FilterCursorElement)(*sourceElement);
      }
      else {
        return FilterCursorNext(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement)(self);
      }
    }
    case(OptionNone) {
      return OptionNone(FilterCursorElement)();
    }
  }
}

COREAPI Unit FilterCursorDestroy(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement)(
  FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement) * self
) {
  FilterCursorSourceCursorDestroy(&self->source);
  FilterCursorFilterClosureDestroy(&self->Filter);
  return_unit;
}

COREAPI IMPLEMENT(
  FilterCursor(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement),
  Cursor(FilterCursorElement),
  .Next    = (void*)FilterCursorNext(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement),
  .Destroy = (void*)FilterCursorDestroy(FilterCursorSourceCursor, FilterCursorFilterClosure, FilterCursorElement)
);
#endif // FILTER_CURSOR_IMPLEMENTATION
#endif // FilterCursorSourceCursor && FilterCursorFilterClosure && FilterCursorElement

#undef FILTER_CURSOR_IMPLEMENTATION
#undef FilterCursorSourceCursor
#undef FilterCursorSourceCursorNext
#undef FilterCursorSourceCursorDestroy
#undef FilterCursorFilterClosure
#undef FilterCursorFilterClosureCall
#undef FilterCursorFilterClosureDestroy
#undef FilterCursorElement
