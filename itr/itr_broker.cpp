// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_broker.cpp                                                 //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include <iostream>

#include "itr_broker.h"

namespace itr
{

ItrBroker::ItrBroker() :
    m_isRun( false )
{
}

ItrBroker::~ItrBroker()
{
}

void ItrBroker::doWork()
{
    // читаем обновления котировок из потоков истории цен
    // читаем входной поток заявок
    // исполняем заявки
    // результат исполнения заявок пишем в выходной поток результатов исполнения заявок
    QString result;
    m_isRun = true;

    std::cout << "ItrBroker::run1()\n";
/*
    while( m_isRun )
    {

    }
*/
    std::cout << "ItrBroker::run2()\n";

    emit resultReady( result );
}

}
