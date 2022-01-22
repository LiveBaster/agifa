// Project AGIFA                                                              //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_motor.cpp                                                //
// AUTHORS:    Victor Artyukhov, Nikita Demerza                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include "agifa_motor.h"

namespace agifa_base
{

AgifaMotor::AgifaMotor() :
    m_motorId( EmptyId )
{
}

AgifaMotor::~AgifaMotor()
{
}

int AgifaMotor::Compare( const AgifaLinkPointer* poi )
{
    AgifaMotor* p = (AgifaMotor*)poi;
    if( m_motorId == p->m_motorId )
        return 0 ;
    if( m_motorId < p->m_motorId )
        return -1;
    return 1;
}

AgifaLinkPointer* AgifaMotor::Duplicate() const
{
    return (new AgifaMotor())->Copy( this );
}

AgifaLinkPointer* AgifaMotor::Copy( const AgifaLinkPointer* poi )
{
    AgifaMotor* p = (AgifaMotor*)poi;
    m_motorId = p->m_motorId;
    return this;
}

}
