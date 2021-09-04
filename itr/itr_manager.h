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

namespace itr
{

class ItrManager : public QObject
{
    Q_OBJECT
public:
    ItrManager(QObject *parent = nullptr);
    virtual ~ItrManager();

public slots:
    void run();

signals:
    void finished();
};

}

#endif
