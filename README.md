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
// examples/log.c

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

<pre>
<b><code style="color: #6BE4E6">DEBUG</code></b> examples/log.c:7: You see this?
<b><code style="color: #3FC4DE">INFO </code></b> examples/log.c:8: It's just for your own information ...
<b><code style="color: #FBC3A7">WARN </code></b> examples/log.c:9: This is not good.
<b><code style="color: #EC6A88">ERROR</code></b> examples/log.c:10: We got a serious problem!
</pre>
