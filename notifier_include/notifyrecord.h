#ifndef NOTIFYRECORD_H
#define NOTIFYRECORD_H

#include <memory>
#include <string>

#include "sender_reciever_traits.h"


template<class MonitorType>
class NotifyRecord
{
public:
    template<class Listener>
    void AddListener(MonitorType nvalue,Listener listner, const std::string &displaystr)
    {
        listentraits_.AddListner(nvalue, listner, displaystr);
    }

    template<class SenderType>
    void OnCallingUpdate(SenderType sender, const std::string &displaystr)
    {
        sender_.reset(new Sender<SenderType>(sender, displaystr));
    }

    void OnCalledUpdate()
    {
        sender_.reset();
    }

private:
    std::shared_ptr<NotifyObj> sender_;
    SenderRecieverTraits<MonitorType> listentraits_;
};

#endif // NOTIFYRECORD_H
