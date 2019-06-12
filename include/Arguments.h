//
// Created by alex on 6/11/19.
//

#ifndef VARIABLE_ARGS_DYNAMIC_LOADING_ARGUMENTS_H
#define VARIABLE_ARGS_DYNAMIC_LOADING_ARGUMENTS_H

#include <any>
#include <vector>
#include <typeinfo>
#include <functional>

struct TypeInfo
{
    TypeInfo(const std::type_info& typeInfo): m_hashcode{typeInfo.hash_code()}, m_name{typeInfo.name()} {}

    TypeInfo(const TypeInfo&) = default;
    TypeInfo(TypeInfo&&) = default;

    TypeInfo& operator= (const TypeInfo&) = default;
    TypeInfo& operator= (TypeInfo&&) = default;

    bool operator==(const TypeInfo& rhs) const
    {
        if(m_hashcode == rhs.m_hashcode)
            return m_name == rhs.m_name;
        return false;
    }

    bool operator!=(const TypeInfo& rhs) const
    {
        return !this->operator==(rhs);
    }

    size_t hashcode() const { return m_hashcode; }
    const std::string& name() const { return m_name; }

private:
    size_t m_hashcode;
    std::string m_name;

};

using Type = std::any;
using Arguments = std::vector<Type>;
using Function = std::function<Type(const Arguments&)>;

struct FunctionInfo
{
    std::string name;
    std::vector<std::pair<std::string, TypeInfo>> argumentTypes;
    TypeInfo returnType;
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
