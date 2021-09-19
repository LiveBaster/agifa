// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_manager.cpp                                                //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include <iostream>
#include <cstdio>

#include "itr_manager.h"
#include "itr_broker.h"

namespace itr
{

ItrManager::ItrManager(QObject *parent) :
    QObject(parent),
    m_isRun( false ),
    m_pBroker( nullptr )
{
    m_pBroker = new ItrBroker();
    connect( &m_brokerThread, &QThread::started, m_pBroker, &ItrBroker::doWork );
    connect( &m_brokerThread, &QThread::finished, m_pBroker, &ItrBroker::exitWork );
    connect( m_pBroker, &ItrBroker::resultReady, this, &ItrManager::handleResults );
    m_pBroker->moveToThread( &m_brokerThread );
    m_brokerThread.start();
}

ItrManager::~ItrManager()
{
    if( m_pBroker )
        m_pBroker->exitWork();
    m_brokerThread.quit();
    m_brokerThread.wait();
}

void ItrManager::run()
{
    m_isRun = true;

    std::cout << "ItrManager::run1()\n";

    while( m_isRun )
    {
        if( getchar() == 'q' )
            // завершение программы
            break;
        int delay = 1;
        struct timespec ts = { delay/10, 1 };
        timespec remaining;
        nanosleep( &ts, &remaining );
    }

    std::cout << "ItrManager::run2()\n";

    emit finished();
}

void ItrManager::handleResults( const QString& result )
{

    std::cout << "ItrManager::handleResults()" << result.toStdString() << "\n";

}

}
