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

namespace itr
{

class ItrBroker
// симулятор брокера
// входные данные: потоки истории цен по каждому инструменту, потоки заявок
// выходные данные: потоки результатов исполнения заявок
{
protected:
public:
    ItrBroker();
    virtual ~ItrBroker();
};

}

#endif
