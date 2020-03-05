#ifndef QOBJA_H
#define QOBJA_H

#include <QObject>

class QOBJA: public QObject
{
    Q_OBJECT
public:
signals:
    void EmitSignal(bool,bool);
};

#endif // QOBJA_H
