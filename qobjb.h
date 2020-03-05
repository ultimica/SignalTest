#ifndef QOBJB_H
#define QOBJB_H

#include <QObject>

class QOBJB: public QObject
{
    Q_OBJECT
public:
    void SlotReciever(bool  , bool);
};

#endif // QOBJB_H
