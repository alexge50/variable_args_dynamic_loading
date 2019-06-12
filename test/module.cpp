//
// Created by alex on 6/11/19.
//

#include <Arguments.h>
#include <SymbolGen.h>
#include "TypeRegister.h"

#include <iostream>

EXPORT int f(int lenny)
{
    std::cout << lenny << std::endl;
    return 1;
}

MODULE_EXPORT(MyTypes,
{
    def("f", f, {"lenny"});
})


