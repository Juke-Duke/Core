#ifndef OptionValue
#error Type parameter 'OptionValue' is not defined
#endif

#ifndef OptionValueClone
#define OptionValueClone(value) (*(value))
#endif

#ifndef OptionValueDestroy
#define OptionValueDestroy(value) ((void)(value))
#endif

#ifndef Option
#include <core/Core.h>

#define Option(OptionValue) GENERIC(Option, OptionValue)
#define OptionNone(OptionValue) CONCAT(Option(OptionValue), None)
#define OptionSome(OptionValue) CONCAT(Option(OptionValue), Some)
#define OptionDefault(OptionValue) CONCAT(Option(OptionValue), Default)
#define OptionClone(OptionValue) CONCAT(Option(OptionValue), Clone)
#define OptionDestroy(OptionValue) CONCAT(Option(OptionValue), Destroy)
#endif

#ifdef OptionValue
typedef struct Option(OptionValue) union(
  Option,
  (OptionSome, OptionValue),
  (OptionNone)
) Option(OptionValue);

VARIANT_CREATE_DECL(Option(OptionValue), OptionSome(OptionValue), (OptionSome, OptionValue));
VARIANT_CREATE_DECL(Option(OptionValue), OptionNone(OptionValue), (OptionNone));
Option(OptionValue) OptionDefault(OptionValue)();
Option(OptionValue) OptionClone(OptionValue)(Option(OptionValue) const* option);
Unit OptionDestroy(OptionValue)(Option(OptionValue) * option);

#ifdef OPTION_IMPLEMENTATION
COREAPI VARIANT_CREATE_IMPL(Option(OptionValue), OptionSome(OptionValue), (OptionSome, OptionValue));
COREAPI VARIANT_CREATE_IMPL(Option(OptionValue), OptionNone(OptionValue), (OptionNone));

COREAPI Option(OptionValue) OptionDefault(OptionValue)() {
  return OptionNone(OptionValue)();
}

COREAPI Option(OptionValue) OptionClone(OptionValue)(Option(OptionValue) const* option) {
  match(option) {
    case(OptionSome, value) {
      return OptionSome(OptionValue)(OptionValueClone(value));
    }
    case(OptionNone) {
      return OptionNone(OptionValue)();
    }
  }
}

COREAPI Unit OptionDestroy(OptionValue)(Option(OptionValue) * option) {
  match(option) {
    case(OptionSome, value) {
      OptionValueDestroy(value);
    }
    default: break;
  }

  *option = OptionNone(OptionValue)();
  return_unit;
}
#endif // OPTION_IMPLEMENTATION
#endif // OptionValue

#undef OPTION_IMPLEMENTATION
#undef OptionValue
#undef OptionValueClone
#undef OptionValueDestroy
