#ifndef MapCursorSourceCursor
#error Type parameter 'MapCursorSourceCursor' is not defined
#endif

#ifndef MapCursorSourceCursorNext
#error Function parameter 'Option(MapCursorSourceElement) MapCursorSourceCursorNext(MapCursorSourceCursor* cursor)' is not defined
#endif

#ifndef MapCursorSourceCursorDestroy
#error Function parameter 'Unit MapCursorSourceCursorDestroy(MapCursorSourceCursor* cursor)' is not defined
#endif

#ifndef MapCursorMapperClosure
#error Type parameter 'MapCursorMapperClosure' is not defined
#endif

#ifndef MapCursorMapperClosureCall
#error Function parameter 'MapCursorTargetElement MapCursorMapperClosureCall(MapCursorMapperClosure* closure, MapCursorSourceElement value)' is not defined
#endif

#ifndef MapCursorMapperClosureDestroy
#error Function parameter 'Unit MapCursorMapperClosureDestroy(MapCursorMapperClosure* closure)' is not defined
#endif

#ifndef MapCursorSourceElement
#error Type parameter 'MapCursorSourceElement' is not defined
#endif

#ifndef MapCursorTargetElement
#error Type parameter 'MapCursorTargetElement' is not defined
#endif

#ifndef MapCursor
#include <core/Core.h>

#define MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) GENERIC(MapCursor, MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement)
#define MapCursorCreate(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) CONCAT(MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement), Create)
#define MapCursorNext(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) CONCAT(MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement), Next)
#define MapCursorClone(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) CONCAT(MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement), Clone)
#define MapCursorDestroy(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) CONCAT(MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement), Destroy)
#endif

#if defined MapCursorSourceCursor && defined MapCursorMapperClosure && defined MapCursorSourceElement && defined MapCursorTargetElement
typedef struct MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) {
  MapCursorSourceCursor source;
  MapCursorMapperClosure Map;
} MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement);

MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) MapCursorCreate(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement)(
  MapCursorSourceCursor source,
  MapCursorMapperClosure Map
);
Option(MapCursorTargetElement) MapCursorNext(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement)(
  MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) * self
);
Unit MapCursorDestroy(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement)(
  MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) * self
);
IMPLEMENT_SIG(
  MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement),
  Cursor(MapCursorTargetElement)
);

#ifdef MAP_CURSOR_IMPLEMENTATION
COREAPI MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) MapCursorCreate(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement)(
  MapCursorSourceCursor source,
  MapCursorMapperClosure Map
) {
  return (MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement)){
    .source = source,
    .Map    = Map,
  };
}

COREAPI Option(MapCursorTargetElement) MapCursorNext(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement)(
  MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) * self
) {
  auto next = MapCursorSourceCursorNext(&self->source);

  match(&next) {
    case(OptionSome, sourceElement) {
      return OptionSome(MapCursorTargetElement)(
        MapCursorMapperClosureCall(&self->Map, *sourceElement)
      );
    }
    case(OptionNone) {
      return OptionNone(MapCursorTargetElement)();
    }
  }
}

COREAPI Unit MapCursorDestroy(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement)(
  MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement) * self
) {
  MapCursorSourceCursorDestroy(&self->source);
  MapCursorMapperClosureDestroy(&self->Map);
  return_unit;
}

COREAPI IMPLEMENT(
  MapCursor(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement),
  Cursor(MapCursorTargetElement),
  .Next    = (void*)MapCursorNext(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement),
  .Destroy = (void*)MapCursorDestroy(MapCursorSourceCursor, MapCursorMapperClosure, MapCursorSourceElement, MapCursorTargetElement)
);
#endif // MAP_CURSOR_IMPLEMENTATION
#endif // MapCursorSourceCursor && MapCursorMapperClosure && MapCursorSourceElement && MapCursorTargetElement

#undef MAP_CURSOR_IMPLEMENTATION
#undef MapCursorSourceCursor
#undef MapCursorSourceCursorNext
#undef MapCursorSourceCursorDestroy
#undef MapCursorMapperClosure
#undef MapCursorMapperClosureCall
#undef MapCursorMapperClosureDestroy
#undef MapCursorSourceElement
#undef MapCursorTargetElement
