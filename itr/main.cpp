// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       main.cpp                                                       //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include <csignal>

#include <QCoreApplication>
#include <QtCore>
#include <QObject>
#include "itr_manager.h"

using namespace itr;

int main(int argc, char *argv[])
{
    QCoreApplication application( argc, argv );

    ItrManager* ItrManager = new class ItrManager( &application );
    QObject::connect( ItrManager, SIGNAL(finished()), &application, SLOT(quit()) );
    QTimer::singleShot( 0, ItrManager, SLOT(run()) );
    return application.exec();
}
