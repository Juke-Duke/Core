#ifndef OptionValue
#error "Type parameter 'OptionValue' is not defined."
#define OptionValue int
#endif

#include <core/Generic.h>

#ifndef Option
typedef enum {
  Option_None,
  Option_Some,
} OptionTag;

#define Option(OptionValue) GENERIC(Option, OptionValue)
#define OptionNone(OptionValue) GENERIC(None, OptionValue)
#define OptionSome(OptionValue) GENERIC(Some, OptionValue)
#endif

typedef struct {
  OptionValue value;
  OptionTag tag;
} Option(OptionValue);

static Option(OptionValue) OptionNone(OptionValue)() {
  return (Option(OptionValue)){
    .value = (OptionValue){},
    .tag = Option_None,
  };
}

static Option(OptionValue) OptionSome(OptionValue)(OptionValue value) {
  return (Option(OptionValue)){
    .value = value,
    .tag = Option_Some,
  };
}

#undef OptionValue
