// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_paperbase.h                                                //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __ITR_PAPERBASE_H )
#define __ITR_PAPERBASE_H

#include <QtCore>

namespace itr
{

class ItrPaperBase
// базовый класс для всех инструментов
{
protected:
public:
    ItrPaperBase();
    virtual ~ItrPaperBase();
};


}

#endif
