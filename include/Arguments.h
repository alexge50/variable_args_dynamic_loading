//
// Created by alex on 6/11/19.
//

#ifndef VARIABLE_ARGS_DYNAMIC_LOADING_ARGUMENTS_H
#define VARIABLE_ARGS_DYNAMIC_LOADING_ARGUMENTS_H

#include <vector>
#include <functional>
#include <variant>
#include <unordered_map>

using Type = std::variant<int, float>;
using Arguments = std::vector<Type>;
using Function = std::function<Type(const Arguments&)>;

struct FunctionInfo
{
    std::string name;
    std::unordered_map<std::string, std::string> argumentTypes;
    std::string returnType;
    Function function;
};

using FunctionsInfo = std::vector<FunctionInfo>;

using ExportedSymbols = FunctionsInfo(*)();

#ifdef __WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((__visibility__("default")))
#endif

#endif //VARIABLE_ARGS_DYNAMIC_LOADING_ARGUMENTS_H
