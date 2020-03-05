#include <QCoreApplication>
#include <QObject>
#include <QDebug>

#include <iostream>
#include "mysignal.h"
#include "qobja.h"
#include "qobjb.h"
#include <chrono>


#define CONNECTIONNUMBER 100000
#define EMITLOOP    1

struct TimeStamp
{
    TimeStamp()
    {
        begin = std::chrono::steady_clock::now();
    }
    ~TimeStamp()
    {
        end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;

    }
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end ;
};






struct ObjectA
{
    void EmitMySignal()
    {
       DVVPOBS.CallUpdate<DeviceViewInterProcess::DVIP_UNDOREDOUPDATE>();
    }
    void EmitParamSignal()
    {
        DVVPOBS.CallUpdate<DeviceViewInterProcess::DVIP_PARM_TEST>(UndoRedoParam(true,true));
    }
};

struct ObjectB
{
    ObjectB()
    {
        DVVPOBS.RegisterFunction<DeviceViewInterProcess::DVIP_UNDOREDOUPDATE>([this]()
        {
          //  std::cout<<"MyReciever BB"<<std::endl;
        });
    }
};

struct ObjectC
{
    ObjectC()
    {
        DVVPOBS.RegisterFunction<DeviceViewInterProcess::DVIP_PARM_TEST>([this](UndoRedoParam)
        {
           // DumpC();
        });
    }

//    void DumpC()
//    {
//        std::cout<<"MyReciever CC"<<std::endl;
//    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QOBJA aa;

    QOBJB b[CONNECTIONNUMBER];
    for(int i=0;i<CONNECTIONNUMBER;++i)
        QObject::connect(&aa,&QOBJA::EmitSignal,&b[i],&QOBJB::SlotReciever);


    {
    TimeStamp _t;
    for(int i=0;i<EMITLOOP;++i)
        aa.EmitSignal(true,true);
    }


    ObjectA mya;
    ObjectB myb[CONNECTIONNUMBER];
    {
    TimeStamp _t;
    for(int i=0;i<EMITLOOP;++i)
        mya.EmitMySignal();
    }

    ObjectC myc[CONNECTIONNUMBER];
    {
        TimeStamp _t;
        for(int i=0;i<EMITLOOP;++i)
            mya.EmitParamSignal();
    }



    return a.exec();
}
