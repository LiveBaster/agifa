// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_portfolio.h                                                //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __ITR_PORTFOLIO_H )
#define __ITR_PORTFOLIO_H

#include <QtCore>

namespace itr
{

class ItrPortfolio
// портфель инструментов
{
protected:
public:
    ItrPortfolio();
    virtual ~ItrPortfolio();
};

}

#endif
