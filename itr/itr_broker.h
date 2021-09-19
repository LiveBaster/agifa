// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_broker.h                                                   //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __ITR_BROKER_H )
#define __ITR_BROKER_H

#include <QtCore>
#include <QObject>
#include "itr_stock.h"

namespace itr
{

using namespace agifa_base;

class ItrBroker : public QObject
// симулятор брокера
// входные данные: потоки истории цен по каждому инструменту, поток заявок
// выходные данные: поток результатов исполнения заявок
{
    Q_OBJECT
protected:
    AgifaArrayTemp<ItrStock> m_stocks;
    bool m_isRun;
public:
    ItrBroker();
    virtual ~ItrBroker();

    void doWork();
signals:
    void resultReady( const QString& result );
};

}

#endif
