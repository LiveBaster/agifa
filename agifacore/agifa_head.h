// Project AGIFA/Core                                                         //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_head.h                                                   //
// AUTHORS:    Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __AGIFA_HEAD_H )
#define __AGIFA_HEAD_H

#include <QtCore>
#include <QObject>

#include "agifa_brain.h"

namespace agifa_core
{

class AgifaHead : public QObject
{
    Q_OBJECT
protected:
    bool m_isRun;
    // компонент "Ухо"
    AgifaBrain* m_pEar;
    QThread m_earThread;
    // компонент "Голосовой аппарат"
    AgifaBrain* m_pVoice;
    QThread m_voiceThread;
public:
    AgifaHead( QObject* parent = nullptr );
    virtual ~AgifaHead();

    // загрузка конфигурации и инициализация головы
    void InitHead();
public slots:
    void run();
    void handleResults( const QString& result );
signals:
    void finished();
protected:
    void Wait();
};

}

#endif
