#ifndef RefT
#error "Type parameter 'RefT' is not defined"
#endif

#ifndef Ref
#include <core/Core.h>

#define Ref(RefT) GENERIC(Ref, RefT)
#define RefMut(RefT) GENERIC(RefMut, RefT)
#endif

#ifdef RefT
typedef RefT const* Ref(RefT);
typedef RefT* RefMut(RefT);
#endif

#undef RefT
