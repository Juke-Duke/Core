#include <core/Any.h>
#include <stdlib.h>

Any* AnyClone(Any const* any) {
  return InterfaceDispatch(Clone, any);
}

void AnyDestroy(Any* any) {
  InterfaceDispatch(Destroy, any);
  free(any);
}
