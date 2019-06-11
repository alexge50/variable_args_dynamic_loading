//
// Created by alex on 6/11/19.
//

#ifndef VARIABLE_ARGS_DYNAMIC_LOADING_SYMBOLGEN_H
#define VARIABLE_ARGS_DYNAMIC_LOADING_SYMBOLGEN_H

#include "Arguments.h"

template<typename T>
std::string get_type_name()
{
    if constexpr (std::is_same_v<T, int>)
        return "int";
    else if constexpr (std::is_same_v<T, float>)
        return "float";

    return "";
}

template<typename T>
void dummy() {}

struct Module
{
public:
    const auto& get() { return info; }

    template<typename ReturnType, typename... Args>
    void def(const std::string& name, ReturnType(*f)(Args...), std::array<std::string, sizeof...(Args)> arg_names = {})
    {
        std::array arg_types = {get_type_name<Args>()...};
        std::unordered_map<std::string, std::string> argumentTypes;

        for(int i = 0; i < sizeof...(Args); i++)
            argumentTypes[arg_names[i]] = arg_types[i];

        info.push_back({name, std::move(argumentTypes), get_type_name<ReturnType>(), Function{[f, arg_names, arg_types](const Arguments& arguments){
            int i = -1;
            return f((dummy<Args>, i++, (arg_types[i] == "int" ? std::get<int>(arguments.at(arg_names[i])) : std::get<float>(arguments.at(arg_names[i]))))...);
        }}});
    }

    void register_functions();

private:
    FunctionsInfo info;
};

#define MODULE_EXPORT() \
EXPORT FunctionsInfo export_init()\
{\
    Module module; \
    module.register_functions();\
    return module.get();\
}\
void Module::register_functions()


#endif //VARIABLE_ARGS_DYNAMIC_LOADING_SYMBOLGEN_H
