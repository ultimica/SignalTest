#ifndef DEVICE_INTERNAL_COMMUNICATOR_H
#define DEVICE_INTERNAL_COMMUNICATOR_H

#include <QString>

#include <tuple>

#include "observer_template.h"
#include "observernotifier.h"
#include "singleton_template.h"
#include "update_traits.h"

enum class DeviceViewInterProcess
{
    DVIP_ERROR = -1,

    DVIP_UNDOREDOUPDATE,
    DVIP_PARM_TEST,
    DVIP_SIZE,
};




EXTERN_FUNTRAITS(DeviceViewInterProcess::DVIP_UNDOREDOUPDATE,void)

using UndoRedoParam = std::tuple<bool, bool>;
EXTERN_FUNTRAITS(DeviceViewInterProcess::DVIP_PARM_TEST,UndoRedoParam)



class DVVPObserver
{
public:
    template <DeviceViewInterProcess value, class Functor>
    void RegisterFunction(Functor fun)
    {
        obs_.RegisterNotifyFunction<value>(fun);
    }

    template <DeviceViewInterProcess nvalue, class Parameter>
    void CallUpdate(Parameter param)
    {
        obs_.CallUpdate<nvalue>(param);
    }

    template <DeviceViewInterProcess nvalue>
    void CallUpdate()
    {
        obs_.CallUpdate<nvalue>();
    }

    ~DVVPObserver() {}

    template <typename T>
    friend class TSingleton;

protected:
    DVVPObserver()
    {

        obs_.RegisterNotifier<DeviceViewInterProcess::DVIP_UNDOREDOUPDATE>();
        obs_.RegisterNotifier<DeviceViewInterProcess::DVIP_PARM_TEST>();
    }

private:
    SimpleObseverTemplateInterface<DeviceViewInterProcess> obs_;
};

#define DVVPOBS TSingleton<DVVPObserver>::GetInstance()

#endif  // DEVICE_INTERNAL_COMMUNICATOR_H
