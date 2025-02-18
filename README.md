# Core

Core is a collection of reusable C general purpose functions as well as generic data structures.

## Usage

```c
#include <core/Core.h>
#include <stdio.h>

#define ListElement Int
#include <core/collections/List.h>

#define ListElement Char
#include <core/collections/List.h>

Int32 main() {
  var index = ListDefault(Int)();
  var chars = ListDefault(Char)();

  for (var i = 0; i < 26; ++i) {
    ListAppend(Int)(&index, i);
    ListAppend(Char)(&chars, 'a' + i);
  }

  for (var i = 0; i < ListCount(Int)(&index); ++i) {
    printf("%d: ", ListAt(Int)(&index, i));
    printf("%c\n", ListAt(Char)(&chars, i));
  }

  ListDestroy(Int)(list);
  ListDestroy(Char)(chars);

  return 0;
}
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

[MIT](LICENSE)
