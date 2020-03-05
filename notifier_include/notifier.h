#ifndef __NOTIFIER__
#define __NOTIFIER__

#include <functional>
#include <memory>
#include <vector>

#include "update_traits.h"

enum class MonitorType;

class Notifier
{
public:
    virtual ~Notifier() {}
};

template <class NotifyParamType>
class GenericNotifier : public Notifier
{
public:
    virtual ~GenericNotifier() {}

    void onUpdate(NotifyParamType param)
    {
        for (auto functor : update_fun_) {
            functor(param);
        }
    }

    void RegisterFunction(UpdateTraits<NotifyParamType> function)
    {
        update_fun_.push_back(function);
    }

private:
    UpdateList<NotifyParamType> update_fun_;
};

template <>
class GenericNotifier<void> : public Notifier
{
public:
    virtual ~GenericNotifier() {}

    void onUpdate()
    {
        for (auto functor : update_fun_) {
            functor();
        }
    }

    void RegisterFunction(UpdateTraits<void> function)
    {
        update_fun_.push_back(function);
    }

private:
    UpdateList<void> update_fun_;
};

#endif
