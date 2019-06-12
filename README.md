# Dynamic Arguments
Call functions imported from shared objects / dlls with a variable number of arguments and types.

## How to use
so/dll source file:
```cpp
#include <Arguments.h>
#include <SymbolGen.h>

using MyTypes = TypeRegister<int, float, std::vector<int>>;

int f(int a, float b, int c, std::vector<int> x)
{
    return 0;
}

MODULE_EXPORT(MyTypes,
{
    def("f", f, {"a", "b", "c", "x"});
})
```

loader:
```cpp
#include <Arguments.h>
#include <Module.h>

using MyTypes = TypeRegister<int, float, std::vector<int>>;

int main()
{
    Module<MyTypes> module("path/to/so");

    module.getFunctionsInfo()[0].function({
        1, 1.0, 1, std::vector<int>{1}
    });

    return 0;
}
```
## TODO
* windows support
* add unit tests
* search common paths given a shared object name