//
// Created by alex on 6/11/19.
//

#ifndef VARIABLE_ARGS_DYNAMIC_LOADING_MODULE_H
#define VARIABLE_ARGS_DYNAMIC_LOADING_MODULE_H

#include <dlfcn.h>
#include <string>
#include "Arguments.h"

class Module
{
public:
    explicit Module(const std::string& name)
    {
        m_dlLib = dlopen(name.c_str(), RTLD_NOW);

        auto entry_point = reinterpret_cast<void*(*)()>(dlsym(m_dlLib, "entry_point"));

        m_importedFunctions = reinterpret_cast<ExportedSymbols>(entry_point())();
    }

    const FunctionsInfo& getFunctionsInfo() const { return m_importedFunctions; };

private:
    void* m_dlLib;
    FunctionsInfo m_importedFunctions;
};


#endif //VARIABLE_ARGS_DYNAMIC_LOADING_MODULE_H
