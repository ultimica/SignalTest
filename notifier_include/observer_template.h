#ifndef OBSERVER_TEMPLATE_H
#define OBSERVER_TEMPLATE_H

/// Essential template function for supporting implementation of observer

#include <memory>
#include <type_traits>

#include "data_monitor_manager.h"
#include "notifier.h"
#include "sender_reciever_traits.h"
#include "update_traits.h"

template <class MonitorType>
class ObseverTemplateInterface
{
public:
    using ObserverEnumType = MonitorType;

    virtual ~ObseverTemplateInterface() {}
    template <class ListenerType, MonitorType nvalue>
    void RegisterNotifyFunction(NotifyFunType<MonitorType, nvalue> fun,
                                ListenerType listner,
                                const std::string &str)
    {
        Internal_RegisterNotifyFunction<nvalue>(fun);
        listentraits_.AddListner(nvalue, listner, str);
    }

    template <class SenderType, MonitorType nvalue, class Parameter>
    void CallUpdate(Parameter param, SenderType sender, const std::string &str)
    {
        sender_.reset(new Sender<SenderType>(sender, str));
        Internal_CallUpdate<nvalue>(param);
        sender_.reset();
    }

    template <class SenderType, MonitorType nvalue>
    void CallUpdate(SenderType sender, const std::string &str)
    {
        sender_.reset(new Sender<SenderType>(sender, str));
        Internal_CallUpdate<nvalue>();
        sender_.reset();
    }

protected:
    template <MonitorType nvalue>
    void Internal_RegisterNotifyFunction(NotifyFunType<MonitorType, nvalue> fun)
    {
        auto notiflist = MONMAN(MonitorType).GetNotifier(nvalue);
        for (auto notifier : notiflist) {
            auto gennotifier = dynamic_cast<
                GenericNotifier<NotifyFunParameter<MonitorType, nvalue>> *>(
                notifier);
            if (gennotifier) {
                gennotifier->RegisterFunction(fun);
            }
        }
    }

    template <MonitorType nvalue, class Parameter>
    void Internal_CallUpdate(Parameter param)
    {
        //        if(std::is_pointer<T>::value)
        //            auto
        //            ptr=dynamic_cast<NotifyFunParameter<MonitorType,nvalue>>(param);

        auto notiflist = MONMAN(MonitorType).GetNotifier(nvalue);
        for (auto notifier : notiflist) {
            auto gennotifier = dynamic_cast<
                GenericNotifier<NotifyFunParameter<MonitorType, nvalue>> *>(
                notifier);
            if (gennotifier) {
                gennotifier->onUpdate(param);
            }
        }
    }

    template <MonitorType nvalue>
    void Internal_CallUpdate()
    {
        auto notiflist = MONMAN(MonitorType).GetNotifier(nvalue);
        for (auto notifier : notiflist) {
            auto gennotifier = dynamic_cast<GenericNotifier<void> *>(notifier);
            if (gennotifier) {
                gennotifier->onUpdate();
            }
        }
    }

    template <MonitorType nvalue>
    void Internal_RegisterNotifier()
    {
        MONMAN(MonitorType)
            .RegisterNotifier(new GenericNotifier<
                                  NotifyFunParameter<MonitorType, nvalue>>(),
                              nvalue);
    }

private:
    std::shared_ptr<NotifyObj> sender_;
    SenderRecieverTraits<MonitorType> listentraits_;
};

template <class MonitorType>
class SimpleObseverTemplateInterface
{
public:
    template <MonitorType value>
    struct NotifyGuard
    {
        NotifyGuard() { NotifyGuard::isnotifying_ = true; }
        ~NotifyGuard() { NotifyGuard::isnotifying_ = false; }

        static bool isnotifying_;
    };

    virtual ~SimpleObseverTemplateInterface() {}
    template <MonitorType nvalue>
    void RegisterNotifyFunction(NotifyFunType<MonitorType, nvalue> fun)
    {
        Internal_RegisterNotifyFunction<nvalue>(fun);
    }

    template <MonitorType nvalue, class Parameter>
    void CallUpdate(Parameter&& param)
    {
        Internal_CallUpdate<nvalue>(param);
    }

    template <MonitorType nvalue>
    void CallUpdate()
    {
        if (NotifyGuard<nvalue>::isnotifying_)
            return;
        NotifyGuard<nvalue> guard;
        Internal_CallUpdate<nvalue>();
    }

    template <MonitorType nvalue>
    void RegisterNotifier()
    {
        MONMAN(MonitorType)
            .RegisterNotifier(new GenericNotifier<
                                  NotifyFunParameter<MonitorType, nvalue>>(),
                              nvalue);
    }

protected:
    template <MonitorType nvalue>
    void Internal_RegisterNotifyFunction(NotifyFunType<MonitorType, nvalue> fun)
    {
        auto notiflist = MONMAN(MonitorType).GetNotifier(nvalue);
        for (auto notifier : notiflist) {
            auto gennotifier = dynamic_cast<
                GenericNotifier<NotifyFunParameter<MonitorType, nvalue>> *>(
                notifier);
            if (gennotifier) {
                gennotifier->RegisterFunction(fun);
            }
        }
    }

    template <MonitorType nvalue, class Parameter>
    void Internal_CallUpdate(Parameter&& param)
    {
        //        if(std::is_pointer<T>::value)
        //            auto
        //            ptr=dynamic_cast<NotifyFunParameter<MonitorType,nvalue>>(param);

        auto notiflist = MONMAN(MonitorType).GetNotifier(nvalue);
        for (auto notifier : notiflist) {
            auto gennotifier = static_cast<GenericNotifier<NotifyFunParameter<MonitorType, nvalue>> *>(notifier);
            if (gennotifier) {
                gennotifier->onUpdate(param);
            }
        }
    }

    template <MonitorType nvalue>
    void Internal_CallUpdate()
    {
        auto notiflist = MONMAN(MonitorType).GetNotifier(nvalue);
        for (auto notifier : notiflist) {
            auto gennotifier = static_cast<GenericNotifier<void> *>(notifier);
            if (gennotifier) {
                gennotifier->onUpdate();
            }
        }
    }

private:
};

template <class MonitorType>
template <MonitorType value>
bool SimpleObseverTemplateInterface<MonitorType>::NotifyGuard<
    value>::isnotifying_ = false;
#endif
