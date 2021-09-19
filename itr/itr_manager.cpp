// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_manager.cpp                                                //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include <iostream>

#include "itr_manager.h"
#include "itr_broker.h"

namespace itr
{

ItrManager::ItrManager(QObject *parent) :
    QObject(parent)
{
    ItrBroker* pBroker = new ItrBroker();
    connect( &m_brokerThread, &QThread::started, pBroker, &ItrBroker::doWork );
    connect( &m_brokerThread, &QThread::finished, pBroker, &QObject::deleteLater );
    connect( pBroker, &ItrBroker::resultReady, this, &ItrManager::handleResults );
    pBroker->moveToThread( &m_brokerThread );
    m_brokerThread.start();
}

ItrManager::~ItrManager()
{
    m_brokerThread.quit();
    m_brokerThread.wait();
}

void ItrManager::run()
{

    std::cout << "ItrManager::run()\n";

    emit finished();
}

void ItrManager::handleResults( const QString& result )
{

    std::cout << "ItrManager::handleResults()" << result.toStdString() << "\n";

}

}
