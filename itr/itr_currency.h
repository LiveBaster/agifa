// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_currency.h                                                 //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __ITR_CURRENCY_H )
#define __ITR_CURRENCY_H

#include <QtCore>
#include "itr_paperbase.h"

namespace itr
{

class ItrCurrency : public ItrPaperBase
// базовая валюта
{
protected:
public:
    ItrCurrency();
    virtual ~ItrCurrency();
};

}

#endif
