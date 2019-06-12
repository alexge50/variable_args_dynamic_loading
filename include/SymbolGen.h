//
// Created by alex on 6/11/19.
//

#ifndef VARIABLE_ARGS_DYNAMIC_LOADING_SYMBOLGEN_H
#define VARIABLE_ARGS_DYNAMIC_LOADING_SYMBOLGEN_H

#include "Arguments.h"

#include <any>
#include <vector>
#include <typeinfo>
#include <functional>


#include <iostream>

template <typename TypeRegister>
struct Module
{
public:
    const auto& get() { return info; }

    template<typename ReturnType, typename... Args>
    void def(const std::string& name, ReturnType(*f)(Args...), std::array<std::string, sizeof...(Args)> arg_names = {})
    {
        std::array arg_types = {TypeInfo{typeid(Args)}...};
        std::vector<std::pair<std::string, TypeInfo>> argumentTypes;

        argumentTypes.reserve(sizeof...(Args));
        for(int i = 0; i < sizeof...(Args); i++)
            argumentTypes.push_back({arg_names[i], arg_types[i]});

        info.push_back({name, std::move(argumentTypes), {typeid(ReturnType)}, Function<TypeRegister>{[f](const Arguments<TypeRegister>& arguments){
            int i = 0;
            return f(std::get<Args>(arguments[i++])...);
        }}});
    }

    void register_functions();

private:
    FunctionsInfo<TypeRegister> info;
};

#define MODULE_EXPORT(TypeRegister, FunctionRegistration) \
template <>\
void Module<TypeRegister>::register_functions()\
FunctionRegistration \
EXPORT FunctionsInfo<TypeRegister> export_init()\
{\
    Module<TypeRegister> module; \
    module.register_functions();\
    return module.get();\
}\
extern "C" EXPORT void* entry_point()\
{ \
    return reinterpret_cast<void*>(export_init); \
}


#endif //VARIABLE_ARGS_DYNAMIC_LOADING_SYMBOLGEN_H
