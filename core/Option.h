#ifndef OptionValue
#error Type parameter 'OptionValue' is not defined.
#endif

#ifndef Option
#include <core/Core.h>
#include <core/Generic.h>

typedef enum : UInt8 {
  Option_None,
  Option_Some,
} OptionTag;

#define Option(OptionValue) GENERIC(Option, OptionValue)
#define OptionNone(OptionValue) GENERIC(OptionNone, OptionValue)
#define OptionSome(OptionValue) GENERIC(OptionSome, OptionValue)
#endif

typedef struct Option(OptionValue) {
  OptionTag tag;
  OptionValue value;
} Option(OptionValue);

static Option(OptionValue) OptionNone(OptionValue)() {
  return (Option(OptionValue)){
    .tag   = Option_None,
    .value = {},
  };
}

static Option(OptionValue) OptionSome(OptionValue)(OptionValue value) {
  return (Option(OptionValue)){
    .tag   = Option_Some,
    .value = value,
  };
}

#undef OptionValue
