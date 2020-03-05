#ifndef DATA_MON_MANAGER
#define DATA_MON_MANAGER

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

#include "notifier.h"

enum class MonitorType;

class Notifier;
using ListOfNotifier = std::vector<Notifier *>;
// using NotifierMap = std::map<MonitorType, ListOfNotifier>;

template <class MonType>
using GenericNotifierMap = std::map<MonType, ListOfNotifier>;

template <class MonType>
class MonitorMan
{
public:
    static MonitorMan &Instance()
    {
        static MonitorMan<MonType> g_staticInstance;
        return g_staticInstance;
    }

    ~MonitorMan()
    {
        auto pos = notifier_map_.begin();
        auto endpos = notifier_map_.end();
        for (; pos != endpos; pos++) {
            for (auto elm : pos->second)
                delete elm;
        }
        notifier_map_.clear();
    }

    void RegisterNotifier(Notifier *notifier, MonType montype)
    {
        notifier_map_[montype].push_back(notifier);
    }

    void UnRegister(Notifier *notifier)
    {
        auto pos = notifier_map_.begin();
        auto endpos = notifier_map_.end();
        for (; pos != endpos; pos++) {
            auto curvec = pos->second;
            curvec.erase(std::remove(curvec.begin(), curvec.end(), notifier),
                         curvec.end());
        }
        if (notifier)
            delete notifier;
    }

    ListOfNotifier GetNotifier(MonType montype)
    {
        return notifier_map_[montype];
    }

private:
    MonitorMan() {}

    GenericNotifierMap<MonType> notifier_map_;
};

#define MONMAN(MonitorEnumType) MonitorMan<MonitorEnumType>::Instance()
#endif
