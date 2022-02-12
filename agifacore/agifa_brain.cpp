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
    m_isRun( false )
{
}

AgifaBrain::~AgifaBrain()
{
}

bool AgifaBrain::SetSensor( agifa_base::id_t sensorId, agifa_base::result_t result )
{
    QMutexLocker locker( & m_brainMutex );
    AgifaSensor* pSensor = m_system.SearchSensor( sensorId );
    if( pSensor )
    {
        pSensor->SetResult( result );
        return true;
    }
    return false;
}

bool AgifaBrain::GetMotor( agifa_base::id_t motorId, agifa_base::action_t& action )
{
    QMutexLocker locker( & m_brainMutex );
    AgifaMotor* pMotor = m_system.SearchMotor( motorId );
    if( pMotor )
    {
        action = pMotor->GetAction();
        return true;
    }
    return false;
}

void AgifaBrain::doWork()
{
    QString result;
    m_isRun = true;

    std::cout << "AgifaBrain::run1()\n";

    while( m_isRun )
    {
        std::cout << "AgifaBrain::while()\n";
        int delay = 30;
        struct timespec ts = { delay/10, 1 };
        timespec remaining;
        nanosleep( &ts, &remaining );
    }

    std::cout << "AgifaBrain::run2()\n";

    emit resultReady( result );
}

void AgifaBrain::exitWork()
{
    m_isRun = false;
}

}
