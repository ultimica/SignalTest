#ifndef TYPE_CHECKER_H
#define TYPE_CHECKER_H

template <typename T>
struct same_type_check
{
    template <typename TargetType>
    struct target_type
    {
        static constexpr bool value = false;
    };
};



#endif  // TYPE_CHECKER_H
