#ifndef UPDATE_TRAITS_H
#define UPDATE_TRAITS_H

/// Update functon template for Observer

#include <functional>
#include <vector>

template <class NotifyParamType>
class ParamTypeTraits
{
public:
    using funtraits = std::function<void(NotifyParamType)>;
};

template <>
class ParamTypeTraits<void>
{
public:
    using funtraits = std::function<void()>;
};

template <class NotifyParamType>
using UpdateTraits = typename ParamTypeTraits<NotifyParamType>::funtraits;

template <class NotifyParamType>
using UpdateList = std::vector<UpdateTraits<NotifyParamType>>;


template <typename T>
struct FalseType : std::false_type
{
};


template <class ClassEnum, ClassEnum nvalue>
struct NotifyFunTraits
{
    static_assert(std::is_enum<ClassEnum>::value,
                  "ClassEnum must be enumeration type!");
    static_assert(FalseType<ClassEnum>::value,
                  "You must specifiy the function traits!");

    template <class Parameter>
    using FunProtoType = UpdateTraits<Parameter>;
    template <class Parameter>
    using FunParameter = Parameter;
};


template <class ClassEnum, ClassEnum nvalue>
using NotifyFunType = typename NotifyFunTraits<ClassEnum, nvalue>::FunProtoType;

template <class ClassEnum, ClassEnum nvalue>
using NotifyFunParameter = typename NotifyFunTraits<ClassEnum, nvalue>::FunParameter;


#define EXTERN_FUNTRAITS(Value, ParmType) \
    template <>                                     \
    struct NotifyFunTraits<decltype(Value), Value>         \
    {                                               \
        using FunProtoType = UpdateTraits<ParmType>;\
        using FunParameter = ParmType;\
    };
#endif  // UPDATE_TRAITS_H
