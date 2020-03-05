CONFIG+=c++14

INCLUDEPATH += $$PWD/

HEADERS  +=  $$PWD/update_traits.h \
    $$PWD/sender_reciever_traits.h \
    $$PWD/observer_macro.h \
    $$PWD/singleton_template.h \
    $$PWD/observer_template.h \
    $$PWD/notifier.h \
    $$PWD/notifier_helper.h \
    $$PWD/data_monitor_manager.h \
    $$PWD/notifyrecord.h \
    $$PWD/observernotifier.h \
    $$PWD/type_checker.h \
    $$PWD/enum_strmap.h



#LibPath = $$PWD/../../lib/
#LibName = notifier
#!debug_and_release|build_pass {
#    CONFIG(debug, debug|release) {
#        LibName = $$member(LibName, 0)d
#    }
#}
#LIBS += -L$$LibPath -l$$LibName

