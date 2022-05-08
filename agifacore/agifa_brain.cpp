// Project AGIFA/Core                                                         //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_brain.cpp                                                //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include <iostream>
#include <time.h>

#include "agifa_brain.h"

namespace agifa_core
{

AgifaBrain::AgifaBrain() :
    m_isRun( false ),
    m_nodeIndex( EmptyIndex )
{
}

AgifaBrain::~AgifaBrain()
{
}

bool AgifaBrain::SetSensor( agifa_base::id_t sensorId, agifa_base::result_t result )
{
    QMutexLocker locker( &m_brainMutex );
    AgifaSensor* pSensor = m_system.SearchSensor( sensorId );
    if( pSensor )
    {
        pSensor->SetResult( result );
        return true;
    }
    return false;
}
bool AgifaBrain::GetSensor( agifa_base::id_t sensorId, agifa_base::result_t result)
{
    QMutexLocker locker( &m_brainMutex );
    AgifaSensor* pSensor = m_system.SearchSensor( sensorId );
    if( pSensor )
    {
        result = pSensor->GetResult();
        bool isResultChanged = pSensor->IsResultChanged();
        pSensor->SetResultChanged( false ); // действие забрали снаружи - сбрасываем флаг изменения
        return isResultChanged;
    }
    return false;
}

bool AgifaBrain::SetTarget( agifa_base::id_t sensorId, agifa_base::target_t target )
{
    QMutexLocker locker( &m_brainMutex );
    AgifaSensor* pSensor = m_system.SearchSensor( sensorId );
    if( pSensor )
    {
        pSensor->SetTarget( target );
        return true;
    }
    return false;
}

bool AgifaBrain::GetTarget( agifa_base::id_t sensorId, agifa_base::target_t target)
{
    QMutexLocker locker( &m_brainMutex );
    AgifaSensor* pSensor = m_system.SearchSensor( sensorId );
    if( pSensor )
    {
        target = pSensor->GetTarget();
        bool isTargetChanged = pSensor->IsTargetChanged();
        pSensor->SetTargetChanged( false ); // действие забрали снаружи - сбрасываем флаг изменения
        return isTargetChanged;
    }
    return false;
}

bool AgifaBrain::GetMotor( agifa_base::id_t motorId, agifa_base::action_t& action )
{
    QMutexLocker locker( &m_brainMutex );
    AgifaMotor* pMotor = m_system.SearchMotor( motorId );
    if( pMotor )
    {
        action = pMotor->GetAction();
        bool isActionChanged = pMotor->IsActionChanged();
        pMotor->SetActionChanged( false ); // действие забрали снаружи - сбрасываем флаг изменения
        return isActionChanged;
    }
    return false;
}

bool AgifaBrain::SetNodeIndex( index_t index )
{
    QMutexLocker locker( &m_brainMutex );
    m_nodeIndex = index;
    return true;
}

void AgifaBrain::Wait()
{
    int delay = 1;
    struct timespec ts = { delay/10, 1 };
    timespec remaining;
    nanosleep( &ts, &remaining );
}

void AgifaBrain::doWork()
{
    QString result;
    m_isRun = true;

    std::cout << "AgifaBrain::run1()\n";

    while( m_isRun )
    {
        AgifaSensor* pSensor = m_system.SearchSensor( 0 );
        AgifaMotor* pMotor = m_system.SearchMotor( 0 );
        if( pSensor && pMotor )
        {
            QMutexLocker locker( &m_brainMutex );
            if( !pMotor->IsActionChanged() )
            {
                // считываем текущий результат с датчика
                target_t result = pSensor->GetResult();
                // считываем требуемый результат с датчика
                target_t target = pSensor->GetTarget();
                AgifaNode* pNode = m_system.SearchNode( m_nodeIndex );
                if( pNode )
                {
                    // акцептер действия
                    bool acceptorResult = pNode->ActionAcceptor( target, result );
                    if( acceptorResult )
                    {
                        // акцептор действия сработал - требуемый результат достигнут
                        // добавляем родительский узел
                        m_system.AddNode( new AgifaNode( m_nodeIndex+1 ) );
                    }
                    else
                    {
                        // выполняем очередное действие ориентировочно-исследовательской реакции
                        pNode->SynthesisOfAction( *pMotor );
                    }
                }
            }
        }


        std::cout << "AgifaBrain::while()\n";
        Wait();
    }

    std::cout << "AgifaBrain::run2()\n";

    emit resultReady( result );
}

void AgifaBrain::exitWork()
{
    m_isRun = false;
}

}
