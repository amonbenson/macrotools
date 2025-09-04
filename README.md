# `macrotools`

[![CI](https://github.com/amonbenson/macrotools/actions/workflows/ci.yml/badge.svg)](https://github.com/amonbenson/macrotools/actions/workflows/ci.yml)

A collection of C header files that provide a basic control flow for any application. The tools include
- [Logging](#usage-logging)
- [Error Handling](#usage-error-handling)
- [Unit Testing](#usage-unit-testing)

## Installation

Just copy the `include/macrotools` folder into your own project's include directory. Make sure to keep the `macrotools` subdirectory to avoid name clashes with existing headers.

Alternatively, you can also clone this repository (as a submodule) and add the folder `<repo-name>/include` to your list of include directories. Please beware of the [caveats when using git submodules](https://blog.timhutt.co.uk/against-submodules/).

## Usage: Logging

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

## Usage: Error Handling

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

## Usage: Unit Testing

### Example

```c
#include <string.h>
#include "macrotools/test.h"

DESCRIBE(suite_one, "basic assertions") {
    IT("compares numbers") {
        EXPECT_EQ(1, 1);
        EXPECT_NE(1, 2);
        EXPECT(123 == 123);
    }
}

int always_twenty() {
    return 20;
}

DESCRIBE(suite_two, "advanced examples") {
    // you can declare local variables here. Note that they DO NOT get reset after each test run.
    const char *blub_str = "blub";

    IT("checks function return values") {
        EXPECT_EQ(always_twenty(), 20);
    }

    IT("checks strings (using strcmp)") {
        EXPECT_EQ(strcmp(blub_str, "blub"), 0);
    }
}

// List all your test suites here.
// Use TEST_MAIN_EXTERN(...) if you want to link test suites from separate c files.
TEST_MAIN(suite_one, suite_two)
```

```bash
$ make examples && ./build/examples/test
```

```console
basic assertions
  ✓ compares numbers

advanced examples
  ✓ checks function return values
  ✓ checks strings (using strcmp)

 PASSED 
Test Suites: 2 passed, 2 total.
Tests:       3 passed, 3 total.
```
