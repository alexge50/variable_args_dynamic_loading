#include <iostream>
#include <dlfcn.h>

#include "Arguments.h"
#include "Module.h"

#include "TypeRegister.h"

int main()
{
    Module<MyTypes> module("./libmodule.so");

    module.getFunctionsInfo()[0].function({
        1
    });

    return 0;
}