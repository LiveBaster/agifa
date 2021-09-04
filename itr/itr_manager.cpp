// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_manager.cpp                                                //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include "itr_manager.h"

namespace itr
{

ItrManager::ItrManager(QObject *parent) :
    QObject(parent)
{
}

ItrManager::~ItrManager()
{
}

void ItrManager::run()
{
    // Do processing here

    emit finished();
}

}
