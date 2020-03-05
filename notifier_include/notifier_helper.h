#ifndef NOTIFIERHELPER_H
#define NOTIFIERHELPER_H

#include "data_monitor_manager.h"
#include "notifier.h"
#include "update_traits.h"

template <class ParamType, class MonitorEnumType>
class NotifierHelper
{
public:
    static void RegisterNotifyFunction(MonitorEnumType montype,
                                       UpdateTraits<ParamType> fun)
    {
        auto notiflist = MONMAN(MonitorEnumType).GetNotifier(montype);
        for (auto notifier : notiflist) {
            auto gennotifier =
                dynamic_cast<GenericNotifier<ParamType> *>(notifier);
            if (gennotifier) {
                gennotifier->RegisterFunction(fun);
            }
        }
    }
    static void RegisterNotifier(MonitorEnumType montype)
    {
        MONMAN(MonitorEnumType)
            .RegisterNotifier(new GenericNotifier<ParamType>(), montype);
    }

    static void CallUpdate(MonitorEnumType montype, ParamType param)
    {
        auto notiflist = MONMAN(MonitorEnumType).GetNotifier(montype);
        for (auto notifier : notiflist) {
            auto gennotifier =
                dynamic_cast<GenericNotifier<ParamType> *>(notifier);
            if (gennotifier) {
                gennotifier->onUpdate(param);
            }
        }
    }
};

template <class MonitorEnumType>
class NotifierHelper<void, MonitorEnumType>
{
public:
    static void RegisterNotifyFunction(MonitorEnumType montype,
                                       UpdateTraits<void> fun)
    {
        auto notiflist = MONMAN(MonitorEnumType).GetNotifier(montype);
        for (auto notifier : notiflist) {
            auto gennotifier = dynamic_cast<GenericNotifier<void> *>(notifier);
            if (gennotifier) {
                gennotifier->RegisterFunction(fun);
            }
        }
    }
    static void RegisterNotifier(MonitorEnumType montype)
    {
        MONMAN(MonitorEnumType)
            .RegisterNotifier(new GenericNotifier<void>(), montype);
    }

    static void CallUpdate(MonitorEnumType montype)
    {
        auto notiflist = MONMAN(MonitorEnumType).GetNotifier(montype);
        for (auto notifier : notiflist) {
            auto gennotifier = dynamic_cast<GenericNotifier<void> *>(notifier);
            if (gennotifier) {
                gennotifier->onUpdate();
            }
        }
    }
};

#define TEMPLATEFUNCONSTRUCT(CLASSNAME, MONITORTYPE, PARAMETYPE)               \
    void                                                                       \
    CLASSNAME::Internal_RegisterNotifyFunction(MONITORTYPE montype,            \
                                               UpdateTraits<PARAMETYPE> fun)   \
    {                                                                          \
        NotifierHelper<PARAMETYPE,                                             \
                       MONITORTYPE>::RegisterNotifyFunction(montype, fun);     \
    }                                                                          \
                                                                               \
    void CLASSNAME::Internal_RegisterNotifier(MONITORTYPE montype)             \
    {                                                                          \
        NotifierHelper<PARAMETYPE, MONITORTYPE>::RegisterNotifier(montype);    \
    }                                                                          \
                                                                               \
    void CLASSNAME::Internal_CallUpdate(MONITORTYPE montype, PARAMETYPE param) \
    {                                                                          \
        NotifierHelper<PARAMETYPE, MONITORTYPE>::CallUpdate(montype, param);   \
    }

#define TEMPLATEFUNCONSTRUCT_VOID(CLASSNAME, MONITORTYPE)                   \
    void CLASSNAME::Internal_RegisterNotifyFunction(MONITORTYPE montype,    \
                                                    UpdateTraits<void> fun) \
    {                                                                       \
        NotifierHelper<void, MONITORTYPE>::RegisterNotifyFunction(montype,  \
                                                                  fun);     \
    }                                                                       \
                                                                            \
    void CLASSNAME::Internal_RegisterNotifier(MONITORTYPE montype)          \
    {                                                                       \
        NotifierHelper<void, MONITORTYPE>::RegisterNotifier(montype);       \
    }                                                                       \
                                                                            \
    void CLASSNAME::Internal_CallUpdate(MONITORTYPE montype)                \
    {                                                                       \
        NotifierHelper<void, MONITORTYPE>::CallUpdate(montype);             \
    }

#endif  // NOTIFIERHELPER_H
