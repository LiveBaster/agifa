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
    m_motorId( EmptyId ),
    m_actionMin( 0 ),
    m_actionMax( 0 ),
    m_direction( 1 )
{
}

AgifaMotor::AgifaMotor( id_t motorId, action_t actionMin, action_t actionMax ) :
    m_motorId( motorId ),
    m_actionMin( actionMin ),
    m_actionMax( actionMax ),
    m_direction( 1 )
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

action_t AgifaMotor::SynthesisOfAction()
{
    m_action += m_direction;
    if( m_action >= m_actionMax )
        // при достижении максимального ограничения изменяем направление движения мотора
        m_direction = -m_direction;
    else
    if( m_action <= m_actionMin )
        // при достижении минимального ограничения изменяем направление движения мотора
        m_direction = -m_direction;
    return m_action;
}

}
