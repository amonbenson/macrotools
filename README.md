# `macrotools`

A collection of C header files that provide a basic control flow for any application. The tools include
- [Logging](#logging)
- [Error Handling](#error-handling)
- [Unit Testing](#unit-testing)

## Installation

Just copy the `include/macrotools` folder into your own project's include directory. Make sure to keep the `macrotools` subdirectory to avoid name clashes with existing headers.

Alternatively, you can also clone this repository (as a submodule) and add the folder `<repo-name>/include` to your lsit of include directories. Please beware of the [caveats when using git submodules](https://blog.timhutt.co.uk/against-submodules/).

## Logging

### Example

```c
#define LOG_GLOBAL_LEVEL LOG_LEVEL_DEBUG
#include "macrotools/log.h"

int main(int argc, const char *argv[]) {
    LOG_TRACE("The global level is DEBUG, so this should not get printed.");
    LOG_DEBUG("You see this?");
    LOG_INFO("It's just for your own information ...");
    LOG_WARN("This is not good.");
    LOG_ERROR("We got a serious problem!");

    return 0;
}
```

```bash
$ make examples && ./build/examples/log
```

```console
DEBUG examples/log.c:7: You see this?
INFO  examples/log.c:8: It's just for your own information ...
WARN  examples/log.c:9: This is not good.
ERROR examples/log.c:10: We got a serious problem!
```

## Error handling

### Example

```c
#include <stdio.h>
#include "macrotools/error.h"

int good_function() { return 0; }

int bad_function() { return 1; }

int main(int argc, const char *argv[]) {
    TRY_OR_RETURN(good_function(), "good_function() failed.");
    TRY_OR_RETURN(TRY_ASSERT(0 == 0), "Assertion failed: 0 == 0. The universe is broken.");
    TRY_OR_WARN(bad_function(), "bad_function() failed. Continuing...");
    TRY_OR_RETURN(bad_function(), "bad_function() failed again! Who could have known?");

    return 0; // never reached
}
```

```bash
$ make examples && ./build/examples/error
```

```console
WARN  examples/error.c:11: Error 1: bad_function() failed. Continuing...
ERROR examples/error.c:12: Error 1: bad_function() failed again! Who could have known?
```
