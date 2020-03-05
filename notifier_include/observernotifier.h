#ifndef OBSERVERNOTIFIER_H
#define OBSERVERNOTIFIER_H

#include <type_traits>

#include "notifyrecord.h"
#include "observer_template.h"
#include "type_checker.h"

////Check if the same template class
// template <typename T>
// struct same_type_check<ObseverTemplateInterface<T>,T>
//{
//    static constexpr bool value = true;
//};


template <class MonitorType>
class ObserverNotifier
{
public:

    template<MonitorType nValue>
    struct Operation_Register
    {
        template <class ObserverTemplate,
                  class Functor>
                  //class ListenerType>
       static  void RegisterNotifyFunction(ObserverTemplate &observer,
                                    Functor functor)
                                    //ListenerType listen)
        {
            observer.RegisterNotifyFunction<nValue>(functor);
        }

       template <class ObserverTemplate>
       static void RegisterNotifier(ObserverTemplate &observer)
       {
           observer.template RegisterNotifier<nValue>();
       }

    };

    NotifyRecord<MonitorType> notifyrecord_;
};

//template<class MonitorType, MonitorType nvalue>
//using ObserverOp=typename ObserverNotifier<MonitorType>::Operation_Register<nvalue>;

#endif  // OBSERVERNOTIFIER_H
