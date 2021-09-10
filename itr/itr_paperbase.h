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
#include "../agifalib/agifa_array_pointers.h"

namespace itr
{

class ItrPrice
{
protected:
    // цена
    int64_t m_price;
    // знаков после запятой
    int16_t m_decimals;
    // шаг цены
    int16_t m_priceStep;
public:
    ItrPrice() : m_price( 0 ), m_decimals( 2 ), m_priceStep( 1 ) {}
    ItrPrice( int64_t price, int16_t decimals = 2, int16_t priceStep = 1 );

    operator int64_t() const { return m_price; }

    double GetPrice() const { return m_decimals > 0 ? double(m_price)/(10*m_decimals): double(m_price); }
    void SetPrice( double price, int16_t decimals ) { m_price = int64_t(m_decimals > 0 ? price*(10*decimals): price); }
};

class ItrPaperBase : public agifa_base::AgifaLinkPointer
// базовый класс для всех инструментов
{
protected:
    // цена инструмента
    ItrPrice m_price;
    // количество бумаг
    int64_t m_number;
public:
    ItrPaperBase();
    virtual ~ItrPaperBase();

    virtual int Compare( const AgifaLinkPointer* poi );
    virtual AgifaLinkPointer* Duplicate() const;
    virtual AgifaLinkPointer* Copy( const AgifaLinkPointer* poi );
};


}

#endif
