#ifndef SENDER_RECIEVER_TRAITS_H
#define SENDER_RECIEVER_TRAITS_H

//////class for recording Sender and Reciever function name and sequence

#include <map>
#include <string>
#include <vector>

class NotifyObj
{
public:
    virtual ~NotifyObj() {}
};

template <class SenderType>
class Sender : public NotifyObj
{
public:
    virtual ~Sender() {}
    Sender(SenderType sobj, const std::string &str)
      : obj_(sobj)
      , senderstr_(str)
    {
    }
    SenderType obj_;
    std::string senderstr_;
};

template <class ListnerType>
class Listener : public NotifyObj
{
public:
    Listener(ListnerType lisobj, const std::string &str)
      : obj_(lisobj)
      , recstr_(str)
    {
    }
    virtual ~Listener() {}
    ListnerType obj_;
    std::string recstr_;
};

template <class MonitorType>
class SenderRecieverTraits
{
public:
    ~SenderRecieverTraits()
    {
        auto pos = notifymap_.begin();
        auto endpos = notifymap_.end();
        for (; pos != endpos; pos++) {
            for (auto item : pos->second)
                delete item;
        }
        notifymap_.clear();
    }

    template <class SenderType, class ListnerType>
    void AddListner(SenderType typeenum,
                    ListnerType input,
                    const std::string &str)
    {
        notifymap_[typeenum].push_back(new Listener<ListnerType>(input, str));
    }
    std::map<MonitorType, std::vector<NotifyObj *>> notifymap_;
};

#endif
