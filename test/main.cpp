#include <iostream>
#include <dlfcn.h>

#include "Arguments.h"
#include "Module.h"

int main()
{
    Module module("./libmodule.so");

    module.getFunctionsInfo()[0].function({
       {"lenny", {1}}
    });

    return 0;
}