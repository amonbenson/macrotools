# `macrotools`

A collection of C header files that provide a basic control flow for any application. The tools include
- Logging
- Error Handling
- Unit Testing

## Installation

It is recommended to just copy the `include/macrotools` folder into your project. Make sure to keep all files inside the `macrotools` directory to avoid name clashes with existing headers.

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
<b style="color: #6BE4E6">DEBUG</b> examples/log.c:7: You see this?
<b style="color: #3FC4DE">INFO </b> examples/log.c:8: It's just for your own information ...
<b style="color: #FBC3A7">WARN </b> examples/log.c:9: This is not good.
<b style="color: #EC6A88">ERROR</b> examples/log.c:10: We got a serious problem!
</pre>
