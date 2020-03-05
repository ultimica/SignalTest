#ifndef ENUMSTR_H
#define ENUMSTR_H

#include <map>
#include <string>

template<class EnumType>
using EnumStrMap=std::map<std::string, EnumType>;

template <class EnumType>
struct EnumMap
{
    static_assert(std::is_enum<EnumType>::value,
                    "EnumType must be an enumeration type!");

   static  EnumStrMap<EnumType> enumsets_;
};


template<class EnumType>
EnumStrMap<EnumType> EnumMap<EnumType>::enumsets_;

struct RegisterEnum
{
    template <class EnumType>
    constexpr static void CreatePair(const std::string &str, EnumType nvalue)
    {
        EnumMap<EnumType>::enumsets_.emplace(str, nvalue);
    }

    template<class EnumType>
    constexpr static EnumStrMap<EnumType> GetDefinedEnumMap()
    {
        return EnumMap<EnumType>::enumsets_;
    }

    template <class EnumType>
    static EnumType GetEnum(const std::string &str,
                            const EnumType &defaultvalue)
    {
        auto iter = EnumMap<EnumType>::enumsets_.find(str);
        if (iter != EnumMap<EnumType>::enumsets_.end())
            return iter->second;
        else
            return defaultvalue;
    }
};

#define CREATE_ENUMSTR(EnumValue) \
    RegisterEnum::CreatePair(#EnumValue, EnumValue);


#endif  // ENUMSTR_H
