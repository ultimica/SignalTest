#ifndef OBSERVER_MACRO_H
#define OBSERVER_MACRO_H

////Helper macro for easier using

#define REGISTER_NOTIFY_NAME_VOIDPARAM(SingltonInstance, MonitorType, Functor, Listener)  \
    SingltonInstance                                                           \
        .RegisterNotifyFunction<decltype(Listener),MonitorType>(std::bind(&Functor,               \
                                                       Listener), \
                                             Listener,                         \
                                             std::string(#Functor));


#define REGISTER_NOTIFY_NAME(SingltonInstance, MonitorType, Functor, Listener) \
    SingltonInstance                                                           \
        .RegisterNotifyFunction<decltype(Listener),MonitorType>(std::bind(&Functor,               \
                                                       Listener,               \
                                                       std::placeholders::_1), \
                                             Listener,                         \
                                             std::string(#Functor));

#define REGISTER_NOTIFY_LAMBDA(SingltonInstance,                      \
                               MonitorType,                           \
                               Functor,                               \
                               Listener,                              \
                               FunName)                               \
    SingltonInstance.RegisterNotifyFunction<decltype(Listener),MonitorType>(Functor,     \
                                                         Listener,    \
                                                         std::string( \
                                                             FunName));

#define REGISTER_NOTIFY_AUTO(SingltonInstance, MonitorType, Functor, Listener) \
    REGISTER_NOTIFY_LAMBDA(SingltonInstance,                                   \
                           MonitorType,                                        \
                           Functor,                                            \
                           Listener,                                           \
                           std::string(__PRETTY_FUNCTION__));

#define NOTIFY(SingltonInstance, MonitorType, Parameter, Sender) \
    SingltonInstance.CallUpdate<decltype(Sender), MonitorType,decltype(Parameter)>(Parameter,                       \
                                Sender,                          \
                                std::string(__PRETTY_FUNCTION__));

#define NOTIFY_VOID(SingltonInstance, MonitorType, Sender) \
    SingltonInstance.CallUpdate<decltype(Sender), MonitorType>(Sender,                    \
                                std::string(__PRETTY_FUNCTION__));

#endif
