// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_stock.h                                                    //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __ITR_STOCK_H )
#define __ITR_STOCK_H

#include <QtCore>
#include "itr_paperbase.h"

namespace itr
{

class ItrStock : public ItrPaperBase
// акция
{
protected:
public:
    ItrStock();
    virtual ~ItrStock();
};

}

#endif
