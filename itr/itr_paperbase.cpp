// Project AGIFA/ITR                                                          //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       itr_paperbase.cpp                                              //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include "itr_paperbase.h"

namespace itr
{

using namespace agifa_base;

ItrPaperBase::ItrPaperBase()
{
}

ItrPaperBase::~ItrPaperBase()
{
}

int ItrPaperBase::Compare( const AgifaLinkPointer* poi )
{
    ItrPaperBase* p = (ItrPaperBase*)poi;
    if( m_price == p->m_price )
        return 0;
    if( m_price < p->m_price )
        return -1;
    return 1;
}

AgifaLinkPointer* ItrPaperBase::Duplicate() const
{
    return (new ItrPaperBase())->Copy( this );
}

AgifaLinkPointer* ItrPaperBase::Copy( const AgifaLinkPointer* poi )
{
    ItrPaperBase* p = (ItrPaperBase*)poi;
    m_price = p->m_price;
    m_number = p->m_number;
    return this;
}

}
