// Project AGIFA/Core                                                         //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_brain.h                                                  //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __AGIFA_BRAIN_H )
#define __AGIFA_BRAIN_H

#include <QtCore>
#include <QObject>

#include "agifa_system.h"

namespace agifa_core
{

using namespace agifa_base;

class AgifaBrain : public QObject
{
    Q_OBJECT
protected:
    QMutex m_brainMutex;
    bool m_isRun;
    AgifaSystem m_system;
    index_t m_nodeIndex;
public:
    AgifaBrain();
    virtual ~AgifaBrain();

    const AgifaSystem& GetSystem() const { return m_system; }
    AgifaSystem& GetSystem() { return m_system; }

    // потокобезопасная установка входных данных на датчик
    bool SetSensor( agifa_base::id_t sensorId, agifa_base::result_t result );
    // потокобезопасная установка требуемого результата на датчик
    bool SetTarget( agifa_base::id_t sensorId, agifa_base::target_t target );
    // потокобезопасная установка входных данных на датчик
    bool GetMotor( agifa_base::id_t motorId, agifa_base::action_t& action );
    // потокобезопасная установка индекса узла ДР
    bool SetNodeIndex( index_t index );
public slots:
    void doWork();
    void exitWork();
signals:
    void resultReady( const QString& result );
protected:
    void Wait();
};

}

#endif
