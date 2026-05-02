#ifndef Option
#include <core/Core.h>

typedef enum : UInt8 {
  Option_None,
  Option_Some,
} OptionTag;

#define Option(OptionValue) GENERIC(Option, OptionValue)
#define OptionNone(OptionValue) CONCAT(Option(OptionValue), None)
#define OptionSome(OptionValue) CONCAT(Option(OptionValue), Some)
#define OptionClone(OptionValue) CONCAT(Option(OptionValue), Clone)
#define OptionDestroy(OptionValue) CONCAT(Option(OptionValue), Destroy)
#endif

#ifndef OptionValue
#error Type parameter 'OptionValue' is not defined.
#endif

#ifndef OptionValueClone
#define OptionValueClone(value) (*(value))
#endif

#ifndef OptionValueDestroy
#define OptionValueDestroy(value) ((void)(value))
#endif

#ifdef OptionValue
typedef struct Option(OptionValue) {
  OptionTag tag;
  OptionValue value;
} Option(OptionValue);

Option(OptionValue) OptionNone(OptionValue)();
Option(OptionValue) OptionSome(OptionValue)(OptionValue value);
Option(OptionValue) OptionClone(OptionValue)(Option(OptionValue) const* option);
void OptionDestroy(OptionValue)(Option(OptionValue) * option);

#ifdef OPTION_IMPLEMENTATION
Option(OptionValue) OptionNone(OptionValue)() {
  return (Option(OptionValue)){
    .tag   = Option_None,
    .value = {0},
  };
}

Option(OptionValue) OptionSome(OptionValue)(OptionValue value) {
  return (Option(OptionValue)){
    .tag   = Option_Some,
    .value = value,
  };
}

Option(OptionValue) OptionClone(OptionValue)(Option(OptionValue) const* option) {
  switch (option->tag) {
    case Option_None: return OptionNone(OptionValue)();
    case Option_Some: return OptionSome(OptionValue)(OptionValueClone(&option->value));
  }
}

void OptionDestroy(OptionValue)(Option(OptionValue) * option) {
  if (option->tag == Option_Some) {
    OptionValueDestroy(&option->value);
  }

  option->tag   = Option_None;
  option->value = (OptionValue){0};
}
#endif // OPTION_IMPLEMENTATION
#endif // OptionValue

#undef OptionValue
#undef OptionValueClone
#undef OptionValueDestroy
#undef OPTION_IMPLEMENTATION
