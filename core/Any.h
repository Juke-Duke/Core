#pragma once

#include <core/Core.h>

typedef interface(Any
) Any;

Any* AnyClone(Any const* any);
void AnyDestroy(Any* any);
