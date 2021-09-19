// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_manager.h                                                  //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __ITR_MANAGER_H )
#define __ITR_MANAGER_H

#include <QtCore>
#include <QObject>

#include "itr_broker.h"

namespace itr
{

class ItrManager : public QObject
{
    Q_OBJECT
protected:
    bool m_isRun;
    ItrBroker* m_pBroker;
    QThread m_brokerThread;
public:
    ItrManager( QObject* parent = nullptr );
    virtual ~ItrManager();

    // выбрать перспективную акцию из списка доступных акций
    // добавить перспективную акцию в текущий портфель
    // увеличить количество открытых позиций в акции на один пакет лотов
    // уменьшить количество открытых позиций в акции на один пакет лотов
    // запросить увеличение баланса валютой из внешнего источника (пополнить брокерский счёт)
    // увеличить валютный баланс за счёт сокращения открытых позиций в акциях, с целью исполнения внешнего запроса на вывод валюты с брокерского счёта

public slots:
    void run();
    void handleResults( const QString& result );
signals:
    void finished();
};

}

#endif
